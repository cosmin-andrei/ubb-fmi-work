class UI:

    def __init__(self, service):
        self.__service = service
        self.__comenzi={
            "adauga_examen": self.__ui_adauga_examen,
            "vezi_examene": self.__ui_vezi_examene,
            "export": self.__ui_export,
            "tabel": self.__ui_tabel
        }
        self.__data_programari = 0

    def __ui_adauga_examen(self):
        '''
        adauga examenul
        :return: -
        '''
        if len(self.__params) != 4:
            print("numar parametrii invalid")
            return

        data = self.__params[0]
        ora = self.__params[1]
        materie = self.__params[2]
        tip = self.__params[3]
        self.__service.adauga_examen(data, ora, materie, tip)
        print("examen adaugata cu succes")

        if self.__data_programari !=0:
            examene = self.__service.tabel(self.__data_programari)
            for examen in examene:
                print(examen)

    def __ui_vezi_examene(self):
        '''
        afiseaza pe ecran toate examenele programate
        :return: -
        '''
        if len(self.__params) != 0:
            print("numar parametrii invalid")
            return

        examene = self.__service.get_all()
        for examen in examene:
            print(examen)


    def __ui_export(self):
        '''
        functia apeleaza functia export din Service pentru a exporta examene intr-un fisier
        :return: -
        '''
        if len(self.__params) != 2:
            print("numar parametrii invalid")
            return

        cale_catre_fisier = self.__params[0]
        lista = self.__params[1]
        self.__service.export(cale_catre_fisier, lista)
        print("exportat cu succes")

    def __ui_afiseaza_examene(self):
        '''
        afiseaza pe ecran examenele programate ziua urmatoare
        :return:
        '''
        examene = self.__service.data_de_azi()
        for examen in examene:
            print(examen)

    def __ui_tabel(self):
        '''
        afiseaza un tabel pe ecran cu toate examenele programate cu 2 zile
        :return: -
        '''
        if len(self.__params) != 1:
            print("numar parametrii invalid")
            return

        self.__data_programari = self.__params[0]
        examene = self.__service.tabel(self.__data_programari)
        for examen in examene:
            print(examen)


    def run(self):
        self.__ui_afiseaza_examene()
        meniu ="""
            1. adauga_examen - Adauga un examen
            2. vezi_examene - Vezi examene
            3. export - Exporta examene in fisier
            4. tabel - Afiseaza examenele pe 3 zile
            """
        print(meniu)
        while True:
            comanda = input(">>>")
            comanda.strip()
            if comanda == "":
                continue
            if comanda == "exit":
                exit()
            parti = comanda.split(",")
            nume_comanda = parti[0]
            self.__params = parti[1:]
            if nume_comanda in self.__comenzi:
                try:
                    self.__comenzi[nume_comanda]()
                except ValueError as ve:
                    print(str(ve))

