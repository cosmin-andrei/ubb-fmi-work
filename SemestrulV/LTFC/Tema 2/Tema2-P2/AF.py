class AF:
    def __init__(self, alfabet, stari, initial_state, tranzitii, stare_finala):
        self.alfabet = alfabet
        self.stari = stari
        self.stare_initiala = initial_state
        self.tranzitii = tranzitii
        self.stare_finala = stare_finala

    def verifica_stare(self, secventa):
        stare_curenta = self.stare_initiala
        while secventa:
            gasit = False
            for tranzitie in self.tranzitii:
                if tranzitie.sursa == stare_curenta and tranzitie.valoare == secventa[: len(tranzitie.valoare)]:
                    secventa = secventa[len(tranzitie.valoare):]
                    stare_curenta = tranzitie.destinatie
                    gasit = True
                    break

            if not gasit:
                return False

        if stare_curenta in self.stare_finala:
            return True

        return False

    def get_longest_prefix(self, secventa):
        prefix = ""
        stare_curenta = self.stare_initiala

        while secventa:
            gasit = False
            for tranzitie in self.tranzitii:
                if tranzitie.sursa == stare_curenta and tranzitie.valoare == secventa[: len(tranzitie.valoare)]:
                    prefix += tranzitie.valoare
                    secventa = secventa[len(tranzitie.valoare):]
                    stare_curenta = tranzitie.destinatie
                    gasit = True
                    break
            if not gasit:
                return prefix

        return prefix