#DIFERENTE:
# - list/str
# - direct cu nonterminalii/terminalii, nu pe baza de majuscula

#FIRST
def compute_first_of_symbol(symbol, grammar, first_sets):
    nonterminals = set(prod[0] for prod in grammar) #identific neterminale
    if symbol in nonterminals:
        return first_sets[symbol] #multime precalculata
    else:
        return {symbol} #pt terminali

#return lista de productii (left, [right_symbols])
def load_grammar_inline(file_path):
    grammar = []
    with open(file_path, 'r', encoding='utf-8') as file:
        for line in file:
            line = line.strip()
            if not line or '->' not in line:
                continue
            left, right = line.split("->")
            left = left.strip()
            alternatives = right.split("|")
            for alt in alternatives:
                right_symbols = alt.strip().split()
                grammar.append((left, right_symbols))
    return grammar


#calculez multimea FIRST
def compute_first_sets(grammar):
    nonterminals = set(prod[0] for prod in grammar) #neterminalii
    all_symbols = set()
    for left, right in grammar: #all symbols
        for sym in right:
            all_symbols.add(sym)
    terminals = all_symbols - nonterminals

    first_sets = {nt: set() for nt in nonterminals}

    changed = True
    while changed:
        changed = False
        # for each product
        for (left, right_list) in grammar:
            derive_epsilon = True
            i = 0
            while i < len(right_list) and derive_epsilon:
                X = right_list[i]
                if X in terminals:
                    before = len(first_sets[left])
                    first_sets[left].add(X)
                    after = len(first_sets[left])
                    if after > before:
                        changed = True
                    derive_epsilon = False
                else:
                    before = len(first_sets[left])
                    to_add = (first_sets[X] - {'ε'})
                    first_sets[left].update(to_add)
                    after = len(first_sets[left])
                    if after > before:
                        changed = True
                    if 'ε' not in first_sets[X]:
                        derive_epsilon = False
                i += 1

            if derive_epsilon:
                if 'ε' not in first_sets[left]:
                    first_sets[left].add('ε')
                    changed = True

    return first_sets



def extend_grammar_inline(grammar):
    original_start = grammar[0][0]
    extended_grammar = [("S'", [original_start])] + grammar
    return extended_grammar


def compute_nonterminals_and_terminals(grammar):
    nonterminals = set([prod[0] for prod in grammar])
    all_symbols = set()
    for left, right in grammar:
        for sym in right:
            all_symbols.add(sym)
    terminals = all_symbols - nonterminals

    return nonterminals, terminals


def compute_follow_sets(grammar, start_symbol):
    nonterminals, terminals = compute_nonterminals_and_terminals(grammar)
    first_sets = compute_first_sets(grammar)
    follow = {nt: set() for nt in nonterminals}
    follow[start_symbol].add('$')  # EOF
    productions_dict = {}
    for left, right in grammar:
        if left not in productions_dict:
            productions_dict[left] = []
        productions_dict[left].append(right)

    changed = True
    while changed:
        changed = False
        for (left, right) in grammar:
            for i, B in enumerate(right):
                if B in nonterminals:
                    beta = right[i + 1:]
                    if beta:
                        derive_epsilon = True
                        j = 0
                        local_first = set()
                        while j < len(beta) and derive_epsilon:
                            sym = beta[j]
                            fs = compute_first_of_symbol(sym, grammar, first_sets)
                            local_first.update(fs - {'ε'})
                            if 'ε' not in fs:
                                derive_epsilon = False
                            j += 1
                        before = len(follow[B])
                        follow[B].update(local_first)
                        after = len(follow[B])
                        if after > before:
                            changed = True

                        if derive_epsilon:
                            before2 = len(follow[B])
                            follow[B].update(follow[left])
                            after2 = len(follow[B])
                            if after2 > before2:
                                changed = True
                    else:
                        before = len(follow[B])
                        follow[B].update(follow[left])
                        after = len(follow[B])
                        if after > before:
                            changed = True
    return follow


