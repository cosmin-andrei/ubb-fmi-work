class Examen:

    def __init__(self, data, ora, materie, tip):
        self.__data = data
        self.__ora = ora
        self.__materie = materie
        self.__tip = tip

    def get_data(self):
        '''
        returneaza data examenului
        :return: string
        '''
        return self.__data

    def get_ora(self):
        '''
        returneaza ora examenului
        :return: string
        '''
        return self.__ora

    def get_materie(self):
        '''
        returneaza materia examenului
        :return: string
        '''
        return self.__materie

    def get_tip(self):
        '''
        returneaza tipul examenului
        :return: string
        '''
        return self.__tip

    def __eq__(self, other):
        '''
        verifica daca doua examene sunt la fel
        :param other: examen
        :return: True - daca examenele sunt la fel
                False - altfel
        '''
        return (self.__materie == other.__materie) and (self.__tip == other.__tip)

    def __str__(self):
        '''
        returneaza informatii despre un examen
        :return: examen
        '''
        return f"{self.__data},{self.__ora},{self.__materie},{self.__tip}"
