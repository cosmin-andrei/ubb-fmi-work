from domain.vanzari import Vanzare


class ServiceVanzare:

    def __init__(self, repo_vanzari):
        self.__repo_vanzari = repo_vanzari

    def adauga_vanzare(self, id_produs, denumire, nr_bucati_vandute):
        '''
        adauga o vanzare la repo
        :param id_produs: int
        :param denumire: string
        :param nr_bucati_vandute: int
        :return: -
        '''
        vanzare = Vanzare(id_produs, denumire, nr_bucati_vandute)
        self.__repo_vanzari.adauga_vanzare(vanzare)