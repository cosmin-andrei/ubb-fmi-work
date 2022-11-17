from erori.repo_error import RepoError


class RepoStudenti:
    def __init__(self):
        self.__studenti = {}

    def adauga_student(self, student):
        if student.get_id_student() in self.__studenti:
            raise RepoError("student existent!")
        self.__studenti[student.get_id_student()] = student

    def sterge_student_dupa_id(self, id_student):
        if id_student not in self.__studenti:
            raise RepoError("student inexistent!")
        del self.__studenti[id_student]

    def cauta_student_dupa_id(self, id_student):
        if id_student not in self.__studenti:
            raise RepoError("student inexistent!")
        return self.__studenti[id_student]

    def modifica_student(self, student):
        if student.get_id_student() not in self.__studenti:
            raise RepoError("student inexistent!")
        self.__studenti[student.get_id_student()] = student

    def get_all(self):
        studenti = []
        for studenti_id in self.__studenti:
            studenti.append(self.__studenti[studenti_id])
        return studenti

    def __len__(self):
        return len(self.__studenti)
