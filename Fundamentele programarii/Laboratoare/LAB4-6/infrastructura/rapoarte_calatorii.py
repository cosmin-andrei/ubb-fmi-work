def rapoarte_destinatie(l,calatorie,destinatie):
    '''
    returneaza numarul de calatorii cu o anumita destinatie string
    :param l: lista cu calatorii unic identificabile prin id tip int
    :param calatorie: calatorie
    :param destinatie: string 
    :return: int - numarul de calatorii cu o anumita destinatie string
    '''
    k=0
    for calatorie in l:
        if calatorie[7]==destinatie:
            k += 1
    return k

def rapoarte_perioada(l,calatorie,zi_inceput,luna_inceput,an_inceput,zi_sfarsit,luna_sfarsit,an_sfarsit):
    '''
    returneaza toate pachetele de calatorie disponibile intr-o perioada data, in ordine crescatoare a preturilor
    :param l: lista cu calatorii unic identificabile prin id int
    :param calatorie: calatorie
    :param zi_inceput:int
    :param luna_inceput:int
    :param an_inceput: int
    :param zi_sfarsit: int
    :param luna_sfarsit: int
    :param an_sfarsit: int
    :return: lista cu toate pachetele disponibile intr-o anumita perioada, ordonate in ordinea crescatoare a preturilor
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

    lista.sort(key=lambda calatorie: calatorie[8])
    return lista

def rapoarte_mediepret(l,calatorie,destinatie):
    '''
    returneaza media de pret a calatoriilor pentru o destinatie string data
    :param l: lista cu calatorii unic identificabile prin id int
    :param calatorie: calatorie
    :param destinatie: string
    :return: float - media de pret a calatoriilor pentru o destinatie string
    '''

    suma=0
    elemente=0
    for calatorie in l:
        if calatorie[7]==destinatie:
            suma += calatorie[8]
            elemente += 1
    return suma/elemente