from domain.produs import Produs
from domain.vanzari import Vanzare
from infrastructura.repo_produse import RepoProduse
from infrastructura.repo_vanzari import RepoVanzari


class Teste:

    def __init__(self):
        #produs
        self.__id_produs = 1
        self.__denumire = "Crizantema"
        self.__pret = 10
        self.__nr_bucati = 100
        self.__tip = "floare"
        self.__produs = Produs(self.__id_produs, self.__denumire, self.__pret, self.__nr_bucati, self.__tip)

        #vanzare
        self.__nr_bucati_vandute = 10
        self.__vanzare = Vanzare(self.__id_produs, self.__denumire, self.__nr_bucati_vandute)

        #repo produse
        self.__repo_produse = RepoProduse
        self.__repo_vanzari = RepoVanzari


    def __teste_domain(self):
        '''
        testeaza domeniile produs si vanzare
        :return: -
        '''
        #produs
        assert(self.__produs.get_id_produs() == self.__id_produs)
        assert(self.__produs.get_denumire() == self.__denumire)
        assert(self.__produs.get_pret() == self.__pret)
        assert(self.__produs.get_nr_bucati() == self.__nr_bucati)
        assert(self.__produs.get_tip() == self.__tip)

        #vanzari
        assert(self.__vanzare.get_id() == self.__id_produs)
        assert(self.__vanzare.get_denumire_produs() == self.__denumire)
        assert(self.__vanzare.get_nr_bucati_vandute() == self.__nr_bucati_vandute)

    def __teste_repo(self):
        produs = Produs(self.__id_produs, self.__denumire, self.__pret, self.__nr_bucati, self.__tip)


    def run_teste(self):
        self.__teste_domain()
