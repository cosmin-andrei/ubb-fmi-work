class Nota:

    def __init__(self, id_nota, id_student, id_laborator, valoare_nota):
        self.__valoare_nota = valoare_nota
        self.__id_laborator = id_laborator
        self.__id_student = id_student
        self.__id_nota = id_nota

    def get_id_nota(self):
        '''
        :return: int-id unic identificabil
        '''
        return self.__id_nota

    def get_id_student(self):
        '''
        returneaza id student
        :return: int - id student
        '''
        return self.__id_student

    def get_id_laborator(self):
        '''
        returneaza id laborator
        :return: int - id laborator
        '''
        return self.__id_laborator

    def get_valoare_nota(self):
        '''
        returneaza valoarea notei
        :return: int - valoare nota
        '''
        return self.__valoare_nota

    def set_valoare_nota(self, valoare_nota):
        '''
        seteaza o noua valoare a nota
        :param valoare_nota: int
        :return: -
        '''
        self.__valoare_nota = valoare_nota

    def __eq__(self, other):
        '''
                verifica daca doua iduri sunt egale
                :param other: nota
                :return: - bool: True daca notele au acelasi id
                                False altfel
                '''
        return self.__id_nota == other.__id_nota

    def __str__(self):
        '''
        :return: id nota si valoarea notei
        '''
        return f"{self.__id_nota} {self.__id_student} {self.__id_laborator} {self.__valoare_nota}"

class notaDTO:

    def __init__(self, valoare_nota):
        self.__valoare_nota = valoare_nota

    def __str__(self):
        '''
        :return: valoare nota
        '''
        return f"{self.__valoare_nota}"

