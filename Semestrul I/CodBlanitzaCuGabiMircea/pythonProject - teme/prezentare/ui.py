from business.service_teme import get_all_teme_service, adauga_tema_service
from domeniu.tema import to_string_tema
from infrastructura.repository_teme import numar_teme_lista


def ui_adauga_tema(l,params):
    if len(params)!=3:
        print("numar parametrii invalid!")
        return
    id_tema = int(params[0])
    cod_tema = params[1]
    pret = float(params[2])
    adauga_tema_service(l,id_tema,cod_tema,pret)

def ui_printeaza_lista_teme(l,params):
    if(len(params)!=0):
        print("numar parametri invalid!")
        return
    if numar_teme_lista(l)==0:
        print("nu exista teme introduse!")
        return
    teme = get_all_teme_service(l)
    for tema in teme:
        print(to_string_tema(tema))


def ruleaza_ui():
    teme = []
    comenzi = {
        "adauga_tema":ui_adauga_tema,
        "printeaza_lista_teme":ui_printeaza_lista_teme
    }
    while True:
        comanda = input(">>>")
        comanda = comanda.strip()
        if comanda == "":
            continue
        if comanda == "exit":
            return
        parti = comanda.split()
        nume_comanda = parti[0]
        params = parti[1:]
        for param in params:
            param = param.strip()
        if nume_comanda in comenzi:
            try:
                comenzi[nume_comanda](teme,params)
            except ValueError as ve:
                print(ve)
        else:
            print("comanda invalida!")