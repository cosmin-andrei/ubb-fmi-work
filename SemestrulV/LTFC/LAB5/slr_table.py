from tabulate import tabulate

# adaug toate productiile relevante pentru simbolurile nonterminale
# de dupa punct
def closure(items, grammar):
    closure_set = set(items)
    added = True

    while added:
        added = False
        #items from current closure
        for (left, right, dot_pos) in list(closure_set):
            if dot_pos < len(right):  # if symbol after dot
                symbol = right[dot_pos]
                if symbol.isupper():  # if non terminal, caut productiile
                    for prod_left, prod_right in grammar:
                        if prod_left == symbol: #productia are in stanga dot
                            new_item = (prod_left, prod_right, 0) #adaug la inceput (.)
                            if new_item not in closure_set: # nu exista, o adaugam in closure
                                closure_set.add(new_item)
                                added = True
    return closure_set

#goto-ul unui set de itemi
def goto(items, symbol, grammar):
    goto_set = set()
    #iterez prin starea curenta
    for (left, right, dot_pos) in items:
        #verific unde este punctul si pun un nou item
        if dot_pos < len(right) and right[dot_pos] == symbol:
            goto_set.add((left, right, dot_pos + 1))
    return closure(goto_set, grammar)

#colectia canonica
#tuple: states - lista de stari canonice
#       tranzitii - dict al tranzitiilor intre stari
def construct_canonical_collection(grammar):
    start_symbol = grammar[0][0] #start gramatica
    initial_item = (start_symbol, grammar[0][1], 0)  # S' -> · S
    initial_closure = closure([initial_item], grammar) #closeure stare init

    states = [initial_closure] #lista de stari
    transitions = {}

    added = True
    while added:
        added = False
        for state in states: #iterez starile
            #obtin simbolurile din partea dreapta si
            #calculez starea rezultata prin aplicare goto pe simbol curent
            for symbol in {s for _, right, _ in state for s in right}:
                new_state = goto(state, symbol, grammar)

                #valid + not exist => adaug starea si tranzitia
                if new_state and new_state not in states:
                    states.append(new_state)
                    added = True
                if new_state:
                    transitions[(tuple(state), symbol)] = new_state

    return states, transitions


#construiesc tabelul de analiza SLR (action+goto)
def construct_slr_table(states, transitions, follow):
    """
    states (list of set): colectia canonica de stari
    transitions (dict): tranzitii intre stari
    grammar (list of tuples): gramatica
    follow (dict): multumi follow pt fiecare nonterminal

    Return: tuple: (action, goto_table) lista de dictionare fiecare
    """

    #init action+goto
    action = [{} for _ in range(len(states))]
    goto_table = [{} for _ in range(len(states))]

    # parcurg fiecare stare
    for i, state in enumerate(states):
        for item in state:
            left, right, dot_pos = item
            if dot_pos < len(right): #dot not at the final
                symbol = right[dot_pos] #adaug simbol imediat dupa punct

                if symbol.islower() or symbol == '$':  # Terminal
                    next_state = None
                    # Find destination state pentru tranzitia cu simbolul curent
                    for (state_key, transition_symbol), target_state in transitions.items():
                        if tuple(state) == state_key and symbol == transition_symbol:
                            next_state = target_state
                            break

                    if next_state is not None:
                        action_entry = f"S{states.index(next_state)}" #Actiunea SHIFT
                        #gestionare conflicte (Shift-Shift.. Shift-Reduce
                        if symbol in action[i]:
                            if isinstance(action[i][symbol], list):
                                action[i][symbol].append(action_entry)
                            else:
                                action[i][symbol] = [action[i][symbol], action_entry]
                        else:
                            action[i][symbol] = action_entry

                else:  # Non-terminal
                    next_state = None
                    # Find destionation state pentru tranzitia cu simbolul curent
                    for (state_key, transition_symbol), target_state in transitions.items():
                        if tuple(state) == state_key and symbol == transition_symbol:
                            next_state = target_state
                            break
                    if next_state is not None: #o adaug in go_to
                        goto_table[i][symbol] = states.index(next_state)
            else:
                if left == "S'":
                    action[i]['$'] = "Accept"
                else:
                    #Reduce pentru fiecare simbol din FOLLOW (left)
                    for terminal in follow[left]:
                        # remove ( )
                        action_entry = f"R {left} -> {right}"

                        #simbol terminal existent deja in tabelul de actiuni
                        if terminal in action[i]:
                            #isinstance - verifica daca apartine... is list?
                            if isinstance(action[i][terminal], list):
                                action[i][terminal].append(action_entry) #aplicam reduce
                            else:
                                action[i][terminal] = [action[i][terminal], action_entry]
                        else:
                            action[i][terminal] = action_entry

    # verific existenta conflictelor
    conflicts = []
    for i, state_actions in enumerate(action):
        for symbol, entries in state_actions.items():
            if isinstance(entries, list):
                conflicts.append((i, symbol, entries))

    if conflicts:
        print("Conflict tabel SLR:")
        for state, symbol, entries in conflicts:
            print(f"Starea {state}, simbolul '{symbol}' are conflicte: {entries}")
        raise ValueError("Gramatica nu e SLR.")

    return action, goto_table


def print_slr_table(action, goto2, grammar):
    terminals = set()
    non_terminals = set()
    for left, right in grammar:
        for symbol in right:
            if symbol.isupper():
                non_terminals.add(symbol)
            else:
                terminals.add(symbol)
    terminals.add('$')

    terminals = sorted(terminals)
    non_terminals = sorted(non_terminals)
    headers = ['State'] + terminals + non_terminals
    table = []

    for i in range(len(action)):
        row = [i]
        for t in terminals:
            entry = action[i].get(t, '')
            row.append(entry)
        for nt in non_terminals:
            entry = goto2[i].get(nt, '')
            row.append(entry)
        table.append(row)

    print(tabulate(table, headers=headers, tablefmt='grid'))