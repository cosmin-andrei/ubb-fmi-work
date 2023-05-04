from business.service_examene import ServiceExamene
from domain.examen import Examen
from infrastructure.repo_examene import RepoExamene
from validatoare.validator_examen import ValidareExamen


class Teste:

    def __testeDomain(self):
        examen = Examen("20.02","08:00","FP","normala")
        assert examen.get_data() == "20.02"
        assert examen.get_ora() == "08:00"
        assert examen.get_materie() == "FP"
        assert examen.get_tip() == "normala"

    def __testeValidator(self):
        examen_gresit = Examen("00.15","25:65","","test")
        try:
            ValidareExamen.valideaza_examen(examen_gresit)
        except ValueError as ve:
            assert str(ve) == "data invalida\nora invalida\nmaterie invalida\ntip invalid\n"
        examen = Examen("20.02","08:00","FP","normala")
        ValidareExamen.valideaza_examen(examen)

    def __testeRepo(self):
        repo = RepoExamene()
        assert len(repo.get_all()) == 0
        repo.adauga_examen(Examen("20.02","08:00","FP","normala"))
        assert repo.get_all() == [Examen("20.02","08:00","FP","normala")]
        try:
            repo.adauga_examen(Examen("20.02","08:00","FP","normala"))
        except ValueError as ve:
            assert str(ve) == "examen existent"

    def __testeService(self):
        repo = RepoExamene()
        validator = ValidareExamen()
        service = ServiceExamene(repo, validator)
        assert len(service.get_all()) == 0
        service.adauga_examen("20.02","08:00","FP","normala")
        assert len(service.get_all()) == 1
        try:
            service.adauga_examen("20.02", "08:00", "FP", "normala")
        except ValueError as ve:
            assert str(ve) == "examen existent"
        service.adauga_examen("21.03","09:00","LC","restanta")
        service.adauga_examen("21.03","08:00","FP","restanta")
        service.adauga_examen("26.01","10:00","ASC","normala")
        service.adauga_examen("26.01","08:00","LC","normala")
        service.adauga_examen("27.01","09:00","C","normala")
        examene = service.data_de_azi()
#        assert examene == [Examen("26.01","08:00","LC","normala"),Examen("26.01","10:00","ASC","normala")]

        examene=[]
        service.export("test4.txt","FP LC")
        with open("test4.txt", "r") as f:
            lines = f.readlines()
            for line in lines:
                line.strip()
                if line != "":
                    parti = line.split(",")
                    data = parti[0]
                    ora = parti[1]
                    materie = parti[2]
                    tip = parti[3]
                    examen = Examen(data, ora, materie, tip)
                    examene.append(examen)
        #assert examene == [Examen("20.02","08:00","FP","normala"), Examen("21.03","08:00","FP","restanta"), Examen("21.03","09:00","LC","restanta"), Examen("26.01","08:00","LC","normala")]

        examene = service.tabel("26.01")
        assert examene == [Examen("26.01","10:00","ASC","normala"), Examen("26.01","08:00","LC","normala"), Examen("27.01","09:00", "C","normala")]

    def run(self):
        self.__testeDomain()
        self.__testeValidator()
        self.__testeRepo()
        self.__testeService()
        print("teste rulate cu succes")