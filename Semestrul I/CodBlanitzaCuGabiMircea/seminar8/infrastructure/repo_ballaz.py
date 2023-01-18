from exceptions.repo_error import RepoError


class RepoBallaz:

    def __init__(self):
        self._ballaz = {}

    def add_balla(self, balla):
        id_baller = balla.get_id_baller()
        if id_baller in self._ballaz:
            raise RepoError("balla existent!")
        self._ballaz[id_baller] = balla

    def sterge_balla(self,id_baller):
        if id_baller not in self._ballaz:
            raise RepoError("balla inexistent!")
        del self._ballaz[id_baller]

    def modifica_balla(self,balla):
        id_baller = balla.get_id_baller()
        if id_baller not in self._ballaz:
            raise RepoError("balla inexistent!")
        self._ballaz[id_baller] = balla

    def get_all_ballaz(self):
        return [x for x in self._ballaz.values()]

    def size(self):
        return len(self._ballaz)

    def cauta_balla_dupa_id(self,id_baller):
        if id_baller not in self._ballaz:
            raise RepoError("balla inexistent!")
        return self._ballaz[id_baller]