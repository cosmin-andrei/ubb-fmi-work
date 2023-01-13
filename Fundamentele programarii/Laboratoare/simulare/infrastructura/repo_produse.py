from domain.produs import Produs
from exceptions.repo_error import RepoError


class RepoProduse:

    def __init__(self, __cale_catre_fisier):
        self._produse = {}
        self.__cale_catre_fisier = __cale_catre_fisier

    def __read_all_from_file(self):
        '''
        citeste toate produsele din fisier
        :return: -
        '''
        with open(self.__cale_catre_fisier,"r") as f:
            lines = f.readlines()
            self._produse.clear()
            for line in lines:
                line = line.strip()
                if line != "":
                    parts = line.split(",")
                    id_produs = int(parts[0])
                    denumire = parts[1]
                    pret = float(parts[2])
                    nr_bucati = int(parts[3])
                    tipul = int(parts[4])
                    produs = Produs(id_produs, denumire, pret, nr_bucati, tipul)
                    self._produse[id_produs] = produs

    def __write_all_to_file(self):
        '''
        scrie in fisier
        :return: -
        '''
        with open(self.__cale_catre_fisier,"w") as f:
            for produs in self._produse:
                f.write(str(produs)+"\n")

    def __append_to_file(self,produs):
        '''
        adauga in fisier
        :param produs: produs
        :return: -
        '''
        with open(self.__cale_catre_fisier,"a") as f:
            f.write(str(produs)+"\n")

    def adauga_produs(self, produs):
        '''
        adauga produsul in dictionarul de produse
        :param produs: produs
        :return: -
        '''
        self.__read_all_from_file()
        id_produs = produs.get_id_produs()
        if produs in self._produse:
            raise RepoError("produs existent!")
        self._produse[id_produs] = produs
        self.__append_to_file(produs)

    def get_all(self):
        '''
        returneaza toate produsele
        :return: lista de produse
        '''
        self.__read_all_from_file()
        produse=[]
        for id_produs in self._produse:
            produse.append(self._produse[id_produs])
        return produse


    def __len__(self):
        '''
        :return: numarul de produse
        '''
        return len(self._produse)



