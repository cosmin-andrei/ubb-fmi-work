from grammar_utils import load_grammar, extend_grammar, calculate_follow
from parser import slr_parse
from slr_table import construct_slr_table, print_slr_table, construct_canonical_collection
from syntactic_analyzer import analyze_syntactic

def main():
    grammar_file = "grammar.txt"
    program_file = "program.txt"

    print("\n\nRezultat PARTEA 2:")
    analyze_syntactic(grammar_file, program_file)

    grammar_file = "gramatica.txt"
    grammar = load_grammar(grammar_file)

    print("\nGramatica init:")
    for production in grammar:
        if not isinstance(production, tuple) or len(production) != 2:
            print(f"Productie invalida: {production}")
            raise ValueError("Productiile din gramatica initiala nu sunt corecte.")
        print(f"{production[0]} -> {production[1]}")

    extended_grammar = extend_grammar(grammar)

    print("\nGramatica extinsa:")
    for production in extended_grammar:
        if not isinstance(production, tuple) or len(production) != 2:
            print(f"Productie invalida: {production}")
            raise ValueError("Productiile din gramatica extinsa nu sunt corecte.")
        print(f"{production[0]} -> {production[1]}")

    states, transitions = construct_canonical_collection(extended_grammar)

    print("\nColectia canonica de stari:")
    for i, state in enumerate(states):
        print(f"Stare I{i}:")
        for item in state:
            if not isinstance(item, tuple) or len(item) != 3:
                print(f"Item invalid in stare {i}: {item}")
                raise ValueError("Itemii din colectia canonica nu sunt corecti.")
            print(f"  {item}")

    print("\nTranzitii intre stari:")
    for key, value in transitions.items():
        print(f"{key} -> {value}")

    follow = calculate_follow(extended_grammar, extended_grammar[0][0])

    try:
        action, goto = construct_slr_table(states, transitions, follow)
    except ValueError as e:
        print("Eroare: A fost detectata o problema in timpul construirii tabelului SLR.")
        print(e)
        return

    print("\nTabelul de analiza SLR:")
    print_slr_table(action, goto, extended_grammar)

    input_sequence = list(input("Introduceti secventa de intrare (ex. b p e): ").split())
    result = slr_parse(input_sequence, action, goto)
    print(result)

if __name__ == "__main__":
    main()
