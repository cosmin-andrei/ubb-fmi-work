from business import service_produse, service_vanzari
from exceptions.repo_error import RepoError
from exceptions.valid_error import ValidError


class UI:

    def __init__(self, service_produse, service_vanzari):
        self.__service_produse = service_produse
        self.__service_vanzari = service_vanzari
        self.__comenzi = {
            "cauta_tip": self.__ui_cauta_tip,
            "pret_total": self.__ui_pret_total
        }

    def __ui_cauta_tip(self):
        '''if len(self.__params) != 1:
            print("Numar parametrii invalid")
            return
        tip = self.__params[0]
        print(self.__service_produse.cauta_tip(tip))
        '''
        pass


    def __ui_pret_total(self):
        pass

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


