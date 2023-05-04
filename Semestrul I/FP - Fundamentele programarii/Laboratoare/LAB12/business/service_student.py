from domain.student import Student


class ServiceStudent:
    def __init__(self, validator_student, repo_studenti):
        self.__validator_student = validator_student
        self.__repo_studenti = repo_studenti

    def adauga_student(self, id_student, nume, grupa):
        '''
        pe baza datelor despre un student va crea un student, va incerca
        sa il valideze si daca e valid, va incerca sa il adauge
        in dictionarul de studenti unic identificabile prin idul lor intreg
        :param id_student: int
        :param nume: string
        :param grupa: int
        :return:-
        '''
        student = Student(id_student, nume, grupa)
        self.__validator_student.valideaza_student(student)
        self.__repo_studenti.adauga_student(student)

    def modifica_student(self, id_student, nume_nou, grupa_noua):
        '''
        modifica studentul cu id unic identificabil
        :param id_student: int
        :param nume_nou: string
        :param grupa_noua: int
        :return: -
        '''
        student = Student(id_student, nume_nou, grupa_noua)
        self.__validator_student.valideaza_student(student)
        self.__repo_studenti.modifica_student(student)

    def cauta_student_dupa_id(self, id_student):
        '''
        cauta student dupa id unic identificabil
        :param id_student: int
        :return: student
        '''
        student = self.__repo_studenti.cauta_student_dupa_id(id_student)
        return student

    def get_all(self):
        return self.__repo_studenti.get_all()


