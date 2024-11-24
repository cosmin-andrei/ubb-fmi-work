from AF import automat_finit


def print_menu():
    print("\nMeniu:")
    print("1. read from file")
    print("2. read from cmd")
    print("3. print automat")
    print("4. verify seq")
    print("5. prefix")


def main():
    fa = automat_finit()
    while True:
        print_menu()
        option = input("Choose your option: ")

        if option == '1':
            path = input("Path: ")
            fa.load_from_file(path)
        elif option == '2':
            fa.read_from_cmd()
        elif option == '3':
            fa.print_all()
        elif option == '4':
            seq = input("Input sequence: ")
            if fa.check(seq):
                print("OK")
            else:
                print("Not OK")
        elif option == '5':
            seq = input("Input sequence: ")
            print(f"Longest seq: {fa.prefix(seq)}")
        elif option == '6':
            print(fa.verify_determinist())
        else:
            print("Choose a valid option")

if __name__ == '__main__':
    main()
