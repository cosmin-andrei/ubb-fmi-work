from domain.laborator import Laborator
from infrastructura.repo_laboratoare import RepoLaboratoare

class FileRepoLabs(RepoLaboratoare):

    def __init__(self, __cale_catre_fisier):
        RepoLaboratoare.__init__(self)
        self.__cale_catre_fisier = __cale_catre_fisier

    def __read_all_from_file(self):
        with open(self.__cale_catre_fisier,"r") as f:
            lines = f.readlines()
            self._laboratoare.clear()
            for line in lines:
                line = line.strip()
                if line != "":
                    parts = line.split()
                    id_lab = int(parts[0])
                    descriere = parts[1]
                    zi = int(parts[2])
                    luna = int(parts[3])
                    an = int(parts[4])
                    laborator = Laborator(id_lab, descriere, zi, luna, an)
                    self._laboratoare[id_lab] = laborator

    def __write_all_to_file(self):
        with open(self.__cale_catre_fisier, "w") as f:
            for laborator in self._laboratoare:
                f.write(str(laborator) + "\n")

    def __append_to_file(self, laborator):
        with open(self.__cale_catre_fisier, "a") as f:
            f.write(str(laborator) + "\n")

    def adauga_laborator(self, laborator):
        self.__read_all_from_file()
        RepoLaboratoare.adauga_laborator(self, laborator)
        self.__append_to_file(laborator)

    def sterge_laborator(self, id_laborator):
        self.__read_all_from_file()
        RepoLaboratoare.sterge_laborator(self, id_laborator)
        self.__write_all_to_file()

    def modifica_laborator(self,laborator):
        self.__read_all_from_file()
        RepoLaboratoare.modifica_laborator(self, laborator)
        self.__write_all_to_file()

    def cauta_laborator_dupa_id(self, id_laborator):
        self.__read_all_from_file()
        return RepoLaboratoare.cauta_laborator_dupa_id(self, id_laborator)

    def get_all(self):
        self.__read_all_from_file()
        return RepoLaboratoare.get_all(self)