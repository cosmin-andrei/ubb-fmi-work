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
    lista=[]
    for calatorie in l:
        if calatorie[3]>an_inceput and calatorie[6]<an_sfarsit:
            lista.append(calatorie)
        elif calatorie[3] == an_inceput and calatorie[6] == an_sfarsit:
            if calatorie[2]>luna_inceput and calatorie[5]<luna_sfarsit:
                lista.append(calatorie)
            elif calatorie[2]==luna_inceput and calatorie[5]==luna_sfarsit:
                if calatorie[1]>=zi_inceput and calatorie[4]<=zi_sfarsit:
                    lista.append(calatorie)

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

    lista =[]
    for calatorie in l:
        if calatorie[7] == destinatie and calatorie[8]<pret:
            lista.append(calatorie)
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

    lista=[]
    for calatorie in l:
        if calatorie[4]==zi_sfarsit and calatorie[5]==luna_sfarsit and calatorie[6]==an_sfarsit:
            lista.append(calatorie)
    return lista