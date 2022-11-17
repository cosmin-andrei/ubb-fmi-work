class ValidatorStudent:

    def __init__(self):
        pass

    def valideaza_student(self, student):
        erori = ""
        if student.get_id_student() < 0:
            erori += "id invalid\n"
        if student.get_nume() == "":
            erori += "nume invalid\n"
        if student.get_grupa() < 0:
            erori += "grup invalida\n"
        if len(erori) > 0:
            raise ValidError(erori)