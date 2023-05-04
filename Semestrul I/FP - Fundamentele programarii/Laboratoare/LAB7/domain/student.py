class Student:

    def __init__(self, id_student, nume, grupa):
        self.__id_student = id_student
        self.__nume = nume
        self.__grupa = grupa

    def get_id_student(self):
        '''
        returneaza idul studentului
        :return:  int- idul intreg al studentului
        '''
        return self.__id_student

    def get_nume(self):
        '''
        returneaza numele studentului
        :return: string - numele studentului
        '''
        return self.__nume

    def get_grupa(self):
        '''
        returneaza grupa studentului
        :return: int - grupa studentului
        '''
        return self.__grupa

    def set_nume(self, nume):
        '''
        seteaza numele studentului student
        :param nume: string
        :return: -
        '''
        self.__nume = nume

    def set_grupa(self, grupa):
        '''
        seteaza grupa studentului student
        :param grupa: int
        :return: -
        '''
        self.__grupa = grupa

    def __eq__(self, other):
        '''
        verifica daca doi studenti au acelasi id
        :param other: student
        :return: - bool: True daca studentii au acelasi id
                        False altfel
        '''
        return self.__id_student == other.__id_student

    def __str__(self):
        '''
        :return: idul studentului int, numele studentului string, grupa studentului int
        '''
        return f"{self.__id_student} {self.__nume} {self.__grupa}"