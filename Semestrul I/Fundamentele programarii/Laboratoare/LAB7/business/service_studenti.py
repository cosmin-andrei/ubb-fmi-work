from domain.student import Student


class ServiceStudenti:

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

    def get_all_studenti(self):
        '''
        returneaza toti studentii
        :return: returneaza lista de studenti
        '''
        return self.__repo_studenti.get_all()
