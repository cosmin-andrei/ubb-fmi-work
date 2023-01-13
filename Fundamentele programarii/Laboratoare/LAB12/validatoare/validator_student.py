from erori.exceptions import EroriValidare


class ValidatorStudent:
    @staticmethod
    def valideaza_student(student):
        erori = ""
        if student.get_id_student() < 0:
            erori += "id invalid\n"
        if student.get_nume() == "":
            erori += "nume invalid\n"
        if student.get_grupa() <= 0:
            erori += "grupa invalida\n"
        if len(erori) > 0:
            raise EroriValidare(erori)