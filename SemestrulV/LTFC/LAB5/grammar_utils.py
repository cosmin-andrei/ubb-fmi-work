
#incarc gramatica si returnez lista de productii
# NonTerminal -> Terminali | NonTerminali
# return list: lista de productii ca perechi (stanga, dreapta)
def load_grammar(file_path):
    grammar = []
    with open(file_path, 'r') as file:
        for line in file:
            left, right = line.strip().split("->")
            alternatives = right.split("|")
            for alternative in alternatives:
                grammar.append((left.strip(), alternative.strip()))
    return grammar

#extind gramatica
def extend_grammar(grammar):
    start_symbol = grammar[0][0]  #simbol start
    extended_grammar = [("S'", start_symbol)] + grammar
    return extended_grammar


#multumile first
#dict cheia-nonterminal -> mult FIRST
def calculate_first(grammar):
    from collections import defaultdict
    productions = defaultdict(list)
    all_symbols = set()

    #construiesc productiile
    for left, right in grammar:
        productions[left].append(right)
        all_symbols.add(left)
        for symbol in right:
            all_symbols.add(symbol)

    # Init mult FIRST
    # nu e in productii -> terminal, FIRST (simbol) = simbol
    first = {symbol: set() for symbol in all_symbols}
    for symbol in all_symbols:
        if symbol not in productions:
            first[symbol] = {symbol}

    changed = True
    while changed:
        changed = False

        # adaug toate simbolurile din FIRST(X) in FIRST(A) - X (din partea dreapta) curent si fara epsilon
        # X contine epsilon => continuam procesarea a ce e in dreapta
        # X nu continue epsilon, ne oprim
        # daca tot ce e in a poate deriva in epsilon, il adaug in FIRST A
        # iterez gramatica
        for A in productions:
            # A->a ; a - secventa
            for alpha in productions[A]:
                i = 0
                # parcurc ce e in dreapta
                while i < len(alpha):
                    X = alpha[i]

                    # adaug epsilon
                    # before_update si after_update pentrun detectie modificari
                    before_update = len(first[A])
                    first[A].update(first[X] - {'ε'})
                    after_update = len(first[A])

                    if after_update > before_update:
                        changed = True

                    if 'ε' not in first[X]:
                        break

                    i += 1
                else:
                    # neterminatii au epsilon si adaugam si la FIRST(A)
                    if 'ε' not in first[A]:
                        first[A].add('ε')
                        changed = True

    #preluam doar ce e in gramatica
    return {A: first[A] for A in productions}

#FOLLOW
#dict: cheie-nonterminat -> mult FOLLOW
def calculate_follow(grammar, start_symbol):
    #multimea FIRST si init FOLLOW
    first = calculate_first(grammar)
    follow = {non_terminal: set() for non_terminal, _ in grammar}
    follow[start_symbol].add('$') # doar pt start

    #gramatica dictionar
    productions = {}
    for left, right in grammar:
        if left not in productions:
            productions[left] = []
        productions[left].append(right)

    while True:
        updated = False
        #iterez productiile din gramatica
        for left, right in grammar:
            #curr_follow multime de simboluri ce poate aparea imediat dupa simbolul curent in prod
            curr_follow = follow[left]
            #ce e in dreapta la productie, in ordine inversa
            for i in reversed(range(len(right))):
                char = right[i]
                if char in follow: #e nonterminal
                    if curr_follow - follow[char]: #diferit ceva
                        follow[char].update(curr_follow)
                        updated = True
                    #produce epsilon => extind
                    if 'ε' in first[char]:
                        curr_follow = curr_follow.union(first[char] - {'ε'})
                    else: #init cu First
                        curr_follow = first[char]
                else:
                    curr_follow = {char}
        if not updated:
            break

    return follow
