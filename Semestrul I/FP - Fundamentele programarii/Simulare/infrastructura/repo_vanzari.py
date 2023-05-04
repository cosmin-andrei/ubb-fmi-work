from domain.vanzari import Vanzare
from exceptions.repo_error import RepoError


class RepoVanzari:

    def __init__(self, __cale_catre_fisier):
        self._vanzari = {}
        self.__cale_catre_fisier = __cale_catre_fisier

    def __read_all_from_file(self):
        '''
        citeste din fisier toate vanzarile
        :return: -
        '''
        with open(self.__cale_catre_fisier,"r") as f:
            lines = f.readlines()
            self._vanzari.clear()
            for line in lines:
                line = line.strip()
                if line != "":
                    parts = line.split(",")
                    id_produs = parts[0]
                    denumire = parts[1]
                    nr_bucati_vandute = parts[2]
                    vanzare = Vanzare(id_produs, denumire, nr_bucati_vandute)
                    self._vanzari[id_produs]= vanzare

    def __write_all_to_file(self):
        '''
        scrie in fisier vanzari
        :return: -
        '''
        with open(self.__cale_catre_fisier,"w") as f:
            for vanzare in self._vanzari:
                f.write(str(vanzare)+"\n")

    def __append_to_file(self, vanzare):
        '''
        adauga in fisier vanzari
        :param vanzare: vanzare
        :return: -
        '''
        with open(self.__cale_catre_fisier,"a") as f:
            f.write(str(vanzare)+"\n")

    def adauga_vanzare(self, vanzare):
        '''
        adauga vanzari in repo
        :param vanzare: vanzare
        :return: -
        '''
        self.__read_all_from_file()
        id_vanzare = vanzare.get_id_produs()
        self._vanzari[id_vanzare] = vanzare.get_nr_bucati_vandute() + vanzare
        self.__append_to_file(vanzare)