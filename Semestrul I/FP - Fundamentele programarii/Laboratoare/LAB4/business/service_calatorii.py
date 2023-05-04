from domain.calatorie import creeaza_calatorie, set_zi_inceput_calatorie, set_luna_inceput_calatorie, \
    set_an_inceput_calatorie, set_zi_sfarsit_calatorie, set_luna_sfarsit_calatorie, set_an_sfarsit_calatorie, \
    set_destinatie_calatorie, set_pret_calatorie
from infrastructura.repository_calatorii import adauga_calatorie_lista, numar_calatorii_lista, get_all_calatorii_lista
from validatoare.validare_calatorie import valideaza_calatoria


def adauga_calatorie_service(l,l_undo,id_calatorie, zi_inceput, luna_inceput, an_inceput, zi_sfarsit, luna_sfarsit, an_sfarsit, destinatie, pret):
    '''
    pe baza datelor despre calatorie va crea o calatorie, va incerca
    sa o valideze si daca e valida, va incerca sa o adauge
    in lista l de calatorii unic identificabile prin idul lor intreg
    daca nu exista deja o calatorie cu acelasi id in lista
    :param l: lista de calatorii unic identificabile prin idul lor intreg
    :param id_calatorie:int
    :param zi_inceput: int
    :param luna_inceput: int
    :param an_inceput: int
    :param zi_sfarsit: int
    :param luna_sfarsit: int
    :param an_sfarsit: int
    :param destinatie: string
    :param pret: float
    :return: -
    :raises ValueError - idul calatoriei <=0, se concateneaza stringul "id invalid!\n" la codul de eroare
        - ziua de inceput/sfarsit este in afara intervalului [1,31], se concateneaza stringul "zi de inceput / final invalida!\n" la codul de eroare
        - luna de inceput/sfarsit este in afara intervalului [1,12],
        - anul de inceput > anul de sfarsit
        - anul inceput = anul de sfarsit, luna de inceput > luna de sfarsit
    '''

    l_undo.append(l[:])
    calatorie=creeaza_calatorie(id_calatorie, zi_inceput, luna_inceput, an_inceput, zi_sfarsit, luna_sfarsit, an_sfarsit, destinatie, pret)
    valideaza_calatoria(calatorie)
    adauga_calatorie_lista(l,calatorie)

def numar_calatorii_service(l):
    '''
    returneaza numarul de calatorii din lista l de calatorii unic identificabile prin idul intreg
    :param l: lista de calatorii unic identificabile prin idul lor intreg
    :return: rez: int - numarul de calatorii din lista
    '''
    return numar_calatorii_lista(l)

def get_all_calatorii_service(l):
    '''
    returneaza lista tuturor calatoriilor
    :param l: lista de calatorii
    :return: rez: lista de calatorii
    '''
    return get_all_calatorii_lista(l)

def set_calatorie(l, l_undo, id, zi_inceput_noua, luna_inceput_noua, an_inceput_nou, zi_sfarsit_noua, luna_sfarsit_noua, an_sfarsit_nou, destinatie_noua, pret_nou):
    calatorie_noua = creeaza_calatorie(id, zi_inceput_noua,luna_inceput_noua,an_inceput_nou,zi_sfarsit_noua,luna_sfarsit_noua,an_sfarsit_nou,destinatie_noua,pret_nou)

    i=0
    for calatorie in l:
        if id == calatorie[0]:
            break
        else:
            i=i+1

    l_undo.append(l[:])
    calatorie_noua[:] = l[i]
    set_zi_inceput_calatorie(calatorie_noua,zi_inceput_noua)
    set_luna_inceput_calatorie(calatorie_noua,luna_inceput_noua)
    set_an_inceput_calatorie(calatorie_noua,an_inceput_nou)
    set_zi_sfarsit_calatorie(calatorie_noua,zi_sfarsit_noua)
    set_luna_sfarsit_calatorie(calatorie_noua,luna_sfarsit_noua)
    set_an_sfarsit_calatorie(calatorie_noua,an_sfarsit_nou)
    set_destinatie_calatorie(calatorie_noua,destinatie_noua)
    set_pret_calatorie(calatorie_noua,pret_nou)
    l[i] = calatorie_noua