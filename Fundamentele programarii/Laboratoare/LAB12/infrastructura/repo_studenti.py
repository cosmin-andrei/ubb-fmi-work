from erori.exceptions import RepoError


class RepoStudenti:
    def __init__(self):
        self._studenti = {}

    def adauga_student(self, student):
        '''
        adauga student in dictionarul de studenti
        :param student: student
        :return: -
        '''
        if student.get_id_student() in self._studenti:
            raise RepoError("student existent!")
        self._studenti[student.get_id_student()] = student

    def cauta_student_dupa_id(self, id_student):
        '''
        returneaza studentul cu idul id_student
        :param id_student: int
        :return: student cu idul intreg id_student
        '''
        if id_student not in self._studenti:
            raise RepoError("student inexistent!")
        return self._studenti[id_student]

    def modifica_student(self, student):
        '''
        modifica studentul dupa IDul intreg
        :param student: student
        :return: -
        '''
        if student.get_id_student() not in self._studenti:
            raise RepoError("student inexistent!")
        self._studenti[student.get_id_student()] = student

    def sterge_student_dupa_id(self, id_student):
        '''
        sterge studentul dupa id intreg unic identificabil
        :param id_student: int
        :return: -
        '''
        if id_student not in self._studenti:
            raise RepoError("student inexistent!")
        del self._studenti[id_student]

    def get_all(self):
        '''
        returneaza o lista cu studenti
        :return: lista studenti
        '''
        studenti = []
        for studenti_id in self._studenti:
            studenti.append(self._studenti[studenti_id])
        return studenti