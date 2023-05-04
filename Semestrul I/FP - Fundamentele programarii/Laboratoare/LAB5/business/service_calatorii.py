from domain.calatorie import creeaza_calatorie
from infrastructura.repository_calatorii import adauga_calatorie_lista
from validatoare.validare_calatorie import valideaza_calatoria


def adauga_calatorie_service(l,id_calatorie, zi_inceput, luna_inceput, an_inceput, zi_sfarsit, luna_sfarsit, an_sfarsit, destinatie, pret):
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

    calatorie=creeaza_calatorie(id_calatorie, zi_inceput, luna_inceput, an_inceput, zi_sfarsit, luna_sfarsit, an_sfarsit, destinatie, pret)
    valideaza_calatoria(calatorie)
    adauga_calatorie_lista(l,calatorie)