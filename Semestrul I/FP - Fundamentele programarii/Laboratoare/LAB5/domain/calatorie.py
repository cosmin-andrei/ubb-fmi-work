def creeaza_calatorie(id_calatorie, zi_inceput, luna_inceput, an_inceput, zi_sfarsit, luna_sfarsit, an_sfarsit, destinatie, pret):
    '''
    creeaza o calatrorie cu idul intreg id_calatorie, cu ziua int zi_inceput,
    luna int luna_inceput, an int an_inceput, zi int zi_sfarsit, luna int luna_sfarsit, an int an_sfarsit,
    destinatie string destinatie, pret float pret
    :param id_calatorie: int
    :param zi_inceput: int
    :param luna_inceput: int
    :param an_inceput: int
    :param zi_sfarsit: int
    :param luna_sfarsit: int
    :param an_sfarsit: int
    :param destinatie: string
    :param pret: float
    :return: calatroria cu idul intreg id_calatorie, cu ziua int zi_inceput,
    luna int luna_inceput, an int an_inceput, zi int zi_sfarsit, luna int luna_sfarsit, an int an_sfarsit,
    destinatie string destinatie, pret float pret
    '''

    return [id_calatorie, zi_inceput, luna_inceput, an_inceput, zi_sfarsit, luna_sfarsit, an_sfarsit, destinatie, pret]

def get_id_calatorie(calatorie):
    '''
    returneaza idul intreg al calatoriei calatorie
    :param calatorie: calatorie
    :return: rez: int - idul intreg al calatoriei
    '''
    return calatorie[0]

def get_zi_inceput(calatorie):
    '''
    returneaza ziua de inceput tip intreg al calatoriei calatorie
    :param calatorie: calatorie
    :return: int - ziua de inceput a calatoriei
    '''
    return calatorie[1]

def get_luna_inceput(calatorie):
    '''
    returneaza luna de inceput tip intreg al calatoriei calatorie
    :param calatorie: calatorie
    :return: int - luna de inceput a calatoriei
    '''
    return calatorie[2]

def get_an_inceput(calatorie):
    '''
    returneaza anul de inceput tip intreg a calatoriei calatorie
    :param calatorie: calatorie
    :return: int - anul de inceput a calatoriei
    '''
    return calatorie[3]

def get_zi_sfarsit(calatorie):
    '''
    returneaza ziua de sfarsit tip intreg a calatoriei calatorie
    :param calatorie: calatorie
    :return: int - ziua de sfarsit a calatoriei
    '''
    return calatorie[4]

def get_luna_sfarsit(calatorie):
    '''
    returneaza luna de sfarsit tip intreg a calatoriei calatorie
    :param calatorie: calatorie
    :return: int - luna de sfarsit a calatoriei
    '''
    return calatorie[5]

def get_an_sfarsit(calatorie):
    '''
    returneaza anul de sfarsit tip intreg a calatoriei calatorie
    :param calatorie: calatorie
    :return: int - an de sfarsit a calatoriei
    '''
    return calatorie[6]

def get_destinatie(calatorie):
    '''
    returneaza destinatia string a calatoriei calatorie
    :param calatorie: calatorie
    :return: string - destinatia calatoriei
    '''
    return calatorie[7]

def get_pret(calatorie):
    '''
    returneaza pretul float al calatoriei calatorie
    :param calatorie: calatorie
    :return: float - pret calatorie
    '''
    return calatorie[8]

def set_zi_inceput_calatorie(calatorie, zi_inceput_noua):
    '''
    seteaza ziua de inceput int a calatoriei calatorie la intul zi_inceput_noua
    :param calatorie: calatorie
    :param zi_inceput_noua: int
    :return: -
    '''
    calatorie[1]=zi_inceput_noua

def set_luna_inceput_calatorie(calatorie, luna_inceput_noua):
    '''
    seteaza luna de inceput int a calatoriei calatorie la intul luna_inceput_noua
    :param calatorie: calatorie
    :param luna_inceput_noua: int
    :return: -
    '''
    calatorie[2]=luna_inceput_noua

def set_an_inceput_calatorie(calatorie, an_inceput_nou):
    '''
    seteaza an de inceput int al calatoriei calatorie la intul an_inceput_noua
    :param calatorie: calatorie
    :param an_inceput_noua: int
    :return: -
    '''
    calatorie[3]=an_inceput_nou

def set_zi_sfarsit_calatorie(calatorie, zi_sfarsit_noua):
    '''
    seteaza ziua de sfarsit int a calatoriei calatorie la intul zi_sfarsit_noua
    :param calatorie: calatorie
    :param luna_inceput_noua: int
    :return: -
    '''
    calatorie[4]=zi_sfarsit_noua

def set_luna_sfarsit_calatorie(calatorie, luna_sfarsit_noua):
    '''
    seteaza luna de sfarsit int a calatoriei calatorie la intul luna_sfarsit_noua
    :param calatorie: calatorie
    :param luna_inceput_noua: int
    :return: -
    '''
    calatorie[5]=luna_sfarsit_noua

def set_an_sfarsit_calatorie(calatorie, an_sfarsit_nou):
    '''
    seteaza anul de sfarsit int al calatoriei calatorie la intul an_sfarsit_noua
    :param calatorie: calatorie
    :param luna_inceput_noua: int
    :return: -
    '''
    calatorie[6]=an_sfarsit_nou

def set_destinatie_calatorie(calatorie,destinatie_noua):
    '''
    seteaza o destinatie string a calatoriei calatorie la stringul destinatie_noua
    :param calatorie: calatorie
    :param destinatie_noua: string
    :return: -
    '''
    calatorie[7]=destinatie_noua

def set_pret_calatorie(calatorie,pret_nou):
    '''
    seteaza pretul float al calatoriei calatorie la floatul pret_nou
    :param calatorie: calatorie
    :param pret_nou: float
    :return: -
    '''
    calatorie[8]=pret_nou

def egal_calatorii(calatoria_a, calatoria_b):
    '''
    verifica daca calatoria calatoria_a si calatoria calatoria_b sunt egale
    :param calatoria_a: calatorie
    :param calatoria_b: calatorie
    :return: rez - bool: True daca calatoria_a si calatoria_b sunt aceeasi calatorie
                        False, altfel
    '''

    return get_id_calatorie(calatoria_a) == get_id_calatorie(calatoria_b)