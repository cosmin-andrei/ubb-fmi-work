from domain.student import Student


class Teste:

    def __init__(self):
        self.__id_student = 1
        self.__nume_student = "Andrei Cosmin"
        self.__grupa_student = 211
        self.__student = Student(self.__id_student, self.__nume_student, self.__grupa_student)

    def __teste_domain_student(self):
        assert (self.__id_student == self.__student.get_id_student())
        assert (self.__nume_student == self.__student.get_nume())
        assert (self.__grupa_student == self.__student.get_grupa())

    def ruleaza_teste(self):
        self.__teste_domain_student()
        print("toate testele au mers bine")
