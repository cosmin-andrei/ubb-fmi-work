from business.service_calatorii import adauga_calatorie_service, get_all_calatorii_service
from domain.calatorie import set_zi_inceput_calatorie
from infrastructura.repository_calatorii import numar_calatorii_lista


def ui_adauga_calatorie(l,params):
    if len(params)!=9:
        print("numar parametrii invalid!")
        return
    id_calatorie = int(params[0])
    zi_inceput = params[1]
    luna_inceput = params[2]
    an_inceput = params[3]
    zi_sfarsit = params[4]
    luna_sfarsit = params[5]
    an_sfarsit = params[6]
    destinatie = params[7]
    pret = float(params[8])
    adauga_calatorie_service(l,id_calatorie,zi_inceput,luna_inceput,an_inceput,zi_sfarsit,luna_sfarsit,an_sfarsit,destinatie,pret)


def ui_printeaza_lista_calatorii(l,params):
    if (len(params) != 0):
        print("numar parametri invalid!")
        return
    if numar_calatorii_lista(l) == 0:
        print("nu exista calatorii introduse!")
        return
    calatorii = get_all_calatorii_service(l)
    for calatorie in calatorii:
        print(calatorie,"\n")


def ui_modifica_calatorie_comanda():
    print("""
    1. Ziua de inceput
    2. Ziua de sfarsit
    3. Luna de inceput
    3. Luna de sfarsit
    4. Anul de inceput
    5. Anul de sfarsit
    6. Destinatia
    7. Pretul""")
    comanda=int(input("Ce doresti sa modifici? Introdu numarul comenzii:"))
    return comanda

def ui_modifica_calatorie(l,params):
    id=input("Ce calatorie vrei sa modifici?")
    calatorii = get_all_calatorii_service(l)
    for calatorie in calatorii:
        if id == calatorie[0]:
            comanda= ui_modifica_calatorie_comanda()
            if comanda == 1:
                zi_noua=int(input("ziua noua:"))
                set_zi_inceput_calatorie()
            elif comanda == 2:
                pass



def ui_sterge_calatorii(l,params):
    pass


def ui_cauta_calatorii(l,params):
    pass


def ui_filtreaza_calatorii(l,params):
    pass


def ui_rapoarte_calatorii(l,params):
    pass


def ui_undo(l,params):
    pass


def ruleaza_ui():
    calatorii = []
    comenzi={
        "adauga_calatorie":ui_adauga_calatorie,
        "printeaza_calatoriile":ui_printeaza_lista_calatorii,
        "modifica_calatorie": ui_modifica_calatorie,
        "sterge_calatorii": ui_sterge_calatorii,
        "cauta_calatorii": ui_cauta_calatorii,
        "filtreaza_calatorii": ui_filtreaza_calatorii,
        "rapoarte_calatorii": ui_rapoarte_calatorii,
        "undo": ui_undo
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
                comenzi[nume_comanda](calatorii,params)
            except ValueError as ve:
                print(ve)
        else:
            print("comanda invalida!")