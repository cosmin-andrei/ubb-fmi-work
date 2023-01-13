class Produs:

    def __init__(self, id_produs, denumire, pret, nr_bucati, tip):
        self.__id_produs = id_produs
        self.__denumire = denumire
        self.__pret = pret
        self.__nr_bucati = nr_bucati
        self.__tip = tip

    def get_id_produs(self):
        '''

        :return: idul int al produsului
        '''
        return self.__id_produs

    def get_denumire(self):
        '''

        :return: denumirea string a produsului
        '''
        return self.__denumire

    def get_pret(self):
        '''

        :return: pretul float al produsului
        '''
        return self.__pret

    def get_nr_bucati(self):
        '''

        :return: nr de bucati int al produsului
        '''
        return self.__nr_bucati

    def get_tip(self):
        '''

        :return: tipul string al produsului
        '''
        return self.__tip