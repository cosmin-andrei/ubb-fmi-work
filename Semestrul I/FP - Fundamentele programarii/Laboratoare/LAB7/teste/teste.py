from business.service_studenti import ServiceStudenti
from domain.student import Student
from infrastructura import repo_studenti
from infrastructura.repo_studenti import RepoStudenti
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

        #acelasi student
        self.__acelasi_id_student = 1
        self.__alt_nume_student = "diana onosa"
        self.__alt_grupa_student = 221
        self.__acelasi_id_alt_student = Student(self.__acelasi_id_student, self.__alt_nume_student, self.__alt_grupa_student)

        #repo
        self.__repo_studenti = RepoStudenti()

        #service
        self.__service_studenti = ServiceStudenti(self.__validator_student,self.__repo_studenti)

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

        #de adaugat cautarea
        assert(self.__repo_studenti.cauta_student_dupa_id(1) == self.__student)

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


    def ruleaza_teste(self):
        self.__teste_domain_student()
        self.__teste_validator_student()
        self.__teste_repo_student()
        self.__teste_business_student()
        print("toate testele au mers bine")
