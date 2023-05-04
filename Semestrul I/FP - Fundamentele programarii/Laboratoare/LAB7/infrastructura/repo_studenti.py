from domain.student import Student


class RepoStudenti:
    def __init__(self):
        self.__studenti = []

    def adauga_student(self,student):
        '''
        adauga un student la lista studenti
        :param student: student
        :return: -
        '''
        self.__studenti.append(student)

    def sterge_student_dupa_id(self, id_student):
        '''
        sterge studentul dupa idul intreg id_student
        :param id_student: int
        :return:-
        '''
        for _student in self.__studenti:
            if Student.get_id_student(_student) == id_student:
                self.__studenti.remove(_student)

    def cauta_student_dupa_id(self, id_student):
        '''
        cauta studentul dupa idul intreg id_student
        :param id_student: int
        :return: -
        '''
        for _student in self.__studenti:
            if Student.get_id_student(_student) == id_student:
                return _student

    def modifica_student(self, student):
        '''
        modifica studentul dupa idul sau intreg
        :param student: student
        :return: -
        '''
        for _student in self.__studenti:
            if Student.get_id_student(_student) == Student.get_id_student(student):
                nume = Student.get_nume(student)
                Student.set_nume(_student,nume)
                grupa = Student.get_grupa(student)
                Student.set_grupa(_student,grupa)

    def get_all(self):
        '''
        search all the students and put them in a dictionary
        :return: a list with students
        '''
        studenti = []
        for student in self.__studenti:
            studenti.append(student)
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
