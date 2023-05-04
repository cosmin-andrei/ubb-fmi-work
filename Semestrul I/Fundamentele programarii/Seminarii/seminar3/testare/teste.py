from domain.player import creeaza_player, get_id_player, get_nume_player, get_valoare_player, set_nume_player, \
    set_valoare_player
from infrastructura.repository_players import adauga_player_la_lista, numar_players_lista
from validare.validator_player import valideaza_player


def ruleaza_teste_player():
    id_player = 23
    nume = "Jordan"
    valoare = 9000.1

    player = creeaza_player(id_player,nume,valoare)
    assert(id_player == get_id_player(player))
    assert(nume == get_nume_player(player))
    assert(abs(valoare - get_valoare_player(player))<0.001)

    nume_nou = "LeBum"
    valoare_noua = 89.75
    set_nume_player(player,nume_nou)
    assert (nume_nou == get_nume_player(player))
    set_valoare_player(player,valoare_noua)
    assert (abs(valoare_noua - get_valoare_player(player)) < 0.001)


def ruleaza_teste_validare_player():
    id_player = 23
    nume = "Jordan"
    valoare = 9000.1

    player_corect = creeaza_player(id_player, nume, valoare)
    valideaza_player(player_corect)

    id_player_gresit = -1
    nume_gresit = ""
    valoare_gresita = 0.0
    player_gresit = creeaza_player(id_player_gresit,nume_gresit,valoare_gresita)
    try:
        valideaza_player(player_gresit)
        assert(False)
    except ValueError as ve:
        assert(str(ve) == "id invalid!\nnume invalid!\nvaloare invalida!\n")


def ruleaza_teste_repository_players():
    players = []
    id_player = 23
    nume = "Jordan"
    valoare = 9000.1
    assert(numar_players_lista(players) == 0)
    player = creeaza_player(id_player, nume, valoare)
    adauga_player_la_lista(players,player)
    assert (numar_players_lista(players) == 1)
    id_player_nou = 23
    nume_nou = "LeBum"
    valoare_noua = 90.1
    player_acelasi_id = creeaza_player(id_player_nou, nume_nou, valoare_noua)
    try:
        adauga_player_la_lista(players,player_acelasi_id)
        assert False
    except ValueError as ve:
        assert(str(ve)=="player existent!\n")
    assert (numar_players_lista(players) == 1)

def ruleaza_toate_testele():
    ruleaza_teste_player()
    print("teste player rulate cu succes!")
    ruleaza_teste_validare_player()
    print("teste validare player rulate cu succes!")
    ruleaza_teste_repository_players()
    print("teste repository players rulate cu succes!")