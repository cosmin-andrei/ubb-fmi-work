class Tranzitie:
    def __init__(self, sursa, destinatie, valoare):
        self.valoare = valoare
        self.sursa = sursa
        self.destinatie = destinatie

    def __str__(self):
        return self.sursa + " " +  self.destinatie + " " + self.valoare
