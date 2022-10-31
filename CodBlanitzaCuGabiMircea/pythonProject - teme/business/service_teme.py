from domeniu.tema import creeaza_tema
from infrastructura.repository_teme import numar_teme_lista, adauga_tema_lista, get_all_teme_lista
from validatoare.validator_tema import valideaza_tema


def adauga_tema_service(l,id_tema,cod_tema,pret):
    '''
    pe baza idului intreg id_tema, a codului string cod_tema si a floatului pret
    va crea o tema, va incerca sa o valideze si daca e valida
    va incerca sa o adauge in lista l de teme unic identificabile prin idul lor intreg
    daca nu exista deja o tema cu acelasi id in lista
    :param l: lista de teme unic identificabile prin idul lor intreg
    :param id_tema: int
    :param cod_tema: string
    :param pret: float
    :return: - (daca teme este valida si nu exista deja o alta tema cu acelasi id in lista l)
    :raises ValueError -daca idul int al temei <0, se concateneaza stringul "id invalid\n" la codul de eroare
                        daca codul string al temei == "", se concateneaza stringul "cod invalid\n" la codul de eroare
                        daca pretul float al temei <=0, se concateneaza stringul "pret invalid\n" la codul de eroare
                        - daca cel putin unul dintre atributele temei este invalid
                       daca exista o tema cu idul id_tema in lista l, se arunca exceptie de tipul ValueErorr cu mesajul codului de eroare
    '''

    tema = creeaza_tema(id_tema,cod_tema,pret)
    valideaza_tema(tema)
    adauga_tema_lista(l,tema)

def numar_teme_service(l):
    '''
    returneaza numarul de teme din lista l de teme unic identificabile prin idul lor intreg
    :param l: lista de teme unic identificabile prin idul lor intreg
    :return: rez: int - numarul de teme din lista
    '''
    return numar_teme_lista(l)

def get_all_teme_service(l):
    '''
    returneaza lista tuturor temelor
    :param l: lista de teme
    :return: rez: lista de teme
    '''
    return get_all_teme_lista(l)