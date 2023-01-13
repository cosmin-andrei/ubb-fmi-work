class Laborator:

    def __init__(self, id_laborator, descriere, zi_deadline, luna_deadline, an_deadline):
        self.__id_laborator = id_laborator
        self.__descriere = descriere
        self.__zi_deadline = zi_deadline
        self.__luna_deadline = luna_deadline
        self.__an_deadline = an_deadline

    def get_id_laborator(self):
        '''
        :return: int - ID unic identificabil
        '''
        return self.__id_laborator

    def get_descriere(self):
        '''

        :return: string - enuntul problemei
        '''
        return self.__descriere

    def get_zi_deadline(self):
        '''

        :return: int - zi deadline
        '''
        return self.__zi_deadline

    def get_luna_deadline(self):
        '''
        :return: int - luna deadline
        '''
        return self.__luna_deadline

    def get_an_deadline(self):
        '''
        :return: int - an deadline
        '''
        return self.__an_deadline

    def set_descriere(self, descriere):
        '''
        seteaza descrierea problemei
        :param descriere: string
        :return: -
        '''
        self.__descriere = descriere

    def set_zi_deadline(self, zi_deadline):
        '''
        seteaza ziua deadline
        :param zi_deadline: int
        :return: -
        '''
        self.__zi_deadline = zi_deadline

    def set_luna_deadline(self, luna_deadline):
        '''
        seteaza luna deadline
        :param luna_deadline: int
        :return: -
        '''
        self.__luna_deadline = luna_deadline

    def set_an_deadline(self, an_deadline):
        '''
        seteaza an deadline
        :param an_deadline: int
        :return: -
        '''
        self.__an_deadline = an_deadline

    def __eq__(self, other):
        '''
        verifica daca doua laboratoare au acelasi id unic identificabil
        :param other: laboraotr
        :return: - true daca au acelasi id
                - false daca au iduri diferite
        '''
        return self.__id_laborator == other.__id_laborator

    def __str__(self):
        '''
        :return: id laborator, descriere, zi+luna+an deadline
        '''
        return f"{self.__id_laborator} {self.__descriere} {self.__zi_deadline} {self.__luna_deadline} {self.__an_deadline}"
