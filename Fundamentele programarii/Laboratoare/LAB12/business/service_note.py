from domain.nota import Nota
from domain.student import SortStudentNume


class ServiceNote:

    def __init__(self, validator_nota, repo_studenti, repo_laboratoare, repo_note):
        self.__validator_nota = validator_nota
        self.__repo_studenti = repo_studenti
        self.__repo_laboratoare = repo_laboratoare
        self.__repo_note = repo_note

    def adauga_nota(self, id_nota, id_laborator, id_student, valoare_nota):
        '''
        noteaza laboratorul unui student
        :param id_nota: int id_nota
        :param id_laborator: int
        :param id_student: int
        :param valoare_nota: int
        :return: -
        '''
        nota = Nota(id_nota, id_student, id_laborator, valoare_nota)
        self.__repo_note.adauga_nota(nota)

    def get_all(self):
        return self.__repo_note.get_all()

    # stergeri

    def sterge_laborator(self, id_laborator):
        '''
        sterge laborator dupa id_laborator
        :param id_laborator: int
        :return: -
        '''
        laborator = self.__repo_laboratoare.cauta_laborator_dupa_id(id_laborator)
        note = self.__repo_note.get_all()
        note_student = [x for x in note if x.get_id_laborator() == laborator.get_id_laborator()]
        for nota_student in note_student:
            self.__repo_note.sterge_nota_dupa_id(nota_student.get_id_nota())
        self.__repo_studenti.sterge_student_dupa_id(id_laborator)

    def sterge_student(self, id_student):
        '''
        sterge toate notele studentului dupa id student
        :param id_student: int
        :return:-
        '''

        student = self.__repo_studenti.cauta_student_dupa_id(id_student)
        note = self.__repo_note.get_all()
        note_student = [x for x in note if x.get_id_student() == student.get_id_student]
        for nota_student in note_student:
            self.__repo_note.sterge_nota_dupa_id(nota_student.get_id_nota())
        self.__repo_studenti.sterge_student_dupa_id(id_student)

    def medie_student(self, id_student):
        '''
        calculeaza media notelor unui student
        :param id_student: int
        :return: float - medie
        '''
        note = self.__repo_note.get_all()
        s = 0
        k = 0

        for nota in note:
            if nota.get_id_student() == id_student:
                s += nota.get_valoare_nota()
                k += 1

        s = float(s / k)

        return float(s)

    def studenti_restantieri(self):
        '''
        returneaza o lista cu studentii restantieri
        :return: lista cu studentii care au media laboratoarelor sub 5
        '''

        studenti = self.__repo_studenti.get_all()
        restantieri = []
        for student in studenti:
            id_student = student.get_id_student()
            medie = self.medie_student(id_student)
            if self.medie_student(id_student) < 5:
                student = self.__repo_studenti.cauta_student_dupa_id(id_student)
                nume_student = student.get_nume()
                studentDTO = SortStudentNume(nume_student, medie)
                restantieri.append(studentDTO)
        return restantieri

    def sorteaza_dupa_nume(self, id_laborator):
        '''
        sorteaza dupa nume notele de la un lab al studentilor
        :param id_laborator: int
        :return: lista note
        '''
        note = self.__repo_note.get_all()
        infoStudenti = {}
        for nota in note:
            id_lab_2 = nota.get_id_laborator()
            if id_lab_2 == id_laborator:
                valoare_nota = nota.get_valoare_nota()
                id_student = nota.get_id_student()
                infoStudenti[id_student] = valoare_nota

        studenti = []
        for id_student in infoStudenti:
            student = self.__repo_studenti.cauta_student_dupa_id(id_student)
            nume = student.get_nume()
            val_nota = infoStudenti[id_student]
            studentDTO = SortStudentNume(nume, val_nota)
            studenti.append(studentDTO)

        def key(student1, student2):
            if student1.get_nume() > student2.get_nume():
                return True
            elif student1.get_nume() < student2.get_nume():
                return False
            else:
                return student1.get_id_student() > student2.get_id_student()

        studenti.sort(key=lambda x: x.get_nume(), reverse=False)


    def sorteaza_dupa_nume_gnome(self):
        '''
        sorteaza studentii dupa numele lor
        :return: lista studenti
        '''

        l = [(student.get_nume(), self.medie_student(student.get_id_student())) for student in self.__repo_studenti.get_all()]

        n = len(l)
        i = 0

        while i < n:
            if i == 0:
                i = i + 1
            if l[i][0] < l[i - 1][0]:
                i = i + 1
            elif l[i][0] == l[i - 1][0]:
                if l[i][1] < l[i - 1][1]:
                    l[i], l[i - 1] = l[i - 1], l[i]
                i = i + 1
            else:
                l[i], l[i - 1] = l[i - 1], l[i]
                i = i - 1

        self.gnomesort(l)
        return l

    def sorteaza_dupa_medie(self):
        '''
        sorteaza studentii dupa mediile studentilor
        :return: lista studenti si medie
        '''

        l = [(self.medie_student(student.get_id_student()), student.get_nume()) for student in self.__repo_studenti.get_all()]

        n = len(l)
        i = 0

        while i < n:
            if i == 0:
                i = i + 1
            if l[i][0] < l[i - 1][0]:
                i = i + 1
            elif l[i][0] == l[i - 1][0]:
                if l[i][1] < l[i - 1][1]:
                    l[i], l[i - 1] = l[i - 1], l[i]
                i = i + 1
            else:
                l[i], l[i - 1] = l[i - 1], l[i]
                i = i - 1

        self.quicksort(l)
        l.reverse()
        return l

    def quicksort(self, list):
        if len(list) < 2:
            return list

        poz = 0

        for i in range(1, len(list)):
            if list[i] <= list[0]:
                poz += 1
                temp = list[i]
                list[i] = list[poz]
                list[poz] = temp

        temp = list[0]
        list[0] = list[poz]
        list[poz] = temp

        left = self.quicksort(list[0:poz])
        right = self.quicksort(list[poz + 1:len(list)])

        lista = left + [list[poz]] + right

        return lista

    def gnomesort(self, lista):

        n = len(lista)
        index = 0
        while index < n:
            if index == 0:
                index = index + 1
            if lista[index] >= lista[index - 1]:
                index = index + 1
            else:
                lista[index], lista[index - 1] = lista[index - 1], lista[index]
                index = index - 1

        return lista



    def nota_frecventa(self):
        '''
        returneaza nota frecventa
        :return: int-nota frecventa
        '''
        note = self.__repo_note.get_all()
        frecventa = {
            1: 0,
            2: 0,
            3: 0,
            4: 0,
            5: 0,
            6: 0,
            7: 0,
            8: 0,
            9: 0,
            10: 0
        }
        for nota in note:
            valoare_nota = nota.get_valoare_nota()
            frecventa[valoare_nota] = 1+frecventa[valoare_nota]

        maxim = 0
        i = 1
        fr_maxim = 0

        while i <= 10:
            if frecventa[i] > fr_maxim:
                maxim = i
                fr_maxim = frecventa[i]
            i += 1

        return maxim