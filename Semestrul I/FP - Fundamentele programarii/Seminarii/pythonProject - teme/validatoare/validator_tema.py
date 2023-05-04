from domeniu.tema import get_id_tema, get_cod_tema, get_pret


def valideaza_tema(tema):
    '''
    verifica daca idul int al temei este >=0, codul string al temei nu e vid si pretul float al temei este >=0.0
    :param tema: tema
    :return: -(daca tema este valida)
    :raises ValueError -daca idul int al temei <0, se concateneaza stringul "id invalid\n" la codul de eroare
                        daca codul string al temei == "", se concateneaza stringul "cod invalid\n" la codul de eroare
                        daca pretul float al temei <=0, se concateneaza stringul "pret invalid\n" la codul de eroare
                        - daca cel putin unul dintre atributele temei este invalid
                        se arunca exceptie de tipul ValueErorr cu mesajul codului de eroare
    '''

    erori = ""
    if get_id_tema(tema)<0:
        erori += "id invalid!\n"
    if get_cod_tema(tema) == "":
        erori += "cod invalid!\n"
    if get_pret(tema) <= 0.0:
        erori += "pret invalid!\n"
    if len(erori) > 0:
        raise ValueError(erori)
