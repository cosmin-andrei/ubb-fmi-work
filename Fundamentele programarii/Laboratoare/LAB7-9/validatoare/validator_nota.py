class ValidatorNota:
    def __init__(self):
        pass

    def valideaza_nota(self, nota):
        erori = ""
        if nota.get_id_nota() < 0:
            erori += "id invalid\n"
        if nota.get_valoare_nota() < 1:
            erori += "nota invalida\n"
        elif nota.get_valoare_nota() >10:
            erori += "nota invalida\n"
        if len(erori) > 0:
            raise ValueError(erori)