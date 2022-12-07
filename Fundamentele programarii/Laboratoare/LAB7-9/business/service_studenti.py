import string
from domain.student import Student
import random

from erori.repo_error import RepoError


class ServiceStudenti:

    def __init__(self, validator_student, repo_studenti):
        self.__validator_student = validator_student
        self.__repo_studenti = repo_studenti
        self.__lnume_random = ["Andreea", "Adriana", "Ariana", "Cosmin", "Gabi", "Mihaela", "a", "b", "c", "d", "e", "f", "g"]

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
        modifica studentul cu id identificabil
        :param id_student: int
        :param nume_nou: string
        :param grupa_noua: int
        :return: -
        '''
        student = Student(id_student, nume_nou, grupa_noua)
        self.__validator_student.valideaza_student(student)
        self.__repo_studenti.adauga_student(student)

    def get_all_studenti(self):
        '''
        returneaza toti studentii
        :return: returneaza lista de studenti
        '''
        return self.__repo_studenti.get_all()

    def genereaza_id_random(self):
        '''
        returneaza un id random generat
        :return: int - id random generat
        '''
        id_random = random.randrange(1,100)
        while id_random in self.__repo_studenti.get_iduri_existente():
            id_random = random.randrange(1, 100)
        return id_random
    def genereaza_nume_random(self):
        '''
        returneaza un nume random din lista de nume random
        :return: string - nume random
        '''
        nume_random = random.choice(self.__lnume_random)
        return nume_random
    def genereaza_grupa_random(self,):
        '''
        returneaza un numar de grupa random
        :return: int - numar grupa generat
        '''
        id_random = random.randrange(100, 999)
        return id_random
