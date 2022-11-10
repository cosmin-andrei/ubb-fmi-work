from business.service_calatorii import *
from infrastructura.cautare_calatorii import *
from infrastructura.filtrare_calatorii import *
from infrastructura.rapoarte_calatorii import *
from infrastructura.repository_calatorii import *
from infrastructura.stergere_calatorii import *
from infrastructura.undo import undo


#Lista calatorii
def ui_printeaza_lista_calatorii(l):

    if numar_calatorii_lista(l) == 0:
        print("nu exista calatorii introduse!")
        return
    calatorii = get_all_calatorii_service(l)
    for calatorie in calatorii:
        print(calatorie,"\n")

# 1.Adaugari
def ui_adauga_calatorie(l,l_undo):
    id_calatorie = int(input("id "))
    zi_inceput = int(input("zi "))
    luna_inceput = int(input("luna "))
    an_inceput = int(input("an "))
    zi_sfarsit = int(input("zi "))
    luna_sfarsit = int(input("luna "))
    an_sfarsit = int(input("an "))
    destinatie = input("destinatie ")
    pret = float(input("pret "))
    adauga_calatorie_service(l,l_undo,id_calatorie,zi_inceput,luna_inceput,an_inceput,zi_sfarsit,luna_sfarsit,an_sfarsit,destinatie,pret)
    print("calatorie adaugata cu succes")

def ui_modifica_calatorie(l,l_undo):

    id_calatorie = int(input("id "))
    zi_inceput_noua = int(input("zi "))
    luna_inceput_noua = int(input("luna "))
    an_inceput_nou = int(input("an "))
    zi_sfarsit_noua = int(input("zi "))
    luna_sfarsit_noua = int(input("luna "))
    an_sfarsit_nou = int(input("an "))
    destinatie_noua = input("destinatie ")
    pret_nou = float(input("pret "))

    set_calatorie(l,l_undo,id_calatorie,zi_inceput_noua,luna_inceput_noua,an_inceput_nou,zi_sfarsit_noua,luna_sfarsit_noua,an_sfarsit_nou,destinatie_noua,pret_nou)
    print("Calatorie modificata cu succes!")

#2. Stergeri
def ui_sterge_pachete_destinatie(l, l_undo):
    destinatie = input("destinatie ")
    stergere_destinatie(l,l_undo,destinatie)
    print("stergere efectuata cu succes")

def ui_sterge_pachete_durata(l,l_undo):
    numar_zile = int(input("numar zile "))
    stergere_nrzile(l,l_undo,numar_zile)
    print("stergere efectuata cu succes")


def ui_sterge_pachete_pret(l,l_undo):
    pret = float(input("pret "))
    stergere_pret(l,l_undo,pret)
    print("stergere efectuata cu succes")

#3. Cautari
def ui_tipareste_pachete_interval(l):
    zi_inceput = int(input("zi "))
    luna_inceput = int(input("luna "))
    an_inceput = int(input("an "))
    zi_sfarsit = int(input("zi "))
    luna_sfarsit = int(input("luna "))
    an_sfarsit = int(input("an "))
    print(cautare_datesejur(l,zi_inceput,luna_inceput,an_inceput,zi_sfarsit,luna_sfarsit,an_sfarsit))

def ui_tipareste_pachete_destinatie(l):
    destinatie=input("destinatie ")
    pret=float(input("pret "))
    print(cautare_destinatie_pret(l,destinatie,pret))

def ui_tipareste_pachete_datasf(l):
    zi_sfarsit = int(input("zi "))
    luna_sfarsit = int(input("luna "))
    an_sfarsit = int(input("an "))
    print(cautare_datasf(l,zi_sfarsit,luna_sfarsit,an_sfarsit))

# 4. Rapoarte
def ui_raport_destinatie(l):
    destinatie=input("destinatie ")
    print(rapoarte_destinatie(l,destinatie))

def ui_raport_perioada(l):
    zi_inceput = int(input("zi "))
    luna_inceput = int(input("luna "))
    an_inceput = int(input("an "))
    zi_sfarsit = int(input("zi "))
    luna_sfarsit = int(input("luna "))
    an_sfarsit = int(input("an "))
    print(rapoarte_perioada(l,zi_inceput,luna_inceput,an_inceput,zi_sfarsit,luna_sfarsit,an_sfarsit))


def ui_raport_mediepret(l):
    destinatie = input("destinatie ")
    print(rapoarte_mediepret(l, destinatie))


# 5. Filtrari
def ui_filtrare_pretdestinatie(l):
    pret=float(input("pret "))
    destinatie=input("destinatie ")
    print(filtrare_pret_destinatie(l,destinatie,pret))


def ui_filtrare_luna(l):
    luna=int(input("luna "))
    print(filtrare_luna(l,luna))


def ui_undo(l,l_undo):
    undo(l,l_undo)
    print("undo efectuat cu succes!")

def menu():
    print("""
    1. Adauga pachet de calatorie
    2. Modifica un pachet de calatorie
    3. Ștergerea tuturor pachetelor de călătorie disponibile pentru o destinație dată
    4. Sterge pachete cu o durata mai scurta decat un numar de zile dat
    5. Sterge pachetele cu pret mai mare decat o suma data
    6. Tipărirea pachetelor de călătorie care presupun un sejur într-un interval dat
    7. Tipărirea pachetelor de călătorie cu o destinație dată și cu preț mai mic decât o sumă dată
    8. Tipărirea pachetelor de călătorie cu o anumită dată de sfârșit
    9. Tipărirea numărului de oferte pentru o destinație dată.
    10. Tipărirea tuturor pachetelor disponibile într-o anumită perioadă citită de la tastatură în ordinea crescătoare a prețului 
    11. Tipărirea mediei de preț pentru o destinație dată
    12. Eliminarea ofertelor care au un preț mai mare decât cel dat și o destinație diferită de cea citită de la tastatură
    13. Eliminarea ofertelor în care sejurul presupune zile dintr-o anumită lună
    14. Refacerea ultimei operații
    15. Printeaza lista ofertelor
    16. Exit
    """)

def ruleaza_ui():
    calatorii = []
    l_undo=[]
    menu()

    while True:

        c=int(input("Introdu numarul comenzii: "))

        if c==1:
            ui_adauga_calatorie(calatorii,l_undo)
        elif c==2:
            ui_modifica_calatorie(calatorii,l_undo)
        elif c==3:
            ui_sterge_pachete_destinatie(calatorii,l_undo)
        elif c==4:
            ui_sterge_pachete_durata(calatorii,l_undo)
        elif c==5:
            ui_sterge_pachete_pret(calatorii,l_undo)
        elif c==6:
            ui_tipareste_pachete_interval(calatorii)
        elif c==7:
            ui_tipareste_pachete_destinatie(calatorii)
        elif c==8:
            ui_tipareste_pachete_datasf(calatorii)
        elif c==9:
            ui_raport_destinatie(calatorii)
        elif c==10:
            ui_raport_perioada(calatorii)
        elif c==11:
            ui_raport_mediepret(calatorii)
        elif c==12:
            ui_filtrare_pretdestinatie(calatorii)
        elif c==13:
            ui_filtrare_luna(calatorii)
        elif c==14:
            ui_undo(calatorii,l_undo)
        elif c==15:
            ui_printeaza_lista_calatorii(calatorii)
        elif c==16:
            exit()
        else:
            print("comanda invalida!")