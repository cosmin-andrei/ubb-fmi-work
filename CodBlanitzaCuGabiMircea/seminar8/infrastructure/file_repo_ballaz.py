from domain.baller import Baller
from infrastructure.repo_ballaz import RepoBallaz


class FileRepoBallaz(RepoBallaz):

    def __init__(self,__cale_catre_fisier):
        RepoBallaz.__init__(self)
        self.__cale_catre_fisier = __cale_catre_fisier

    def __read_all_from_file(self):
        with open(self.__cale_catre_fisier,"r") as f:
            lines = f.readlines()
            self._ballaz.clear()
            for line in lines:
                line = line.strip()
                if line != "":
                    parts = line.split(",")
                    id_baller = int(parts[0])
                    name = parts[1]
                    value = float(parts[2])
                    balla = Baller(id_baller,name,value)
                    self._ballaz[id_baller]= balla

    def __write_all_to_file(self):
        with open(self.__cale_catre_fisier,"w") as f:
            for balla in self._ballaz:
                f.write(str(balla)+"\n")

    def __append_to_file(self,balla):
        with open(self.__cale_catre_fisier,"a") as f:
            f.write(str(balla)+"\n")

    def add_balla(self, balla):
        self.__read_all_from_file()
        RepoBallaz.add_balla(self,balla)
        self.__append_to_file(balla)

    def modifica_balla(self,balla):
        self.__read_all_from_file()
        RepoBallaz.modifica_balla(self, balla)
        self.__write_all_to_file()

    def sterge_balla(self,id_baller):
        self.__read_all_from_file()
        RepoBallaz.sterge_balla(self, id_baller)
        self.__write_all_to_file()

    def get_all_ballaz(self):
        self.__read_all_from_file()
        return RepoBallaz.get_all_ballaz(self)

    def size(self):
        self.__read_all_from_file()
        return RepoBallaz.size(self)

    def cauta_balla_dupa_id(self,id_baller):
        self.__read_all_from_file()
        return RepoBallaz.cauta_balla_dupa_id(self,id_baller)