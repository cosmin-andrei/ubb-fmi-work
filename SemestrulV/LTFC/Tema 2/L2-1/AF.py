from enum import verify


class automat_finit:
    def __init__(self):
        self.states = set()
        self.alphabet = set()
        self.transitions = []
        self.final_states = set()

    def read_transitions(self, tr):
        tr = tr.split(", ")  # split la ,
        for transition in tr:
            transition = transition.strip()  # remove white spaces
            if "->" in transition and ":" in transition:  # verific sa fie valida
                from_st, rest = transition.split("->")  # from si restul
                to_st, alph = rest.split(":")
                from_st = from_st.strip()
                to_st = to_st.strip()
                alph = alph.strip().split(",")
                self.transitions.append((from_st, to_st, alph))

    def load_from_file(self, filename):
        with open(filename, 'r') as f:
            lines = f.readlines()
            self.states = set(lines[0].strip().split(', '))
            self.alphabet = set(lines[1].strip().split(', '))
            self.read_transitions(lines[2].strip())
            self.final_states = set(lines[3].strip().split(', '))

    def print_all(self):
        print("Stari: ", self.states)
        print("Alphabet: ", self.alphabet)
        print("Transitions: ", self.transitions)
        print("Final states: ", self.final_states)

    def check(self, seq):
        if self.verify_determinist():
            curr_state = 'q0'
            for alph in seq:  # parcurg secventa
                ok = False
                for from_st, to_st, alphabet in self.transitions:  # iterez prin lista de tranzitii a automatului
                    if curr_state == from_st and alph in alphabet:
                        curr_state = to_st
                        ok = True
                        break
                if not ok:
                    return False
            return curr_state in self.final_states  # verifica daca e in final states
        else:
            print("Eroare")

    def prefix(self, seq):
        if self.verify_determinist():
            curr_state = 'q0'
            max_prefix = ""
            curr_prefix = ""
            ok_eps = 0

            if curr_state in self.final_states:
                ok_eps = 1

            for alph in seq:
                ok = False
                # iterez prin tranzitii
                for from_st, to_st, alphs in self.transitions:
                    if curr_state == from_st and alph in alphs:
                        curr_state = to_st
                        if curr_state in self.final_states:
                            curr_prefix += alph
                            max_prefix = curr_prefix
                            da = 1
                        else:
                            curr_prefix += alph
                        ok = True
                        break
                if not ok:
                    break

            if max_prefix == "" and ok_eps == 1:
                return "Epsilon"
            else:
                return max_prefix

        else:
            print("Eroare")
            return False

    def read_from_cmd(self):
        self.states = set(input("Input states (comma-separated): ").split(','))
        self.alphabet = set(input("Input alphabet (comma-separated): ").split(','))
        self.read_transitions(input("Input transitions: "))
        self.final_states = set(input("Input final states (comma-separated): ").split(','))

    def verify_determinist(self):
        tr = {}
        for from_st, to_st, alphs in self.transitions:
            for alpha in alphs:
                if from_st not in tr:
                    tr[from_st] = {}
                # exista deja o tranzitie
                if alpha in tr[from_st]:
                    return False

                tr[from_st][alpha] = to_st

        return True
