from erori.repo_error import RepoError


class RepoNote:
    def __init__(self):
        self.__note = {}

    def get_all(self):
        '''
        returneaza o lista cu toate notele
        :return: lista de note
        '''
        note = []
        for nota_id in self.__note:
            note.append(self.__note[nota_id])
        return note

    def adauga_nota(self, nota):
        '''
        adauga nota in dictionarul de note
        :param nota: nota
        :return: -
        '''
        if nota.get_id_nota() in self.__note:
            raise ValueError("nota existenta!")
        self.__note[nota.get_id_nota()] = nota

    def sterge_nota_dupa_id(self, id_nota):
        '''
        sterge nota dupa id unic identificabil
        :param id_nota: int
        :return: -
        '''
        if id_nota not in self.__note:
            raise RepoError("nota inexistenta!")
        del self.__note[id_nota]

    def modifica_nota(self, nota):
        '''
        modifica nota cu una noua
        :param nota: nota
        :return:
        '''
        if nota.get_id_nota() not in self.__note:
            raise RepoError("nota inexistenta!")
        self.__note[nota.get_id_nota()] = nota

    def __len__(self):
        '''
        :return: int - numarul de note
        '''
        return len(self.__note)
    def removeAll(self):
        '''
        removes all notes
        :return: -
        '''
        self.__note.clear()