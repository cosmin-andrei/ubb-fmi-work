from business.service_teme import adauga_tema_service, numar_teme_service
from domeniu.tema import creeaza_tema, get_id_tema, get_cod_tema, get_pret, set_pret
from infrastructura.repository_teme import numar_teme_lista, adauga_tema_lista
from validatoare.validator_tema import valideaza_tema


def ruleaza_teste_tema():
    id_tema=23
    cod_tema = "lab2fpIstvan"
    pret = 50.69
    tema = creeaza_tema(id_tema,cod_tema,pret)
    assert(id_tema==get_id_tema(tema))
    assert(cod_tema == get_cod_tema(tema))
    assert(abs(pret-get_pret(tema)) < 0.00001)
    pret_nou = 60.75
    set_pret(tema,pret_nou)
    assert(abs(pret_nou-get_pret(tema)) < 0.00001)

def ruleaza_teste_validator_tema():
    id_tema = 23
    cod_tema = "lab2fpIstvan"
    pret = 50.69
    tema = creeaza_tema(id_tema,cod_tema,pret)
    valideaza_tema(tema)

    id_tema_gresit = -23
    cod_tema_gresit = ""
    pret_gresit = 0.0
    tema_gresita = creeaza_tema(id_tema_gresit, cod_tema_gresit, pret_gresit)
    try:
        valideaza_tema(tema_gresita)
        assert False
    except ValueError as ve:
        assert(str(ve)=="id invalid!\ncod invalid!\npret invalid!\n")


def ruleaza_teste_repository_teme():
    teme = []
    id_tema = 23
    cod_tema = "lab2fpIstvan"
    pret = 50.69
    tema= creeaza_tema(id_tema,cod_tema,pret)
    assert(numar_teme_lista(teme) == 0)
    adauga_tema_lista(teme,tema)
    assert(numar_teme_lista(teme)==1)

    acelasi_id_tema = 23
    alt_cod_tema = "Lab2LogPop"
    alt_pret = 100.07
    alta_tema_acelasi_id = creeaza_tema(acelasi_id_tema,alt_cod_tema,alt_pret)
    try:
        adauga_tema_lista(teme,alta_tema_acelasi_id)
        assert False
    except ValueError as ve:
        assert(str(ve)=="tema invalida!\n")


def ruleaza_teste_service_tema():
    teme = []
    id_tema = 23
    cod_tema = "lab2fpIstvan"
    pret = 50.69
    assert(numar_teme_service(teme)==0)
    adauga_tema_service(teme,id_tema,cod_tema,pret)
    assert(numar_teme_service(teme)==1)

    id_tema_gresit = -23
    cod_tema_gresit = ""
    pret_gresit = 0.0
    try:
        adauga_tema_service(teme,id_tema_gresit,cod_tema_gresit,pret_gresit)
        assert False
    except ValueError as ve:
        assert(str(ve)=="id invalid!\ncod invalid!\npret invalid!\n")

    acelasi_id_tema = 23
    alt_cod_tema = "Lab2LogPop"
    alt_pret = 100.07

    try:
        adauga_tema_service(teme, acelasi_id_tema, alt_cod_tema, alt_pret)
        assert False
    except ValueError as ve:
        assert (str(ve) == "tema invalida!\n")

def ruleaza_toate_testele():
    ruleaza_teste_tema()
    print("teste tema trecute cu succes!")
    ruleaza_teste_validator_tema()
    print("teste validare tema trecute cu succes!")
    ruleaza_teste_repository_teme()
    print("teste repository teme trecute cu succes!")
    ruleaza_teste_service_tema()
    print("teste service teme trecute cu succes!")