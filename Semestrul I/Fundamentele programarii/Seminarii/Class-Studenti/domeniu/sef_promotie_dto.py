class SefPromotieDTO:

    def __init__(self, nume_student, medie_student):
        self.__nume_student = nume_student
        self.__medie_student = medie_student

    def __str__(self):
        return f"studentul {self.__nume_student} cu media {self.__medie_student}"

    def __lt__(self, other):
        return self.__medie_student < other.__medie_student
