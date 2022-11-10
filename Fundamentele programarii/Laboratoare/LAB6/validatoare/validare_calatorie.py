from domain.calatorie import get_id_calatorie, get_zi_inceput, get_zi_sfarsit, get_luna_inceput, get_luna_sfarsit, \
    get_an_inceput, get_an_sfarsit, get_destinatie, get_pret


def valideaza_calatoria(calatorie):
    '''
    verifica daca:
        - idul calatoriei este mai mare decat 0
        - ziua de inceput si sfarsit este un numar cuprins intre 1 si 31
        - luna de inceput si sfarsit este cuprinsa intre 1 si 12
        - anul de inceput este mai mic sau egal cu cel de sfarsit
            - daca este egal luna de inceput este mai mica sau egala cu luna de sfarsit
                - daca sunt egale, ziua de inceput este mai mica sau egala cu cea de sfarsit
        - destinatia calatoriei nu este vida
        - pretul float al calatoriei>0
    :param calatorie: calatorie
    :return: ValueError
        - idul calatoriei <=0, se concateneaza stringul "id invalid!\n" la codul de eroare
        - ziua de inceput/sfarsit este in afara intervalului [1,31], se concateneaza stringul "zi de inceput / final invalida!\n" la codul de eroare
        - luna de inceput/sfarsit este in afara intervalului [1,12],
        - anul de inceput > anul de sfarsit
        - anul inceput = anul de sfarsit, luna de inceput > luna de sfarsit
    '''

    erori=""
    if get_id_calatorie(calatorie)<=0:
        erori += "id invalid!\n"
    if get_zi_inceput(calatorie)<1:
        erori += "zi inceput invalida!\n"
    if get_luna_inceput(calatorie)<1 or get_luna_inceput(calatorie)>12:
        erori += "luna inceput invalida!\n"
    if get_zi_sfarsit(calatorie)>31:
        erori += "zi sfarsit invalid!\n"
    if get_luna_sfarsit(calatorie)>12 or get_luna_sfarsit(calatorie)<1:
        erori += "luna sfarsit invalid!\n"
    if get_an_inceput(calatorie)>get_an_sfarsit(calatorie):
        erori += "anul este invalid!\n"
    elif get_luna_inceput(calatorie)>get_luna_sfarsit(calatorie):
        erori += "luna este invalida!\n"
    elif get_zi_inceput(calatorie)>get_zi_sfarsit(calatorie):
        erori += "ziua este invalida!\n"
    if get_destinatie(calatorie)=="":
        erori += "destinatia este invalida!\n"
    if get_pret(calatorie)<=0.0:
        erori += "pret invalid!\n"

    if len(erori) > 0:
        raise ValueError(erori)