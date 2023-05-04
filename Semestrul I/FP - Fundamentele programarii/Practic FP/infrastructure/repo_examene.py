class RepoExamene:

    def __init__(self):
        self._examene={}

    def adauga_examen(self, examen):
        '''
        adauga in dictionar un examen
        :param examen: examen
        :return: -
        '''
        id_examen=examen.get_materie()+examen.get_tip()
        if id_examen in self._examene:
            raise ValueError("examen existent")
        self._examene[examen.get_materie()+examen.get_tip()] = examen

    def get_all(self):
        '''
        returneaza o lista cu toate examenele programate
        :return: lista
        '''
        examene = []
        for examen in self._examene:
            examene.append(self._examene[examen])
        return examene
