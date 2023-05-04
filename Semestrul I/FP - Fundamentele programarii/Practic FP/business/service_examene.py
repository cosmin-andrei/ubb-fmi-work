from domain.examen import Examen
import datetime

class ServiceExamene:

    def __init__(self, repository, validator):
        self.__repo = repository
        self.__validator = validator

    def adauga_examen(self, data, ora, materie, tip):
        '''
        adauga examen in fisier si repo
        :param data: string
        :param ora: string
        :param materie: string
        :param tip: string
        :return: -
        '''
        examen = Examen(data, ora, materie, tip)
        self.__validator.valideaza_examen(examen)
        self.__repo.adauga_examen(examen)

    def get_all(self):
        '''
        returneaza toate examenele programate
        :return: lista de examene programate
        '''
        return self.__repo.get_all()


    def data_de_azi(self):
        '''
        functia returneaza o lista cu examenele programate ziua urmatoare
        :return: lista cu examenele programate ziua urmatoare
        '''
        data = datetime.date.today()
        lista_examene=[]
        examene = self.__repo.get_all()
        for examen in examene:
            data_examen = examen.get_data()
            parti = data_examen.split(".")
            if parti[0] == str(data.day+1):
                if parti[1][0] == "0":
                    if parti[1][1] == str(data.month):
                        lista_examene.append(examen)
                elif parti[1][0] == str(data.month):
                    lista_examene.append(examen)

        lista_examene = sorted(lista_examene, key=lambda x: x.get_ora())
        return lista_examene

    def tabel(self, data):
        '''
        functia returneaza o lista cu examenele programate pe trei zile
        :param data: string
        :return: lista cu examenele programate pe 3 zile
        '''
        lista_examene = []
        parti_data = data.split(".")
        examene = self.__repo.get_all()
        for examen in examene:
            data_examen = examen.get_data()
            parti_dataex = data_examen.split(".")
            if parti_dataex[1] == parti_data[1]:
                if int(parti_dataex[0]) == int(parti_data[0]):
                    lista_examene.append(examen)
                elif int(parti_dataex[0]) == int(parti_data[0])+1:
                    lista_examene.append(examen)
                elif int(parti_dataex[0]) == int(parti_data[0])+2:
                    lista_examene.append(examen)


        return lista_examene


    def export(self, __cale_catre_fisier, lista_materii):
        '''
        functia exporta intr-un fisier examenele pe care le doreste utilizatorul
        :param __cale_catre_fisier: string - nume fisier
        :param lista_materii: lista
        :return: -
        '''
        examene = self.__repo.get_all()
        lista_export=[]
        materii = lista_materii.split()
        for examen in examene:
            if examen.get_materie() in materii:
                lista_export.append(examen)

        lista_export = sorted(lista_export, key=lambda x:(x.get_data(), x.get_ora()))

        with open(__cale_catre_fisier, "w") as f:
            for examen in lista_export:
                f.write(str(examen))

