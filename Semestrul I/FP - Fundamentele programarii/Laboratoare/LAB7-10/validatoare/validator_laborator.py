from erori.exceptions import EroriValidare


class ValidatorLaborator:
    @staticmethod
    def valideaza_laborator(laborator):
        erori = ""
        if laborator.get_id_laborator() <= 0:
            erori += "id invalid\n"
        if laborator.get_descriere() == "":
            erori += "descriere invalida\n"
        if laborator.get_zi_deadline() <= 0 or laborator.get_zi_deadline() >31:
            erori += "zi invalida\n"
        if laborator.get_luna_deadline() <=0 or laborator.get_luna_deadline() >12:
            erori += "luna invalida\n"
        if len(erori) > 0:
            raise EroriValidare(erori)