from erori.repo_error import RepoError
from erori.validation_error import ValidError


class UI():

    def __init__(self, service_studenti, service_laboratoare, service_note):
        self.__service_studenti = service_studenti
        self.__service_note = service_note
        self.__service_materii = service_laboratoare
        self.__comenzi = {
            "adauga_student": self.__ui_adauga_student,
            "print_studenti": self.__ui_print_studenti,
            "sterge_student_si_notele_lui": self.__ui_sterge_student_si_note,
        }

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
        if len(self.__params) != 2:
            print("numar parametri invalid!")
            return
        id_student = int(self.__params[0])
        nume = self.__params[1]
        self.__service_studenti.adauga_student(id_student, nume)
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
