class Student():

    def __int__(self, id_student, nume, grupa):
        self.__id_student = id_student
        self.__nume = nume
        self.__grupa = grupa

    def get_id_student(self):
        return self.__id_student

    def get_nume(self):
        return self.__id_student

    def get_grupa(self):
        return self.__grupa

    def set_nume(self, nume):
        self.__nume = nume

    def set_grupa(self, grupa):
        self.__grupa = grupa

    def __eq__(self, other):
        return self.__id_student == other.__id_student

    def __str__(self):
        return f"{self.__id_student} {self.__nume}"