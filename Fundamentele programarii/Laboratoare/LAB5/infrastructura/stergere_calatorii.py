from domain.calatorie import get_destinatie, get_zi_sfarsit, get_zi_inceput, get_pret
from infrastructura.repository_calatorii import get_all_calatorii_lista


def stergere_destinatie(l,calatorie,destinatie):
    '''
    sterge calatoriile cu o anumita destinatie din lista l
    :param l: lista cu calatorii unic identificabile prin id int
    :param calatorie: calatorie
    :param destinatie: string
    :return: -
    '''

    de_sters = {}
    for calatorie in l:
        if get_destinatie(l[calatorie]) == destinatie:
            de_sters[calatorie] = l[calatorie]

    for calatorie in de_sters.keys():
        if calatorie in l:
            del l[calatorie]

def stergere_nrzile(l,calatorie,numar_zile):
    '''
    sterge calatoriile cu un numar mai mic de zile decat numar_zile din lista l
    :param l: lista cu calatorii unic identificabile prin id int
    :param calatorie: calatorie
    :param numar_zile: int
    :return: -
    '''

    de_sters = {}
    for calatorie in l:
        if abs(get_zi_sfarsit(l[calatorie])-get_zi_inceput(l[calatorie]))<numar_zile:
            de_sters[calatorie] = l[calatorie]

    for calatorie in de_sters.keys():
        if calatorie in l:
            del l[calatorie]


def stergere_pret(l,calatorie,pret):
    '''
    sterge calatoriile cu pretul mai mare decat float pret din lista l
    :param l: lista de calatorii unic identificabile prin id int
    :param calatorie: calatorie
    :param pret: float
    :return: -
    '''

    de_sters={}
    for calatorie in l:
        if get_pret(l[calatorie])>pret:
            de_sters[calatorie] = l[calatorie]

    for calatorie in de_sters.keys():
        if calatorie in l:
            del l[calatorie]

