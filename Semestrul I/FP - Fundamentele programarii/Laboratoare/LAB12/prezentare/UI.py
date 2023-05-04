from erori.exceptions import EroriValidare, RepoError


class UI():

    def __init__(self, service_student, service_laborator, service_note):
        self.__service_studenti = service_student
        self.__service_laboratoare = service_laborator
        self.__service_note = service_note
        print("""
                Scrie o comanda:
                adauga_student  - Adauga student (ID Nume Grupa)
                modifica_student - Modifica student
                sterge_student - Sterge student dupa ID
                adauga_laborator - Adauga laborator (ID Enunt Zi Luna An)
                modifica_laborator - Modifica laborator
                sterge_laborator - Sterge laborator dupa ID
                adauga_nota - Adauga o nota (ID IDstud IDlab Nota)
                studenti_restantieri - Afiseaza o lista cu studentii restantieri
                sorteaza_dupa_nume - Sorteaza dupa nume notele studentilor la un laborator dat (dupa ID)
                sorteaza_dupa_nota - Sorteaza dupa nota notele studentilor la un laborator dat (dupa ID)
                nota_frecventa - Afiseaza cea mai frecventa nota luata de studenti
                sorteaza_dupa_medie - QuickSort pe note
                sorteaza_gnome - Sorteaza dupa nume gnome
                exit - Paraseste aplicatia
                """)
        self.__comenzi = {
            "adauga_student": self.__ui_adauga_student,
            "cauta_student": self.__ui_cauta_student,
            "modifica_student": self.__ui_modifica_student,
            "sterge_student": self.__ui_sterge_student,
            "adauga_laborator": self.__ui_adauga_laborator,
            "cauta_laborator": self.__ui_cauta_laborator,
            "modifica_laborator": self.__ui_modifica_laborator,
            "sterge_laborator": self.__ui_sterge_laborator,
            "adauga_nota": self.__ui_adauga_nota,
            "studenti_restantieri": self.__ui_studenti_restantieri,
            "nota_frecventa": self.__ui_nota_frecventa,
            "sorteaza_dupa_nume": self.__ui_sorteaza_dupa_nume,
            "sorteaza_dupa_medie": self.__ui_sorteaza_dupa_medie,
            "sorteaza_gnome": self.__ui_sorteaza_gnome,
            "recursiv": self.__ui_recursiv,
            "exit": self.__ui_exit

        }


    #student

    def __ui_adauga_student(self):
        if len(self.__params) != 3:
            print("numar parametri invalid!")
            return
        id_student = int(self.__params[0])
        nume = self.__params[1]
        grupa = int(self.__params[2])
        self.__service_studenti.adauga_student(id_student, nume, grupa)
        print("student adaugat cu succes")

    def __ui_cauta_student(self):
        if len(self.__params) != 1:
            print("numar parametrii invalid")
            return
        id_student = int(self.__params[0])
        student = self.__service_studenti.cauta_student_dupa_id(id_student)
        print(student)

    def __ui_modifica_student(self):
        if len(self.__params) != 3:
            print("numar parametrii invalid")
            return
        id_student = int(self.__params[0])
        nume_nou = self.__params[1]
        grupa_noua = int(self.__params[2])
        self.__service_studenti.modifica_student(id_student, nume_nou, grupa_noua)
        print("student modificat cu succes")

    def __ui_sterge_student(self):
        if len(self.__params) != 1:
            print("numar parametrii invalid")
            return
        id_student = int(self.__params[0])
        self.__service_note.sterge_student(id_student)
        print(f"student cu idul {id_student} si notele lui sters cu succes!\n")

    #laborator

    def __ui_adauga_laborator(self):
        if len(self.__params) != 5:
            print("numar parametrii invalid")
            return
        id_laborator = self.__params[0]
        descriere_laborator = self.__params[1]
        zi = self.__params[2]
        luna = self.__params[3]
        an = self.__params[4]
        self.__service_laboratoare.adauga_laborator_service(id_laborator, descriere_laborator, zi, luna, an)
        print("laborator adaugat cu succes")

    def __ui_cauta_laborator(self):
        if len(self.__params) !=1:
            print("numar parametrii invalid")
            return
        id_laborator = self.__params[0]
        laborator = self.__service_laboratoare.cauta_laborator_dupa_id(id_laborator)
        print(laborator)

    def __ui_modifica_laborator(self):
        if len(self.__params) != 5:
            print("numar parametrii invalid")
            return
        id_laborator = self.__params[0]
        descriere_noua_laborator = self.__params[1]
        zi_noua = self.__params[2]
        luna_noua = self.__params[3]
        an_nou = self.__params[4]
        self.__service_laboratoare.modifica_laborator(id_laborator, descriere_noua_laborator, zi_noua, luna_noua, an_nou)
        print("laborator modificat cu succes")

    def __ui_sterge_laborator(self):
        if len(self.__params) != 1:
            print("numar parametrii invalid")
            return
        id_laborator = self.__params[0]
        self.__service_note.sterge_laborator(id_laborator)
        print("laborator sters cu succes")

    #nota
    def __ui_adauga_nota(self):
        if len(self.__params) != 4:
            print("numar parametrii invalid")
            return
        id_nota = int(self.__params[0])
        id_student = int(self.__params[1])
        id_laborator = int(self.__params[2])
        valoare_nota = int(self.__params[3])

        self.__service_note.adauga_nota(id_nota, id_laborator, id_student, valoare_nota)
        print("nota adaugata cu succes")

    #rapoarte si sortari
    def __ui_sorteaza_dupa_medie(self):
        if len(self.__params) != 0:
            print("numar parametrii invalid")
            return

        studenti = self.__service_note.sorteaza_dupa_medie()
        for student in studenti:
            print(student)

    def __ui_sorteaza_gnome(self):
        if len(self.__params) != 0:
            print("numar parametrii invalid")
            return

        studenti = self.__service_note.sorteaza_dupa_nume_gnome()
        for student in studenti:
            print(student)

    def __ui_sorteaza_dupa_nume(self):
        if len(self.__params) != 1:
            print("numar parametrii invalid")
            return
        id_laborator = int(self.__params[0])
        studenti = self.__service_note.sorteaza_dupa_nume(id_laborator)
        for student in studenti:
            print(student)

    def __ui_nota_frecventa(self):
        if len(self.__params) != 0:
            print("numar parametrii invalid")
            return
        nota = self.__service_note.nota_frecventa()
        print(nota)

    def __ui_sorteaza_quicksort(self):
        if len(self.__params) !=0:
            print("nr params invalid")
            return
        studenti = self.__service_note.sorteaza_dupa_nume2()
        for student in studenti:
            print(student)

    def __ui_studenti_restantieri(self):
        if len(self.__params) != 0:
            print("numar parametrii invalid")
            return
        restantieri = self.__service_note.studenti_restantieri()
        for restantier in restantieri:
            print(restantier)

    #exit

    def __ui_recursiv(self):
        if len(self.__params)!=0:
            print("Nr invalid")
            return

        medie = self.__service_note.note_student()
        print(medie)
    def __ui_exit(self):
        if len(self.__params)!=0:
            print("numar parametrii invalid")
            return
        exit()

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
                except EroriValidare as ve:
                    print(f"Valid Error:{ve}")
                except RepoError as re:
                    print(f"Repo Error:{re}")
            else:
                print("comanda invalida")
