class ValidareExamen:

    @staticmethod
    def valideaza_examen(examen):
        '''
        functia valideaza un examen
        :param examen: examen
        :return: ValueError - daca exista erori
        '''
        erori = ""
        if examen.get_data == "":
            erori += "data invalida\n"

        data = examen.get_data()
        parti = data.split(".")
        if parti[0] > "31" or parti[0] < "1":
            erori += "data invalida\n"

        elif parti[1]<"0" or parti[1]>"12":
            erori += "data invalida\n"

        if examen.get_ora() == "":
            erori += "ora invalida\n"

        ora = examen.get_ora()
        parti = ora.split(":")
        if parti[0] > "24" or parti[1]<"0" or parti[1]>"60":
            erori += "ora invalida\n"

        if examen.get_materie() == "":
            erori += "materie invalida\n"

        if examen.get_tip() != "normala" and examen.get_tip() != "restanta":
            erori += "tip invalid\n"

        if len(erori)>0:
            raise ValueError(erori)