def closure(items, grammar, nonterminals):
    closure_set = set(items)
    changed = True
    while changed:
        changed = False
        for (left, right, dotpos) in list(closure_set):
            if dotpos < len(right):
                symbol = right[dotpos]
                if symbol in nonterminals:
                    for (A, prod_right) in grammar:
                        if A == symbol:
                            new_item = (A, tuple(prod_right), 0)
                            if new_item not in closure_set:
                                closure_set.add(new_item)
                                changed = True
    return closure_set

def goto(items, symbol, grammar, nonterminals):
    moved = set()
    for (left, right, dotpos) in items:
        if dotpos < len(right) and right[dotpos] == symbol:
            new_item = (left, right, dotpos + 1)
            moved.add(new_item)
    return closure(moved, grammar, nonterminals)

def construct_canonical_collection_inline(grammar):
    nonterminals, terminals = compute_nonterminals_and_terminals(grammar)
    start_symbol = grammar[0][0]
    initial_item = (start_symbol, tuple(grammar[0][1]), 0)
    initial_closure = closure({initial_item}, grammar, nonterminals)

    states = [initial_closure]
    transitions = {}
    changed = True

    while changed:
        changed = False
        for s in states:
            possible_symbols = set()
            for (lft, rght, dotpos) in s:
                if dotpos < len(rght):
                    possible_symbols.add(rght[dotpos])
            for sym in possible_symbols:
                new_state = goto(s, sym, grammar, nonterminals)
                if new_state and new_state not in states:
                    states.append(new_state)
                    changed = True
                if new_state:
                    transitions[(frozenset(s), sym)] = new_state

    return states, transitions


def construct_slr_tables_inline(states, transitions, grammar, follow_sets):
    """
    states (list of set): starile
    transitions (dict): tranzitiile
    grammar (list): gramatica
    follow_sets (dict): FOLLOW
    Return: tuple: (action, goto_table), unde fiecare este un tabel de analiza SLR.

    frozenset - set dar nu il mai poti modifica dupa
    """

    nonterminals, terminals = compute_nonterminals_and_terminals(grammar)

    #mapez fiecare stare cu indexul unic
    index_of_state = {frozenset(st): i for i, st in enumerate(states)}
    action = [{} for _ in range(len(states))] #action (terminale)
    goto_table = [{} for _ in range(len(states))] #goto (neterminale)

    # parcurg fiecare stare si starea in sine
    for i, st in enumerate(states):
        for (left, right, dotpos) in st:
            if dotpos < len(right): # . nu e la final
                # determin simbol si calculez starea rezultata din tranzitie
                sym = right[dotpos]
                next_state = transitions.get((frozenset(st), sym), None)
                if next_state is not None:
                    j = index_of_state[frozenset(next_state)] #index of next state
                    # Terminal => SHIFT
                    if sym in terminals or sym == '$':
                        if sym not in action[i]:
                            action[i][sym] = f"S{j}" #SHIFT -> starea j
                        else:
                            # register conflict
                            existing = action[i][sym]
                            action[i][sym] = [existing, f"S{j}"]
                    else:
                        # E neterminal => GOTO
                        goto_table[i][sym] = j
            else: # . la finalul productiei
                # dotpos == len(right) -> REDUCE
                if left == "S'":
                    action[i]['$'] = "Accept"
                else:
                    # Reduce cu left -> right prin aplicarea regulii
                    reduce_rule = f"R {left} -> {' '.join(right)}"
                    # Pentru fiecare simbol din FOLLOW(left)
                    for terminal in follow_sets[left]:
                        if terminal not in action[i]: # nu exista, o aplicam
                            action[i][terminal] = reduce_rule
                        else:
                            # Conflict (shift/reduce sau reduce/reduce)
                            existing = action[i][terminal]
                            action[i][terminal] = [existing, reduce_rule]


    for i, row in enumerate(action):
        for sym, val in row.items():
            if isinstance(val, list):
                print(f"Conflict: starea {i}, simbol = {sym}, acțiuni = {val}")
                raise ValueError("Gramatica nu este SLR.")

    return action, goto_table


