from domeniu.tema import egal_teme


def adauga_tema_lista(l, tema):
    '''
    incearca sa adauge tema tema in lista l de teme unic identificabile prin idul intreg
    daca nu exista deja o tema in lista l cu acelasi id
    :param l: lista de teme unic identificabile prin idul lor intreg
    :param tema: tema
    :return: - ( l' = l U {tema} daca nu exista tema cu acelasi id in lista l)
    :raises: ValueError : arunca exceptie de tipul ValueError cu mesajul string "tema invalida!\n"
    '''
    for _tema in l:
        if egal_teme(_tema,tema):
            raise ValueError("tema invalida!\n")
    l.append(tema)

def numar_teme_lista(l):
    '''
    returneaza numarul de teme din lista l de teme unic identificabile prin idul lor intreg
    :param l: lista de teme unic identificabile prin idul lor intreg
    :return: rez: int - numarul de teme din lista
    '''
    return len(l)

def get_all_teme_lista(l):
    '''
    returneaza lista tuturor temelor
    :param l: lista de teme
    :return: rez: lista de teme
    '''
    return l[:]