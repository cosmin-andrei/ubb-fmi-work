def filtrare_pret_destinatie(l,destinatie,pret):
    '''
    returneaza o lista cu calatoriile care au o destinatie diferita de string destinatie si un pret mai mare de float pret
    :param l: lista cu calatorii unic identificabile prin id int
    :param calatorie: calatorie
    :param destinatie: string
    :param pret: float
    :return: returneaza lista de calatorii cu o destinatie diferita de string destinatie si un pret mai mare de float pret
    '''

    lista=[]
    for calatorie in l:
        if calatorie[7]!=destinatie and calatorie[8]>pret:
            lista.append(calatorie)
    return lista

def filtrare_luna(l,luna):
    '''
    returneaza calatoriile care sunt din afara lunii luna int
    :param l: lista cu calatorii unic identificabile prin id intreg
    :param calatorie: calatorie
    :param luna: int
    :return: returneaza lista de calatorii cu conditia indeplinita
    '''

    lista=[]
    for calatorie in l:
        if luna != calatorie[2] and luna != calatorie[5]:
            lista.append(calatorie)
    return lista