def slr_parse_inline(input_tokens, action_table, goto_table):
    # simbolul de final
    input_tokens = list(input_tokens) + ['$']

    # stiva stari
    stack = [0]  # index stare
    output = []

    index = 0
    while True:
        state = stack[-1]  # starea din varful stivei (adica cea curenta)
        lookahead = input_tokens[index] #input simbol

        #verificam actiunile definite ale simbolului
        if lookahead not in action_table[state]:
            #returnam eroare daca nu e valid
            expected = ", ".join(action_table[state].keys())
            return f"Eroare: simbol invalid '{lookahead}' starea {state}. Simboluri asteptate: {expected}"

        #actiune simbol curent
        action_val = action_table[state][lookahead]
        if action_val == "Accept":
            output.append("Accept")
            return output

        elif isinstance(action_val, str) and action_val.startswith("S"):
            # SHIFT: trecem la o noua stare
            next_state = int(action_val[1:])
            stack.append(next_state)
            index += 1
            output.append(f"SHIFT: {lookahead} -> starea {next_state}")

        elif isinstance(action_val, str) and action_val.startswith("R "):
            # REDUCE
            rule = action_val[2:] #obtinem partea dreapta a regulii
            left, right = rule.split("->")
            left = left.strip() #neterminalul
            right_symbols = right.strip().split() #partea din dreapta regulii

            # scoatem din lista len(simboluri) cate are right
            if not (len(right_symbols) == 1 and right_symbols[0] == 'ε'):
                for _ in range(len(right_symbols)):
                    stack.pop()

            # obtin noua stare
            top_state = stack[-1]
            # GOTO pe left
            goto_dict = goto_table[top_state]
            if left not in goto_dict:
                return f"Eroare: nu exista GOTO({top_state}, {left})"

            new_state = goto_dict[left]
            stack.append(new_state)
            output.append(f"REDUCE: {left} -> {' '.join(right_symbols)} (stare={new_state})")

        else:
            return f"Eroare: {action_val}"


def analyze_syntactic(grammar_file, program_file):
    """
    - incarc gramatica
    - extind
    - construiesc starile+follow
    - construiesc SLR
    - citesc FIP
    - aplic parser
    - afisez
    """

    grammar = load_grammar_inline(grammar_file)
    for left, right in grammar:
        print(" ", left, "->", right)

    extended_grammar = extend_grammar_inline(grammar)
    print("\nGramatica extinsa:")
    for left, right in extended_grammar:
        print(" ", left, "->", right)

    states, transitions = construct_canonical_collection_inline(extended_grammar)
    print("\ncolectia canonica:")
    for i, st in enumerate(states):
        print(f"  Stare {i}:")
        for it in st:
            print("   ", it)

    print("\nTranzitii intre stari:")
    from_state_to_index = {frozenset(s): idx for idx, s in enumerate(states)}
    for (kset, sym), tset in transitions.items():
        print(f"   (I{from_state_to_index[kset]}, '{sym}') = I{from_state_to_index[frozenset(tset)]}")

    start_symbol = extended_grammar[0][0]
    follow_sets = compute_follow_sets(extended_grammar, start_symbol)

    print("\nFOLLOW:")
    for nt, sset in follow_sets.items():
        print(f"  FOLLOW({nt}) = {sset}")

    try:
        action_table, goto_table = construct_slr_tables_inline(
            states, transitions, extended_grammar, follow_sets
        )
    except ValueError as ve:
        print("\nEroare: Conflict detectat tabela SLR.")
        print(ve)
        return

    with open(program_file, 'r', encoding='utf-8') as f:
        program_input = f.read().split()

    parse_result = slr_parse_inline(program_input, action_table, goto_table)
    if isinstance(parse_result, list):
        for step in parse_result:
            print(step)
    else:
        print(parse_result)
