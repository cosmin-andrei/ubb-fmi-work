from domain.player import get_id_player, get_nume_player, get_valoare_player


def valideaza_player(player):
    '''
    valideaza daca idul intreg al playerului este pozitiv, numele string este nevid si valoarea este strict pozitiva
    daca cel putin un atribut al playerului este invalid arunca exceptie de tipul ValueError
    :param player: player
    :return: -
    :raises:ValueError daca datele din player sunt invalide:
                       daca id_player < 0 -> "id invalid!\n"
                       daca nume == "" -> "nume invalid!\n"
                       daca valoare <=0 -> "valoare invalida!\n"
    '''
    errors = ""
    if get_id_player(player)<0:
        errors += "id invalid!\n"
    if get_nume_player(player)=="":
        errors += "nume invalid!\n"
    if get_valoare_player(player)<=0:
        errors += "valoare invalida!\n"

    if len(errors)>0:
        raise ValueError(errors)
