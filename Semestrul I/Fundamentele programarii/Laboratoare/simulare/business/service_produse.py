from domain.produs import Produs


class ServiceProduse:

    def __init__(self, repo_produse):
        self.__repo_produse = repo_produse

    def adauga_produs(self, id_produs, denumire, pret, nr_bucati, tip):
        '''
        adauga un produs de tip Produs la repoul de produse
        :param id_produs: int
        :param denumire: string
        :param pret: float
        :param nr_bucati: int
        :param tip: string
        :return: -
        '''
        produs = Produs(id_produs, denumire, pret, nr_bucati, tip)
        self.__repo_produse.adauga_produs(produs)

    def cauta_tip(self, tip_produs):
        '''
        returneaza toate produsele de un anumit tip din repo
        :param tip_produs: string
        :return: dictionar - produse_cautate
        '''
        produse_cautate={}
        produse = self.__repo_produse.get_all()
        for produs in produse:
            tip = produs.get_tip()
            if tip_produs == tip:
                produse_cautate[produs.get_id_produs] = produs
        return produse_cautate

    def get_all(self):
        '''
        :return: toate produsele din repo
        '''
        return self.__repo_produse.get_all()