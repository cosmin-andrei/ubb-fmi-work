from domain.player import egal_players


def adauga_player_la_lista(l,player):
    '''

    :param l: lista de playeri unic identificabili prin id_player intreg
    :param player: player
    :return: l' = l U {player}, daca nu exista deja idul intreg al playerului player in lista de playeri l
    :raises: ValueError cu mesajul "player existent!\n" daca idul playerului player exista deja in lista de playeri l
    '''
    for _player in l:
        if egal_players(_player,player):
            raise ValueError("player existent!\n")
    l.append(player)


def numar_players_lista(l):
    '''
    returneaza numarul de playeri unic identificabili prin id intreg din lista
    :param l: lista de playeri unic identificabili prin id intreg
    :return: rez : intreg - numarul de playeri din lista l
    '''
    return len(l)

def get_all_players(l):
    '''
    returneaza lista cu toti playerii unic indentificabili prin id intreg din lista l
    :param l: lista de playeri
    :return: lista de playeri
    '''
    pass