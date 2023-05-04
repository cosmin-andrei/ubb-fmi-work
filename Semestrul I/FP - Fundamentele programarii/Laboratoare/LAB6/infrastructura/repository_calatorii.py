from domain.calatorie import egal_calatorii


def adauga_calatorie_lista(l, calatorie):
    '''
    incearca sa adauge calatoria calatorie in lista l de calatorii unic identificabile prin idul intreg
    daca nu exista deja o calatorie in lista l cu acelasi id
    :param l: lista de calatorii unic identificabile prin idul lor intreg
    :param calatorie: calatorie
    :return: - ( l' = l U {calatorie} daca nu exista calatorie cu acelasi id in lista l)
    :raises: ValueError : arunca exceptie de tipul ValueError cu mesajul string "calatorie invalida!\n"
    '''
    for _calatorie in l:
        if egal_calatorii(_calatorie,calatorie):
            raise ValueError("calatorie invalida!\n")
    l.append(calatorie)

def numar_calatorii_lista(l):
    '''
    returneaza numarul de calatorii din lista l de calatorii unic identificabile prin id calatorie
    :param l: lista cu calatorii unic identificabile
    :return: int - numarul de calatorii din lista l de calatorii
    '''
    return len(l)

def get_all_calatorii_lista(l):
    '''
    returneaza lista tuturor calatoriilor
    :param l: lista de calatorii
    :return: rez: lista de calatorii
    '''
    return l[:]