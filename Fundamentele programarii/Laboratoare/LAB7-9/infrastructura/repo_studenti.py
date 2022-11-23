from erori.repo_error import RepoError


class RepoStudenti:
    def __init__(self):
        self.__studenti = {}

    def adauga_student(self,student):
        '''
        adauga student in dictionarul de studenti
        :param student: student
        :return: -
        '''
        if student.get_id_student() in self.__studenti:
            raise ValueError("student existent!")
        self.__studenti[student.get_id_student()] = student

    def sterge_student_dupa_id(self, id_student):
        '''
        sterge studentul dupa id intreg unic identificabil
        :param id_student: int
        :return: -
        '''
        if id_student not in self.__studenti:
            raise RepoError("student inexistent!")
        del self.__studenti[id_student]

    def cauta_student_dupa_id(self, id_student):
        '''
        returneaza studentul cu idul id_student
        :param id_student: int
        :return: student cu idul intreg id_student
        '''
        if id_student not in self.__studenti:
            raise ValueError("student inexistent!")
        return self.__studenti[id_student]

    def modifica_student(self, student):
        '''
        modifica studentul dupa IDul intreg
        :param student: student
        :return: -
        '''
        if student.get_id_student() not in self.__studenti:
            raise RepoError("student inexistent!")
        self.__studenti[student.get_id_student()] = student

    def get_all(self):
        '''
        search all the students and put them in a dictionary
        :return: a list with students
        '''
        studenti = []
        for studenti_id in self.__studenti:
            studenti.append(self.__studenti[studenti_id])
        return studenti

    def __len__(self):
        '''
        return the number of students
        :return: the number int of students
        '''
        return len(self.__studenti)

    def removeAll(self):
        '''
        removes all students
        :return:
        '''
        self.__studenti.clear()
