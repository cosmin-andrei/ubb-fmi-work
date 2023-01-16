import unittest

from business.service_laborator import ServiceLaborator
from business.service_note import ServiceNote
from business.service_student import ServiceStudent
from domain.laborator import Laborator
from domain.nota import Nota
from domain.student import Student
from erori.exceptions import EroriValidare
from infrastructura.repo_laboratoare import RepoLaboratoare
from infrastructura.repo_note import RepoNote
from infrastructura.repo_studenti import RepoStudenti
from validatoare.validator_laborator import ValidatorLaborator
from validatoare.validator_nota import ValidatorNota
from validatoare.validator_student import ValidatorStudent


class Testare(unittest.TestCase):

    def __DomainValidatorsTests(self):

        #Teste student
        student = Student(1, "Cosmin", 211)
        self.assertEqual(student.get_id_student(), 1)
        self.assertEqual(student.get_nume(), "Cosmin")
        self.assertEqual(student.get_grupa(), 211)
        self.assertEqual(str(student), "1 Cosmin 211")
        student.set_nume("Alin")
        self.assertEqual(student.get_nume(), "Alin")
        student.set_grupa(212)
        self.assertEqual(student.get_grupa(), 212)

        #validare student
        student = Student(-1, "", -50)
        self.assertRaises(EroriValidare, ValidatorStudent.valideaza_student, student)

        #Teste laboratoare
        laborator = Laborator(1, "enuntpb", 1, 12, 2023)
        self.assertEqual(laborator.get_id_laborator(), 1)
        self.assertEqual(laborator.get_descriere(), "enuntpb")
        self.assertEqual(laborator.get_zi_deadline(), 1)
        self.assertEqual(laborator. get_luna_deadline(), 12)
        self.assertEqual(laborator.get_an_deadline(), 2023)
        self.assertEqual(str(laborator), "1 enuntpb 1 12 2023")
        laborator.set_descriere("ABC")
        self.assertEqual(laborator.get_descriere(), "ABC")
        laborator.set_zi_deadline(2)
        self.assertEqual(laborator.get_zi_deadline(), 2)
        laborator.set_luna_deadline(10)
        self.assertEqual(laborator.get_luna_deadline(), 10)
        laborator.set_an_deadline(2022)
        self.assertEqual(laborator.get_an_deadline(), 2022)

        #validare laborator
        laborator = Laborator(0, "", 0, 13, 200)
        self.assertRaises(EroriValidare, ValidatorLaborator.valideaza_laborator, laborator)
        laborator = Laborator(0, "", 32, -1, 200)
        self.assertRaises(EroriValidare, ValidatorLaborator.valideaza_laborator, laborator)

        #Teste Note
        nota = Nota(1, 1, 1, 10)
        self.assertEqual(nota.get_id_nota(), 1)
        self.assertEqual(nota.get_id_laborator(), 1)
        self.assertEqual(nota.get_id_student(), 1)
        self.assertEqual(nota.get_valoare_nota(), 10)
        self.assertEqual(str(nota), "1 1 1 10")
        nota.set_valoare_nota(9)
        self.assertEqual(nota.get_valoare_nota(), 9)

        #validare nota
        nota = Nota(1, 1,1,0)
        self.assertRaises(EroriValidare, ValidatorNota.valideaza_nota, nota)
        nota = Nota(1, 1, 1, 11)
        self.assertRaises(EroriValidare, ValidatorNota.valideaza_nota, nota)

    def __RepoTests(self):
        repository = RepoStudenti()
        self.assertEqual(len(repository.get_all()),0)
        repository.adauga_student(Student(1, "Cosmin", 211))
        self.assertEqual(len(repository.get_all()), 1)
        self.assertEqual(repository.get_all(), [Student(1,"Cosmin", 211)])
        repository.adauga_student(Student(2, "Alin", 212))
        self.assertEqual(len(repository.get_all()), 2)
        self.assertEqual(repository.get_all(), [Student(1,"Cosmin", 211), Student(2, "Alin", 212)])
        repository.sterge_student_dupa_id(2)
        self.assertEqual(repository.get_all(), [Student(1,"Cosmin", 211)])
        repository.modifica_student(Student(1, "Adrian", 212))
        self.assertEqual(repository.get_all(), [Student(1,"Adrian", 212)])
        repository.sterge_student_dupa_id(1)

        repository = RepoLaboratoare()
        self.assertEqual(len(repository.get_all()),0)
        repository.adauga_laborator(Laborator(1, "enuntpb", 1, 12, 2023))
        repository.adauga_laborator(Laborator(2, "enunt2", 2, 12, 2023))
        self.assertEqual(len(repository.get_all()),2)
        self.assertEqual(repository.get_all(), [Laborator(1, "enuntpb", 1, 12, 2023), Laborator(2, "enunt2", 2, 12, 2023)])
        repository.sterge_laborator(2)
        self.assertEqual(repository.get_all(), [Laborator(1, "enuntpb", 1, 12, 2023)])
        repository.modifica_laborator(Laborator(1, "Assigment", 2, 10, 2022))
        self.assertEqual(repository.get_all(), [Laborator(1, "Assigment", 2, 10, 2022)])
        repository.sterge_laborator(1)

        repository = RepoNote()
        self.assertEqual(len(repository.get_all()),0)
        repository.adauga_nota(Nota(1,1,1,10))
        self.assertEqual(len(repository.get_all()),1)
        self.assertEqual(repository.get_all(), [Nota(1,1,1,10)])


    def __ServiceTests(self):

        self.repostud = RepoStudenti()
        self.validstud = ValidatorStudent()
        self.service = ServiceStudent(self.validstud, self.repostud)
        self.servicestud = ServiceStudent(self.validstud, self.repostud)
        self.assertEqual(len(self.service.get_all()),0)
        self.service.adauga_student(1, "ziana", 211)
        self.service.adauga_student(2, "andreea", 213)
        self.service.adauga_student(3, "larian", 215)
        self.assertEqual(len(self.service.get_all()),3)

        self.repolab = RepoLaboratoare()
        self.validlab = ValidatorLaborator()
        self.service = ServiceLaborator(self.validlab, self.repolab)
        self.servicelab = ServiceLaborator(self.validlab, self.repolab)
        self.assertEqual(len(self.service.get_all()),0)
        self.service.adauga_laborator_service(1,"enunt",1,2,2023)

        self.repo = RepoNote()
        self.valid = ValidatorNota()
        self.service = ServiceNote(self.valid, self.repostud, self.repolab, self.repo)
        self.assertEqual(len(self.service.get_all()),0)
        self.service.adauga_nota(1, 1, 1,10)
        self.assertEqual(self.service.get_all(), [Nota(1,1,1,10)])

        self.service.adauga_nota(2, 2, 1, 4)
        self.service.adauga_nota(3, 3, 1, 10)
        self.assertEqual(len(self.service.get_all()),3)

    def ruleaza_teste(self):
        self.__DomainValidatorsTests()
        self.__RepoTests()
        self.__ServiceTests()
        print("Teste rulate cu succes")

