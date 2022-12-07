class Nota:

    def __init__(self, id_nota, student, valoare_nota):
        self.__id_nota = id_nota
        self.__student = student
        self.__valoare_nota = valoare_nota

    def get_id_nota(self):
        '''
        returneaza idul notei
        :return: int - id nota
        '''
        return self.__id_nota

    def get_student(self):
        '''
        returneaza studentul
        :return: student
        '''
        return self.__student

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
                verifica daca doua note au acelasi id
                :param other: nota
                :return: - bool: True daca notele au acelasi id
                                False altfel
                '''
        return self.__id_nota == other.__id_nota

    def __str__(self):
        '''
        :return: id nota si valoarea notei
        '''
        return f"{self.__id_nota} {self.__valoare_nota}"
