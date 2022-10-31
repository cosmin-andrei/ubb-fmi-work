def creeaza_tema(id_tema, cod_tema, pret):
    '''
    creeaza o tema cu idul intreg id_tema, cu codul string cod_tema, si pretul float pret
    :param id_tema: int
    :param cod_tema: string
    :param pret: float
    :return: tema cu idul int id_tema cu codul string cod_tema si pretul float pret
    '''
    return [id_tema, cod_tema, pret]


def get_id_tema(tema):
    '''
    returneaza idul intreg al temei tema
    :param tema: tema
    :return: rez: int - idul intreg al temei tema
    '''
    return tema[0]


def get_cod_tema(tema):
    '''
    returneaza codul string al temei tema
    :param tema: tema
    :return: rez: string - codul temei tema
    '''
    return tema[1]


def get_pret(tema):
    '''
    returneaza pretul float al temei tema (in lei)
    :param tema: tema
    :return: rez: float - pretul temei tema
    '''
    return tema[2]


def set_pret(tema, pret_nou):
    '''
    seteaza pretul float al temei tema la floatul pret_nou
    :param tema: tema
    :param pret_nou: float
    :return: - (tema va avea pretul nou)
    '''
    tema[2] = pret_nou


def egal_teme(tema_a, tema_b):
    '''
    verifica daca tema tema_a si tema tema_b sunt egale adica au acelasi id intreg
    :param tema_a: tema
    :param tema_b: tema
    :return: rez:bool - True daca tema_a si tema_b sunt aceeasi tema adica au acelasi id intreg unic
                        False altfel
    '''
    return get_id_tema(tema_a) == get_id_tema(tema_b)


def to_string_tema(tema):
    '''
    genereaza stringul pentru pretty printingul temei tema
    :param tema: tema: tema
    :return: rez: string = [id_tema]cod_tema=>pret
    '''
    return f"[{get_id_tema(tema)}]{get_cod_tema(tema)}=>{get_pret(tema)}"