
class RepoNote:
    def __init__(self):
        self._note = {}

    def adauga_nota(self, nota):
        '''
        adauga nota in dictionarul de note
        :param nota: nota
        :return: -
        '''
        if nota.get_id_nota() in self._note:
            raise ValueError("nota existenta!")
        self._note[nota.get_id_nota()] = nota

    def sterge_nota_dupa_id(self, id_nota):
        '''
        sterge nota dupa id
        :param id_nota: int
        :return:
        '''
        del self._note[id_nota]

    def get_all(self):
        '''
        returneaza o lista cu toate notele
        :return: lista de note
        '''
        note = []
        for nota_id in self._note:
            note.append(self._note[nota_id])
        return note
