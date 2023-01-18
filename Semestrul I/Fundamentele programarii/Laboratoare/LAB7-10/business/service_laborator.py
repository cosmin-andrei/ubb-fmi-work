from domain.laborator import Laborator


class ServiceLaborator:
    def __init__(self, validator_laborator, repo_laboratoare):
        self.__validator_laborator = validator_laborator
        self.__repo_laboratoare = repo_laboratoare

    def adauga_laborator_service(self, id_laborator, descriere, zi_deadline, luna_deadline, an_deadline):
        '''
        adauga laborator cu id unic identificabil
        :param id_laborator: int
        :param descriere: string
        :param zi_deadline: int
        :param luna_deadline: int
        :param an_deadline: int
        :return:
        '''
        laborator = Laborator(id_laborator, descriere, zi_deadline, luna_deadline, an_deadline)
        self.__repo_laboratoare.adauga_laborator(laborator)

    def cauta_laborator_dupa_id(self, id_laborator):
        '''
        cauta laborator dupa id unic identificabil
        :param id_laborator: int
        :return:
        '''
        laborator = self.__repo_laboratoare.cauta_laborator_dupa_id(id_laborator)
        return laborator

    def modifica_laborator(self, id_laborator, descriere_noua, zi_deadline_noua, luna_deadline_noua, an_deadline_nou):
        '''
        modifica laboratorul cu id unic identificabil
        :param id_laborator: int
        :param descriere_noua: string
        :param zi_deadline_noua: int
        :param luna_deadline_noua: int
        :param an_deadline_nou: int
        :return:
        '''
        laborator = Laborator(id_laborator, descriere_noua, zi_deadline_noua, luna_deadline_noua, an_deadline_nou)
        self.__validator_laborator.valideaza_laborator(laborator)
        self.__repo_laboratoare.modifica_laborator(laborator)

    def get_all(self):
        return self.__repo_laboratoare.get_all()