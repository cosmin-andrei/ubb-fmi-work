from domain.calatorie import get_an_inceput, get_an_sfarsit, get_luna_inceput, get_luna_sfarsit, get_zi_sfarsit, \
    get_zi_inceput, get_destinatie, get_pret


def cautare_datesejur(l,zi_inceput,luna_inceput,an_inceput,zi_sfarsit,luna_sfarsit,an_sfarsit):
    '''
    returneaza pachetele de calatorie care se afla intr-un anumit interval de timp dat
    :param l: lista de calatorii unic identificabile prin id
    :param calatorie: calatorie
    :param zi_inceput: int
    :param luna_inceput: int
    :param an_inceput: int
    :param zi_sfarsit: int
    :param luna_sfarsit: int
    :param an_sfarsit: int
    :return: lista cu pachetele de calatorie care se afla intr-un anumit interval de timp dat
    '''
    lista={}
    for calatorie in l:
        if get_an_inceput(l[calatorie])>an_inceput and get_an_sfarsit(l[calatorie])<an_sfarsit:
            lista[calatorie] = l[calatorie]
        elif get_an_inceput(l[calatorie]) == an_inceput and get_an_sfarsit(l[calatorie]) == an_sfarsit:
            if get_luna_inceput(l[calatorie])>luna_inceput and get_luna_sfarsit(l[calatorie])<luna_sfarsit:
                lista[calatorie] = l[calatorie]
            elif get_luna_inceput(l[calatorie])==luna_inceput and get_luna_sfarsit(l[calatorie])==luna_sfarsit:
                if get_zi_inceput(l[calatorie])>=zi_inceput and get_zi_sfarsit(l[calatorie])<=zi_sfarsit:
                    lista[calatorie] = l[calatorie]
    return lista


def cautare_destinatie_pret(l,destinatie,pret):
    '''
    returneaza pachetele de calatorie cu o anumita destinatie si pret mai mic decat un pret dat
    :param l: lista cu calatorii unic identificabile prin id unic tip int
    :param calatorie: calatorie
    :param destinatie: string
    :param pret: float
    :return: lista cu calatorii cu o anumita destinatie si pret mai mic decat un pret dat
    '''

    lista = {}
    for calatorie in l:
        if get_destinatie(l[calatorie]) == destinatie and get_pret(l[calatorie])<pret:
            lista[calatorie] = l[calatorie]
    return lista

def cautare_datasf(l,zi_sfarsit,luna_sfarsit,an_sfarsit):
    '''
    returneaza pachetele de calatorii cu o anumita data de sfarsit
    :param l: lista de calatorii unic identificabile prin id unic tip int
    :param calatorie: calatorie
    :param zi_sfarsit: int
    :param luna_sfarsit: int
    :param an_sfarsit: int
    :return: lista cu calatorii cu o anumita data de sfarsit\
    '''

    lista={}
    for calatorie in l:
        if get_zi_sfarsit(l[calatorie])==zi_sfarsit and get_luna_sfarsit(l[calatorie])==luna_sfarsit and get_an_sfarsit(l[calatorie])==an_sfarsit:
            lista[calatorie] = l[calatorie]

    return lista
