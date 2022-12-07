from erori.repo_error import RepoError
from erori.validation_error import ValidError


class UI():

    def __init__(self, service_studenti, service_note):
        self.__service_studenti = service_studenti
        self.__service_note = service_note
        self.__comenzi = {
            "adauga_student": self.__ui_adauga_student,
            "print_studenti": self.__ui_print_studenti,
            "modifica_student": self.__ui_modifica_student,
            "sterge_student_si_notele_lui": self.__ui_sterge_student_si_note,
            "adauga_student_random": self.__ui_adauga_student_random,
        }

    def __ui_modifica_student(self):
        if len(self.__params) != 3:
            print("numar parametrii invalid")
            return
        id_student = int(self.__params[0])
        nume_nou = self.__params[1]
        grupa_noua = int(self.__params[2])
        self.__service_studenti.modifica_student(id_student, nume_nou, grupa_noua)
        print("student modificat cu succes")
    def __ui_adauga_student_random(self):
        if len(self.__params) !=1:
            print("numar parametrii invalid")
            return

        k = int(self.__params[0])

        while k !=0:
            id_random = self.__service_studenti.genereaza_id_random()
            nume_random = self.__service_studenti.genereaza_nume_random()
            grupa_random = self.__service_studenti.genereaza_grupa_random()
            self.__service_studenti.adauga_student(id_random, nume_random, grupa_random)
            k = k - 1

        print("studenti random adaugati cu succes")

    def __ui_sterge_student_si_note(self):
        if len(self.__params) != 0:
            print("numar parametrii invalid")
            return
        id_student = int(self.__params[0])
        self.__service_note.sterge_student_si_notele_lui()
        print(f"student cu idul {id_student} si notele lui sters cu succes!\n")



    def __ui_print_studenti(self):
        if len(self.__params) != 0:
            print("numar parametrii invalid")
            return
        studenti = self.__service_studenti.get_all_studenti()
        if len(studenti) == 0:
            print("nu exista studenti adaugati")
            return
        for student in studenti:
            print(student)

    def __ui_adauga_student(self):
        if len(self.__params) != 3:
            print("numar parametri invalid!")
            return
        id_student = int(self.__params[0])
        nume = self.__params[1]
        grupa = int(self.__params[2])
        self.__service_studenti.adauga_student(id_student, nume, grupa)
        print("student adaugat cu succes")

    def run(self):
        while True:
            comanda = input(">>>")
            comanda = comanda.strip()
            if comanda == "":
                continue
            if comanda == "exit":
                return
            parti = comanda.split()
            nume_comanda = parti[0]
            self.__params = parti[1:]
            if nume_comanda in self.__comenzi:
                try:
                    self.__comenzi[nume_comanda]()
                except ValueError:
                    print("UI error: tip numeric invalid")
                except ValidError as ve:
                    print(f"Valid Error:{ve}")
                except RepoError as re:
                    print(f"Repo Error:{re}")
            else:
                print("comanda invalida")
