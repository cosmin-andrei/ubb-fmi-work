class Nota:

    def __init__(self, id_nota, student, id_laborator, nota):
        self.__id_nota = id_nota
        self.__student = student
        self.__id_laborator = id_laborator
        self.__nota = nota
        self.__sters = False

    def get_id_nota(self):
        return self.__id_nota

    def get_student(self):
        return self.__student

    def get_nota(self):
        return self.__nota

    def set_nota(self, nume):
        self.__nota = nume

    def __eq__(self, other):
        return self.__id_nota == other.__id_nota

    def __str__(self):
        return f"{self.__id_nota} {self.__nota}"

    def sterge(self):
        self.__sters = True
