from business.service_note import ServiceNote
from business.service_studenti import ServiceStudenti
from domain.nota import Nota
from domain.student import Student
from infrastructura.repo_note import RepoNote
from infrastructura.repo_studenti import RepoStudenti
from validatoare.validator_nota import ValidatorNota
from validatoare.validator_student import ValidatorStudent


class Teste:

    def __init__(self):
        self.__id_student = 1
        self.__nume_student = "Andrei Cosmin"
        self.__grupa_student = 211
        self.__student = Student(self.__id_student, self.__nume_student, self.__grupa_student)
        self.__validator_student = ValidatorStudent()

        #student gresit
        self.__id_student_gresit = -1
        self.__nume_student_gresit = ""
        self.__grupa_student_gresita = 0
        self.__student_gresit = Student(self.__id_student_gresit, self.__nume_student_gresit, self.__grupa_student_gresita)
        self.__validator_student_gresit = ValidatorStudent()

        #nota gresita
        self.__id_nota_gresit = -1
        self.__val_nota_gresita = 11
        self.__nota_gresita = Nota(self.__id_nota_gresit, self.__student, self.__val_nota_gresita)
        self.__validator_nota_gresita = ValidatorNota()

        #acelasi student
        self.__acelasi_id_student = 1
        self.__alt_nume_student = "diana onosa"
        self.__alt_grupa_student = 221
        self.__acelasi_id_alt_student = Student(self.__acelasi_id_student, self.__alt_nume_student, self.__alt_grupa_student)

        # aceeasi nota
        self.__acelasi_id_nota = 1
        self.__alta_nota = 10
        self.__acelasi_id_alta_nota = Nota(self.__acelasi_id_nota, self.__student, self.__alta_nota)


        #repo
        self.__repo_studenti = RepoStudenti()

        #service
        self.__service_studenti = ServiceStudenti(self.__validator_student,self.__repo_studenti)

        #nota
        self.__id_nota = 1
        self.__valoare_nota = 9
        self.__nota = Nota(self.__id_nota, self.__student, self.__valoare_nota)
        self.__validator_nota = ValidatorNota()
        self.__repo_note = RepoNote()
        self.__service_note = ServiceNote(self.__validator_nota, self.__repo_note, self.__repo_studenti)


    def __teste_domain_student(self):
        assert (self.__id_student == self.__student.get_id_student())
        assert (self.__nume_student == self.__student.get_nume())
        assert (self.__grupa_student == self.__student.get_grupa())

    def __teste_validator_student(self):
        self.__validator_student.valideaza_student(self.__student)
        try:
            self.__validator_student_gresit.valideaza_student(self.__student_gresit)
            assert False
        except ValueError as ve:
            assert(str(ve)== "id invalid\nnume invalid\ngrup invalida\n")

    def __teste_repo_student(self):
        assert(len(self.__repo_studenti.get_all()) == 0)
        self.__repo_studenti.adauga_student(self.__student)
        assert (len(self.__repo_studenti.get_all()) == 1)
        try:
            self.__repo_studenti.adauga_student(self.__acelasi_id_alt_student)
            assert False
        except ValueError as ve:
            assert(str(ve) == "student existent!")

        self.__repo_studenti.sterge_student_dupa_id(self.__id_student)
        assert (len(self.__repo_studenti.get_all()) == 0)

        self.__repo_studenti.adauga_student(self.__student)
        assert (len(self.__repo_studenti.get_all()) == 1)
        self.__repo_studenti.removeAll()
        assert(len(self.__repo_studenti.get_all()) == 0)

    def __teste_business_student(self):
        assert(len(self.__service_studenti.get_all_studenti()) == 0)
        self.__service_studenti.adauga_student(self.__id_student, self.__nume_student, self.__grupa_student)
        assert (len(self.__service_studenti.get_all_studenti()) == 1)

    def __teste_domain_note(self):
        assert (self.__id_nota == self.__nota.get_id_nota())
        assert (self.__valoare_nota == self.__nota.get_valoare_nota())

    def __teste_validator_nota(self):
        self.__validator_nota.valideaza_nota(self.__nota)
        try:
            self.__validator_nota_gresita.valideaza_nota(self.__nota_gresita)
            assert False
        except ValueError as ve:
            assert (str(ve) == "id invalid\nnota invalida\n")

    def __teste_repo_note(self):
        assert (len(self.__repo_note.get_all()) == 0)
        self.__repo_note.adauga_nota(self.__nota)
        assert (len(self.__repo_note.get_all()) == 1)
        try:
            self.__repo_note.adauga_nota(self.__acelasi_id_alta_nota)
            assert False
        except ValueError as ve:
            assert (str(ve) == "nota existenta!")

        self.__repo_note.sterge_nota_dupa_id(self.__id_nota)
        assert (len(self.__repo_note.get_all()) == 0)

        self.__repo_note.adauga_nota(self.__nota)
        assert (len(self.__repo_note.get_all()) == 1)
        self.__repo_note.removeAll()
        assert (len(self.__repo_note.get_all()) == 0)

    def __teste_service_note(self):
        self.__service_note.adauga_nota_service(self.__id_student, self.__id_nota, self.__valoare_nota)
        assert(len(self.__repo_note.get_all()) == 1)
        self.__service_note.sterge_student_si_notele_lui(self.__id_student)
        assert (len(self.__repo_note.get_all()) == 0)



    def ruleaza_teste(self):
        self.__teste_domain_student()
        self.__teste_validator_student()
        self.__teste_repo_student()
        self.__teste_business_student()
        self.__teste_domain_note()
        self.__teste_validator_nota()
        self.__teste_repo_note()
        self.__teste_service_note()
        print("toate testele au mers bine")
