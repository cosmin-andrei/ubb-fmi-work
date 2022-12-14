from infrastructura.repository_calatorii import get_all_calatorii_lista


def stergere_destinatie(l,undolist,destinatie):
    '''
    sterge calatoriile cu o anumita destinatie din lista l
    :param l: lista cu calatorii unic identificabile prin id int
    :param calatorie: calatorie
    :param destinatie: string
    :return: -
    '''
    undolist.append(l[:])
    for calatorie in l:
        if calatorie[7] == destinatie:
            l.remove(calatorie)

    return l[:]

def stergere_nrzile(l,undolist,numar_zile):
    '''
    sterge calatoriile cu un numar mai mic de zile decat numar_zile din lista l
    :param l: lista cu calatorii unic identificabile prin id int
    :param calatorie: calatorie
    :param numar_zile: int
    :return: -
    '''

    undolist.append(l[:])
    for calatorie in l:
        if abs(calatorie[4]-calatorie[1])<numar_zile:
            l.remove(calatorie)

    return l[:]

def stergere_pret(l,undolist,pret):
    '''
    sterge calatoriile cu pretul mai mare decat float pret din lista l
    :param l: lista de calatorii unic identificabile prin id int
    :param calatorie: calatorie
    :param pret: float
    :return: -
    '''

    undolist.append(l[:])

    for calatorie in l:
        if calatorie[8]>pret:
            l.remove(calatorie)
    return l[:]