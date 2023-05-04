from business.service_calatorii import *
from infrastructura.cautare_calatorii import *
from infrastructura.filtrare_calatorii import *
from infrastructura.rapoarte_calatorii import *
from infrastructura.repository_calatorii import *
from infrastructura.stergere_calatorii import *
from infrastructura.undo import undo


#Lista calatorii
def ui_printeaza_lista_calatorii(l,l_undo,params):
    if (len(params) != 0):
        print("numar parametri invalid!")
        return
    if numar_calatorii_lista(l) == 0:
        print("nu exista calatorii introduse!")
        return
    calatorii = get_all_calatorii_service(l)
    for calatorie in calatorii:
        print(calatorie,"\n")

# 1.Adaugari
def ui_adauga_calatorie(l,l_undo,params):
    if len(params) != 9:
        print("Numar de parametrii invalid!")
        return
    id_calatorie = int(params[0])
    zi_inceput = int(params[1])
    luna_inceput = int(params[2])
    an_inceput = int(params[3])
    zi_sfarsit = int(params[4])
    luna_sfarsit = int(params[5])
    an_sfarsit = int(params[6])
    destinatie = params[7]
    pret = float(params[8])
    adauga_calatorie_service(l,l_undo,id_calatorie,zi_inceput,luna_inceput,an_inceput,zi_sfarsit,luna_sfarsit,an_sfarsit,destinatie,pret)
    print("calatorie adaugata cu succes")

def ui_modifica_calatorie(l,l_undo,params):
    if len(params) != 9:
        print("Numar de parametri invalid")
        return

    id_calatorie = int(params[0])
    zi_inceput_noua = int(params[1])
    luna_inceput_noua = int(params[2])
    an_inceput_noua = int(params[3])
    zi_sfarsit_noua = int(params[4])
    luna_sfarsit_noua = int(params[5])
    an_sfarsit_nou = int(params[6])
    destinatie_noua = params[7]
    pret_nou = float(params[8])

    set_calatorie(l,l_undo,id_calatorie,zi_inceput_noua,luna_inceput_noua,an_inceput_noua,zi_sfarsit_noua,luna_sfarsit_noua,an_sfarsit_nou,destinatie_noua,pret_nou)
    print("Calatorie modificata cu succes!")

#2. Stergeri
def ui_sterge_pachete_destinatie(l, l_undo,params):
    if len(params) != 1:
        print("Numar de parametri invalid")
        return

    destinatie = params[0]
    stergere_destinatie(l,l_undo,destinatie)
    print("stergere efectuata cu succes")

def ui_sterge_pachete_durata(l,l_undo,params):
    if len(params) != 1:
        print("Numar de parametri invalid")
        return

    numar_zile = int(params[0])
    stergere_nrzile(l,l_undo,numar_zile)
    print("stergere efectuata cu succes")


def ui_sterge_pachete_pret(l,l_undo,params):
    if len(params) != 1:
        print("Numar de parametri invalid")
        return

    pret = float(params[0])
    stergere_pret(l,l_undo,pret)
    print("stergere efectuata cu succes")

#3. Cautari
def ui_tipareste_pachete_interval(l,l_undo,params):
    if len(params) != 6:
        print("Numar de parametri invalid")
        return

    zi_inceput = int(params[0])
    luna_inceput = int(params[1])
    an_inceput = int(params[2])
    zi_sfarsit = int(params[3])
    luna_sfarsit = int(params[4])
    an_sfarsit = int(params[5])
    print(cautare_datesejur(l,zi_inceput,luna_inceput,an_inceput,zi_sfarsit,luna_sfarsit,an_sfarsit))

def ui_tipareste_pachete_destinatie(l, l_undo,params):
    if len(params) != 2:
        print("Numar de parametri invalid")
        return
    destinatie=params[0]
    pret=float(params[1])
    print(cautare_destinatie_pret(l,destinatie,pret))

def ui_tipareste_pachete_datasf(l,l_undo,params):
    if len(params) != 3:
        print("Numar de parametri invalid")
        return

    zi_sfarsit=int(params[0])
    luna_sfarsit=int(params[1])
    an_sfarsit=int(params[2])
    print(cautare_datasf(l,zi_sfarsit,luna_sfarsit,an_sfarsit))

# 4. Rapoarte
def ui_raport_destinatie(l,l_undo,params):
    if len(params) != 1:
        print("Numar de parametri invalid")
        return

    destinatie=params[0]
    print(rapoarte_destinatie(l,destinatie))

