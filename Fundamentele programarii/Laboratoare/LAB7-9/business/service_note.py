from domain.nota import Nota


class ServiceNote:

    def __init__(self, validator_nota, repo_note, repo_studenti):
        self.__validator_nota = validator_nota
        self.__repo_note = repo_note
        self.__repo_studenti = repo_studenti

    def adauga_nota_service(self, id_student, id_nota, valoare_nota):
        '''
        adauga nota studentului cu id identificabil
        :param id_nota: int
        :param id_student: int
        :param valoare_nota: int
        :return: -
        '''
        student = self.__repo_studenti.cauta_student_dupa_id(id_student)
        nota = Nota(id_nota, student, valoare_nota)
        self.__validator_nota.valideaza_nota(nota)
        self.__repo_note.adauga_nota(nota)

    def sterge_student_si_notele_lui(self, id_student):
        '''
        sterge toate notele studentului identificat prin id unic identificabil id_student
        :param id_student: int
        :return: -
        '''
        student = self.__repo_studenti.cauta_student_dupa_id(id_student)
        note = self.__repo_note.get_all()
        note_student = [x for x in note if x.get_student() == student]
        for nota_student in note_student:
            self.__repo_note.sterge_nota_dupa_id(nota_student.get_id_nota())
        self.__repo_studenti.sterge_student_dupa_id(id_student)

        def get_all(self):
            '''
            returneaza toate notele
            :return: returneaza lista de note
            '''
            return self.__repo_note.get_all()
