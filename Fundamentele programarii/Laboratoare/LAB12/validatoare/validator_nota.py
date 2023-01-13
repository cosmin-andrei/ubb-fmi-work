from erori.exceptions import EroriValidare


class ValidatorNota:

    def valideaza_nota(nota):
        erori = ""
        if nota.get_valoare_nota() < 1:
            erori += "nota invalida\n"
        elif nota.get_valoare_nota() >10:
            erori += "nota invalida\n"
        if len(erori) > 0:
            raise EroriValidare(erori)