def ui_raport_perioada(l,l_undo,params):
    if len(params) != 6:
        print("Numar de parametri invalid")
        return
    zi_inceput = int(params[0])
    luna_inceput = int(params[1])
    an_inceput = int(params[2])
    zi_sfarsit = int(params[3])
    luna_sfarsit = int(params[4])
    an_sfarsit = int(params[5])
    print(rapoarte_perioada(l,zi_inceput,luna_inceput,an_inceput,zi_sfarsit,luna_sfarsit,an_sfarsit))


def ui_raport_mediepret(l,l_undo,params):
    if len(params) != 1:
        print("Numar de parametri invalid")
        return

    destinatie=params[0]
    print(rapoarte_mediepret(l, destinatie))


# 5. Filtrari
def ui_filtrare_pretdestinatie(l,l_undo,params):
    if len(params) != 2:
        print("Numar de parametri invalid")
        return

    pret=float(params[0])
    destinatie=params[1]
    print(filtrare_pret_destinatie(l,destinatie,pret))


def ui_filtrare_luna(l,l_undo,params):
    if len(params) != 1:
        print("Numar de parametri invalid")
        return

    luna=int(params[0])
    print(filtrare_luna(l,luna))


def ui_undo(l,l_undo,params):
    if len(params) != 0:
        print("Numar de parametri invalid")
        return
    undo(l,l_undo)
    print("undo efectuat cu succes!")

def menu():
    print("""
    1. Adauga pachet de calatorie (adauga_calatorie)
    2. Modifica un pachet de calatorie (modifica_calatorie)
    3. Ștergerea tuturor pachetelor de călătorie disponibile pentru o destinație dată (sterge_pachete_destinatie)
    4. Sterge pachete cu o durata mai scurta decat un numar de zile dat (sterge_pachete_durata)
    5. Sterge pachetele cu pret mai mare decat o suma data (sterge_pachete_pret)
    6. Tipărirea pachetelor de călătorie care presupun un sejur într-un interval dat (tipareste_pachete_interval)
    7. Tipărirea pachetelor de călătorie cu o destinație dată și cu preț mai mic decât o sumă dată (tipareste_pachete_destinatie)
    8. Tipărirea pachetelor de călătorie cu o anumită dată de sfârșit (tipareste_pachete_datasf)
    9. Tipărirea numărului de oferte pentru o destinație dată. (raport_destinatie)
    10. Tipărirea tuturor pachetelor disponibile într-o anumită perioadă citită de la tastatură în ordinea crescătoare a prețului (raport_pachete_datasf)
    11. Tipărirea mediei de preț pentru o destinație dată (raport_mediepret)
    12. Eliminarea ofertelor care au un preț mai mare decât cel dat și o destinație diferită de cea citită de la tastatură (filtrare_pret_destinatie)
    13. Eliminarea ofertelor în care sejurul presupune zile dintr-o anumită lună (filtrare_luna)
    14. Refacerea ultimei operații (undo)
    15. Printeaza lista ofertelor (print_oferte)
    """)

def ruleaza_ui():
    calatorii = []
    l_undo=[]
    menu()
    while True:
        comenzi={
        "adauga_calatorie":ui_adauga_calatorie,
        "modifica_calatorie": ui_modifica_calatorie,
        "sterge_pachete_destinatie": ui_sterge_pachete_destinatie,
        "sterge_pachete_durata": ui_sterge_pachete_durata,
        "sterge_pachete_pret": ui_sterge_pachete_pret,
        "tipareste_pachete_interval": ui_tipareste_pachete_interval,
        "tipareste_pachete_destinatie": ui_tipareste_pachete_destinatie,
        "tipareste_pachete_datasf": ui_tipareste_pachete_datasf,
        "raport_destinatie": ui_raport_destinatie,
        "raport_perioada": ui_raport_perioada,
        "raport_mediepret": ui_raport_mediepret,
        "filtrare_pret_destinatie": ui_filtrare_pretdestinatie,
        "filtrare_luna": ui_filtrare_luna,
        "undo": ui_undo,
        "print_oferte": ui_printeaza_lista_calatorii
        }

        comanda = str(input(">>>"))
        comanda = comanda.strip()
        if comanda == "":
            continue
        if comanda == "exit":
            return
        parti = comanda.split()
        nume_comanda = parti[0]
        params = parti[1:]
        if nume_comanda in comenzi:
            try:
                comenzi[nume_comanda](calatorii, l_undo, params)
            except ValueError as ve:
                print(ve)
        else:
            print("comanda invalida!")