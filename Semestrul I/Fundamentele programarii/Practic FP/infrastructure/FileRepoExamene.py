from domain.examen import Examen
from infrastructure.repo_examene import RepoExamene


class FileRepoExamene(RepoExamene):

    def __init__(self, __cale_catre_fisier):
        RepoExamene.__init__(self)
        self.__cale_catre_fisier = __cale_catre_fisier

    def __read_all_from_file(self):
        '''
        citeste toate examenele din fisier
        :return: -
        '''
        with open(self.__cale_catre_fisier, "r") as f:
            lines = f.readlines()
            self._examene.clear()
            for line in lines:
                line.strip()
                if line != "":
                    parti = line.split(",")
                    data = parti[0]
                    ora = parti[1]
                    materie = parti[2]
                    tip = parti[3]
                    examen = Examen(data, ora, materie, tip)
                    self._examene[examen.get_materie()+examen.get_tip()] = examen

    def __append_to_file(self, examen):
        '''
        adauga la fisier
        :param examen: examen
        :return: -
        '''
        with open(self.__cale_catre_fisier, "a") as f:
            f.write(str(examen) + "\n")

    def __write_all_to_file(self):
        '''
        scrie in fisier toate examenel
        :return: -
        '''
        with open(self.__cale_catre_fisier, "w") as f:
            for examen in self._examene:
                f.write(str(self._examene[examen]) + "\n")

    def adauga_examen(self, examen):
        '''
        adauga examen in fisier si in repo
        :param examen: examen
        :return: -
        '''
        self.__read_all_from_file()
        RepoExamene.adauga_examen(self, examen)
        self.__append_to_file(examen)

    def get_all(self):
        '''
        returneaza toate examenele programate
        :return: lista examene programate
        '''
        self.__read_all_from_file()
        return RepoExamene.get_all(self)
