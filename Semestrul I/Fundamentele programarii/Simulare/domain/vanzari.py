class Vanzare:

    def __init__(self, id_produs, denumire_produs, nr_bucati_vandute):
        self.__id_produs = id_produs
        self.__denumire_produs = denumire_produs
        self.__nr_bucati_vandute = nr_bucati_vandute

    def get_id(self):
        return self.__id_produs

    def get_denumire_produs(self):
        return self.__denumire_produs

    def get_nr_bucati_vandute(self):
        return self.__nr_bucati_vandute
