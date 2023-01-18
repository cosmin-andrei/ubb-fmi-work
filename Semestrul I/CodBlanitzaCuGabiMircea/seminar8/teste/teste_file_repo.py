from domain.baller import Baller
from infrastructure.file_repo_ballaz import FileRepoBallaz


class Teste:
    def __init__(self):
        pass

    def run_all_tests(self):
        self.__run_file_repo_tests()
    def __goleste_fisier(self,cale_catre_fisier):
        with open(cale_catre_fisier,"w") as f:
            f.write("")
    def __run_file_repo_tests(self):
        cale_fisier_test = "teste/ballaz_teste.txt"
        self.__goleste_fisier(cale_fisier_test)
        repo = FileRepoBallaz(cale_fisier_test)
        assert repo.size() == 0
        id_baller = 23
        name = "Jordan"
        value = 9000.1
        balla = Baller(id_baller,name,value)
        repo.add_balla(balla)
        assert repo.size() == 1
        gasit_balla = repo.cauta_balla_dupa_id(id_baller)
        assert (gasit_balla.get_name()==balla.get_name())
