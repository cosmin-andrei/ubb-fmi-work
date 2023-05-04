class Student:

    def __init__(self, id_student, nume):
        self.__id_student = id_student
        self.__nume = nume
        self.__sters = False

    def sterge(self):
        self.__sters = True

    def get_id_student(self):
        return self.__id_student

    def get_nume(self):
        return self.__nume

    def set_nume(self, nume):
        self.__nume = nume

    def __eq__(self, other):
        return self.__id_student == other.__id_student

    def __str__(self):
        return f"{self.__id_student} {self.__nume}"
