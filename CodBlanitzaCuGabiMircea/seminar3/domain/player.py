def creeaza_player(id_player,nume,valoare):
    '''
    creeaza un player cu idul intreg id_player, numele string nume, si valuarea float valoare
    :param id_player: integer
    :param nume: string
    :param valoare: float
    :return: rez: player cu idul intreg id_player, numele string nume, si valuarea float valoare
    '''
    #return [id_player,nume,valoare]
    return {
        "id":id_player,
        "nume":nume,
        "valoare":valoare
    }

def get_id_player(player):
    '''
    obtine idul intreg al playerului player
    :param player: player
    :return: rez : integer - idul playerului player
    '''
    return player["id"]

def get_nume_player(player):
    '''
    obtine numele string al playerului player
    :param player: player
    :return: rez: string numele playerului player
    '''
    return player["nume"]

def get_valoare_player(player):
    '''
    obtine valoarea float a playerului player
    :param player: player
    :return: rez: float valoarea playerului player
    '''
    return player["valoare"]

def set_nume_player(player,nume_nou):
    '''
    modifica numele playerului player la o noua valoare data de stringul nume_nou
    :param player: player
    :param nume_nou: string
    :return: - (numele playerului player se schimba la stringul nume_nou)
    '''
    player["nume"] = nume_nou

def set_valoare_player(player,valoare_noua):
    '''
    modifica valoarea float a playerului player la o noua valoare data de floatul valoare_noua
    :param player: player
    :param valoare_noua: float
    :return: - (valoarea playerului player se schimba la floatul valoare_noua)
    '''
    player["valoare"] = valoare_noua

def egal_players(player_a,player_b):
    '''
    verifica daca player_a si player_b sunt identici adica au acelasi id numeric
    :param player_a: player
    :param player_b: player
    :return: rez = True, daca idul playerului player_a e identic cu idul playerului player_b
    '''
    return get_id_player(player_a) == get_id_player(player_b)