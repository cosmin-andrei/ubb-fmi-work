def slr_parse(input_sequence, action, goto):
    stack_states = [0]  # stari
    stack_symbols = []  # simboluri
    input_sequence.append('$')

    index = 0  # index secv intrare, pt a duce de la un simbol la altul
    while True:
        current_state = stack_states[-1]
        current_symbol = input_sequence[index]

        print(f"Stare curenta: {current_state}, Simbol curent: {current_symbol}")
        print(f"Stiva stari: {stack_states}, Stiva simboluri: {stack_symbols}")

        #validation of symbol
        if current_symbol not in action[current_state]:
            expected = ", ".join(action[current_state].keys())
            return (f"Eroare: simbol invalid '{current_symbol}' in starea {current_state}. "
                    f"Simboluri așteptate: {expected}")

        #determin tipul actiunii - Shift, Reduce, Accept
        action_type = action[current_state][current_symbol]

        #SHIFT
        if action_type.startswith('S'):
            next_state = int(action_type[1:])
            stack_states.append(next_state)
            stack_symbols.append(current_symbol)
            index += 1
            print(f"Shift: trecem la starea {next_state}")

        #REDUCE
        elif action_type.startswith('R'):
            print(f"Reducem cu productia: {action_type[2:]}")
            left, right = action_type[2:].split(' -> ') #split stanga-dreapta
            right_length = len(right) if right != 'ε' else 0

            # scot stari si simboluri
            for _ in range(right_length):
                stack_states.pop()
                stack_symbols.pop()

            current_state = stack_states[-1]
            if left not in goto[current_state]:
                return f"Eroare: nu exista tranziție '{left}' in starea {current_state}"

            stack_states.append(goto[current_state][left])
            stack_symbols.append(left)
            print(f"Reduce: am trecut la starea {stack_states[-1]} + '{left}'")

        elif action_type == 'Accept':
            return "Secventa acceptata"

        else:
            return f"Eroare: {action_type}"