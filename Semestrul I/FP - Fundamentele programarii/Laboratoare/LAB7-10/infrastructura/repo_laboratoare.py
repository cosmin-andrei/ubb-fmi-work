from erori.exceptions import RepoError


class RepoLaboratoare:

    def __init__(self):
        self._laboratoare={}

    def __len__(self):
        '''
        :return: int - numarul laboratoarelor
        '''
        return len(self._laboratoare)

    def adauga_laborator(self, laborator):
        '''
        adauga un laborator la lista
        :param laborator: laborator
        :return: -
        '''
        if laborator.get_id_laborator() in self._laboratoare:
            raise ValueError("laborator existent!")
        self._laboratoare[laborator.get_id_laborator()] = laborator

    def sterge_laborator(self, id_laborator):
        '''
        sterge un laborator dupa id
        :param id_laborator: int
        :return: -
        '''
        if id_laborator not in self._laboratoare:
            raise RepoError("laborator inexistent!")
        del self._laboratoare[id_laborator]

    def modifica_laborator(self, laborator):
        '''
        modifica un laborator dupa id
        :param laborator: laborator
        :return: -
        '''
        if laborator.get_id_laborator() not in self._laboratoare:
            raise RepoError("laborator inexistent!")
        self._laboratoare[laborator.get_id_laborator()] = laborator

    def get_all(self):
        '''
        returneaza toate laboratoarele existente
        :return: lista cu labs existente
        '''
        laboratoare = []
        for laboratoare_id in self._laboratoare:
            laboratoare.append(self._laboratoare[laboratoare_id])
        return laboratoare

    def cauta_laborator_dupa_id(self, id_laborator):
        '''
        cauta un laborator dupa id unic identificabil
        :param id_laborator: int
        :return: laborator
        '''
        if id_laborator not in self._laboratoare:
            raise RepoError("laborator inexistent!")
        return self._laboratoare[id_laborator]
