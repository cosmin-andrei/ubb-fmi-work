class Laborator:

    def __init__(self, id_laborator, descriere, zi_deadline, luna_deadline, an_deadline, student):
        self.__id_laborator = id_laborator
        self.__descriere = descriere
        self.__zi_deadline = zi_deadline
        self.__luna_deadline = luna_deadline
        self.__an_deadline = an_deadline
        self.__student = student
        self.__sters = False

    def get_id_laborator(self):
        return self.__id_laborator

    def get_student(self):
        return self.__student

    def get_descriere(self):
        return self.__descriere

    def get_zi_deadline(self):
        return self.__zi_deadline

    def get_luna_deadline(self):
        return self.__luna_deadline

    def get_an_deadline(self):
        return self.__an_deadline

    def set_descriere(self, descriere):
        self.__descriere = descriere

    def set_zi_deadline(self, zi_deadline):
        self.__zi_deadline = zi_deadline

    def set_luna_deadline(self, luna_deadline):
        self.__luna_deadline = luna_deadline

    def set_an_deadline(self, an_deadline):
        self.__an_deadline = an_deadline

    def __eq__(self, other):
        return self.__id_laborator == other.__id_laborator

    def sterge(self):
        self.__sters = True
