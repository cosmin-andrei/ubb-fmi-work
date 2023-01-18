from business.service_calatorii import numar_calatorii_service, adauga_calatorie_service
from domain.calatorie import creeaza_calatorie, get_id_calatorie, get_zi_inceput, get_luna_inceput, get_an_inceput, \
    get_zi_sfarsit, get_luna_sfarsit, get_an_sfarsit, get_destinatie, get_pret, set_zi_inceput_calatorie, \
    set_luna_inceput_calatorie, set_an_inceput_calatorie, set_luna_sfarsit_calatorie, set_zi_sfarsit_calatorie, \
    set_an_sfarsit_calatorie, set_pret_calatorie, set_destinatie_calatorie
from infrastructura.cautare_calatorii import cautare_datesejur, cautare_destinatie_pret, cautare_datasf
from infrastructura.filtrare_calatorii import filtrare_pret_destinatie, filtrare_luna
from infrastructura.rapoarte_calatorii import rapoarte_destinatie, rapoarte_perioada, rapoarte_mediepret
from infrastructura.repository_calatorii import numar_calatorii_lista, adauga_calatorie_lista
from infrastructura.stergere_calatorii import stergere_destinatie, stergere_nrzile, stergere_pret
from infrastructura.undo import add_to_undo
from validatoare.validare_calatorie import valideaza_calatoria


def ruleaza_teste_calatorie():
    id_calatorie=1
    zi_inceput=10
    luna_inceput=5
    an_inceput=2022
    zi_sfarsit=15
    luna_sfarsit=5
    an_sfarsit=2022
    destinatie="Berlin"
    pret=3020.5
    calatorie = creeaza_calatorie(id_calatorie,zi_inceput,luna_inceput,an_inceput,zi_sfarsit,luna_sfarsit,an_sfarsit,destinatie,pret)
    assert(id_calatorie==get_id_calatorie(calatorie))
    assert(zi_inceput==get_zi_inceput(calatorie))
    assert(luna_inceput==get_luna_inceput(calatorie))
    assert(an_inceput==get_an_inceput(calatorie))
    assert(zi_sfarsit==get_zi_sfarsit(calatorie))
    assert(luna_sfarsit==get_luna_sfarsit(calatorie))
    assert(an_sfarsit==get_an_sfarsit(calatorie))
    assert(destinatie==get_destinatie(calatorie))
    assert(abs(pret-get_pret(calatorie)) < 0.00001)
    zi_inceput_noua=3
    set_zi_inceput_calatorie(calatorie, zi_inceput_noua)
    assert(zi_inceput_noua==get_zi_inceput(calatorie))
    luna_inceput_noua=10
    set_luna_inceput_calatorie(calatorie,luna_inceput_noua)
    assert(luna_inceput_noua==get_luna_inceput(calatorie))
    an_inceput_nou=2023
    set_an_inceput_calatorie(calatorie,an_inceput_nou)
    assert(an_inceput_nou==get_an_inceput(calatorie))
    zi_sfarsit_noua=10
    set_zi_sfarsit_calatorie(calatorie,zi_sfarsit_noua)
    assert(zi_sfarsit_noua==get_zi_sfarsit(calatorie))
    luna_sfarsit_noua=12
    set_luna_sfarsit_calatorie(calatorie,luna_sfarsit_noua)
    assert(luna_sfarsit_noua==get_luna_sfarsit(calatorie))
    an_sfarsit_nou=2023
    set_an_sfarsit_calatorie(calatorie,an_sfarsit_nou)
    assert(an_sfarsit_nou==get_an_sfarsit(calatorie))
    destinatie_noua="Franta"
    set_destinatie_calatorie(calatorie,destinatie_noua)
    assert(destinatie_noua==get_destinatie(calatorie))
    pret_nou=1000.32
    set_pret_calatorie(calatorie,pret_nou)
    assert(abs(pret_nou-get_pret(calatorie))<0.00001)


def ruleaza_teste_validator_calatorie():
    id_calatorie=2
    zi_inceput=15
    luna_inceput=12
    an_inceput=2020
    zi_sfarsit=16
    luna_sfarsit=12
    an_sfarsit=2020
    destinatie="Berlin"
    pret=20.1
    calatorie = creeaza_calatorie(id_calatorie,zi_inceput,luna_inceput,an_inceput,zi_sfarsit,luna_sfarsit,an_sfarsit,destinatie,pret)
    valideaza_calatoria(calatorie)

    id_calatorie=-1
    zi_inceput=0
    luna_inceput=25
    an_inceput=2025
    zi_sfarsit=32
    luna_sfarsit=25
    an_sfarsit=2020
    destinatie=""
    pret=-1.1
    calatorie = creeaza_calatorie(id_calatorie, zi_inceput, luna_inceput, an_inceput, zi_sfarsit, luna_sfarsit, an_sfarsit, destinatie, pret)
    try:
        valideaza_calatoria(calatorie)
        assert False
    except ValueError as ve:
        assert(str(ve)=="id invalid!\nzi inceput invalida!\nluna inceput invalida!\nzi sfarsit invalid!\nluna sfarsit invalid!\nanul este invalid!\ndestinatia este invalida!\npret invalid!\n")

def ruleaza_teste_repository_calatorii():
    calatorii=[]
    id_calatorie = 2
    zi_inceput = 15
    luna_inceput = 12
    an_inceput = 2020
    zi_sfarsit = 16
    luna_sfarsit = 12
    an_sfarsit = 2020
    destinatie = "Berlin"
    pret = 20.1
    calatorie = creeaza_calatorie(id_calatorie, zi_inceput, luna_inceput, an_inceput, zi_sfarsit, luna_sfarsit, an_sfarsit, destinatie, pret)
    assert(numar_calatorii_lista(calatorii) == 0)
    adauga_calatorie_lista(calatorii,calatorie)
    assert(numar_calatorii_lista(calatorii) == 1)

    acelasi_id=2
    alta_zi_inceput = 10
    alta_luna_inceput = 5
    alt_an_inceput = 2021
    alta_zi_sfarsit = 15
    alta_luna_sfarsit = 5
    alt_an_sfarsit = 2022
    alta_destinatie = "Paris"
    alt_pret = 201.1
    alta_calatorie= creeaza_calatorie(acelasi_id, alta_zi_inceput, alta_luna_inceput, alt_an_inceput, alta_zi_sfarsit, alta_luna_sfarsit, alt_an_sfarsit, alta_destinatie, alt_pret)
    try:
        adauga_calatorie_lista(calatorii, alta_calatorie)
        assert False
    except ValueError as ve:
        assert (str(ve) == "calatorie invalida!\n")


def ruleaza_teste_service_calatorie():
    calatorii=[]
    l_undo=[]
    id_calatorie = 2
    zi_inceput = 15
    luna_inceput = 12
    an_inceput = 2020
    zi_sfarsit = 16
    luna_sfarsit = 12
    an_sfarsit = 2020
    destinatie = "Berlin"
    pret = 20.1
    assert(numar_calatorii_service(calatorii)==0)
    adauga_calatorie_service(calatorii,l_undo,id_calatorie, zi_inceput, luna_inceput, an_inceput, zi_sfarsit, luna_sfarsit, an_sfarsit, destinatie, pret)
    assert(numar_calatorii_service(calatorii)==1)

    id_calatorie = -1
    zi_inceput = 0
    luna_inceput = 25
    an_inceput = 2025
    zi_sfarsit = 32
    luna_sfarsit = 25
    an_sfarsit = 2020
    destinatie = ""
    pret = -1.1
    try:
        adauga_calatorie_service(calatorii,l_undo,id_calatorie, zi_inceput, luna_inceput, an_inceput, zi_sfarsit, luna_sfarsit, an_sfarsit, destinatie, pret)
        assert False
    except ValueError as ve:
        assert(str(ve)=="id invalid!\nzi inceput invalida!\nluna inceput invalida!\nzi sfarsit invalid!\nluna sfarsit invalid!\nanul este invalid!\ndestinatia este invalida!\npret invalid!\n")

    acelasi_id = 2
    alta_zi_inceput = 10
    alta_luna_inceput = 5
    alt_an_inceput = 2021
    alta_zi_sfarsit = 15
    alta_luna_sfarsit = 5
    alt_an_sfarsit = 2022
    alta_destinatie = "Paris"
    alt_pret = 201.1
    alta_calatorie = creeaza_calatorie(acelasi_id, alta_zi_inceput, alta_luna_inceput, alt_an_inceput, alta_zi_sfarsit, alta_luna_sfarsit, alt_an_sfarsit, alta_destinatie, alt_pret)
    try:
        adauga_calatorie_service(calatorii,l_undo, acelasi_id, alta_zi_inceput, alta_luna_inceput, alt_an_inceput, alta_zi_sfarsit, alta_luna_sfarsit, alt_an_sfarsit, alta_destinatie, alt_pret)
        assert False
    except ValueError as ve:
        assert (str(ve) == "calatorie invalida!\n")


def ruleaza_teste_cautare_calatorii():
    calatorii = []
    id_calatorie = 2
    zi_inceput = 15
    luna_inceput = 12
    an_inceput = 2020
    zi_sfarsit = 16
    luna_sfarsit = 12
    an_sfarsit = 2020
    destinatie = "Berlin"
    pret = 20.1
    calatorie = creeaza_calatorie(id_calatorie, zi_inceput, luna_inceput, an_inceput, zi_sfarsit, luna_sfarsit, an_sfarsit, destinatie, pret)
    adauga_calatorie_lista(calatorii, calatorie)
    id_calatorie = 5
    zi_inceput = 10
    luna_inceput = 11
    an_inceput = 2021
    zi_sfarsit = 16
    luna_sfarsit = 12
    an_sfarsit = 2021
    destinatie = "Franta"
    pret = 100
    calatorie = creeaza_calatorie(id_calatorie, zi_inceput, luna_inceput, an_inceput, zi_sfarsit, luna_sfarsit, an_sfarsit, destinatie, pret)
    adauga_calatorie_lista(calatorii, calatorie)
    lista = cautare_datesejur(calatorii, 8, 9, 2019, 10, 10, 2022)
    assert(lista == [[2, 15, 12, 2020, 16, 12, 2020, 'Berlin', 20.1], [5, 10, 11, 2021, 16, 12, 2021, 'Franta', 100]])
    destinatie = "Berlin"
    pret=23.555
    lista = cautare_destinatie_pret(calatorii,destinatie,pret)
    assert(lista == [[2, 15, 12, 2020, 16, 12, 2020, 'Berlin', 20.1]])
    lista = cautare_datasf(calatorii,zi_sfarsit,luna_sfarsit,an_sfarsit)
    assert(lista == [[5, 10, 11, 2021, 16, 12, 2021, 'Franta', 100]])


def ruleaza_teste_rapoarte_calatorii():
    calatorii = []
    id_calatorie = 2
    zi_inceput = 15
    luna_inceput = 12
    an_inceput = 2020
    zi_sfarsit = 16
    luna_sfarsit = 12
    an_sfarsit = 2020
    destinatie = "Franta"
    pret = 20.1
    calatorie = creeaza_calatorie(id_calatorie, zi_inceput, luna_inceput, an_inceput, zi_sfarsit, luna_sfarsit, an_sfarsit, destinatie, pret)
    adauga_calatorie_lista(calatorii, calatorie)
    id_calatorie = 5
    zi_inceput = 10
    luna_inceput = 11
    an_inceput = 2021
    zi_sfarsit = 16
    luna_sfarsit = 12
    an_sfarsit = 2021
    destinatie = "Franta"
    pret = 100
    calatorie = creeaza_calatorie(id_calatorie, zi_inceput, luna_inceput, an_inceput, zi_sfarsit, luna_sfarsit, an_sfarsit, destinatie, pret)
    adauga_calatorie_lista(calatorii, calatorie)
    destinatie_data="Franta"
    assert(rapoarte_destinatie(calatorii,destinatie_data) == 2)
    alta_destinatie_data="Berlin"
    assert(rapoarte_destinatie(calatorii, alta_destinatie_data) == 0)
    id_calatorie = 3
    zi_inceput = 10
    luna_inceput = 11
    an_inceput = 2021
    zi_sfarsit = 16
    luna_sfarsit = 12
    an_sfarsit = 2021
    destinatie = "Berlin"
    pret = 9999
    calatorie = creeaza_calatorie(id_calatorie, zi_inceput, luna_inceput, an_inceput, zi_sfarsit, luna_sfarsit, an_sfarsit, destinatie, pret)
    adauga_calatorie_lista(calatorii, calatorie)
    lista = rapoarte_perioada(calatorii,zi_inceput,luna_inceput,an_inceput, zi_sfarsit, luna_sfarsit, an_sfarsit)
    assert(lista == [[5, 10, 11, 2021, 16, 12, 2021, 'Franta', 100], [3, 10, 11, 2021, 16, 12, 2021, 'Berlin', 9999]])
    destinatie="Franta"
    assert(rapoarte_mediepret(calatorii,destinatie) == 60.05)


def ruleaza_teste_filtrare_calatorii():
    calatorii = []
    id_calatorie = 2
    zi_inceput = 15
    luna_inceput = 1
    an_inceput = 2020
    zi_sfarsit = 16
    luna_sfarsit = 1
    an_sfarsit = 2020
    destinatie = "Berlin"
    pret = 20.1
    calatorie = creeaza_calatorie(id_calatorie, zi_inceput, luna_inceput, an_inceput, zi_sfarsit, luna_sfarsit,an_sfarsit, destinatie, pret)
    adauga_calatorie_lista(calatorii, calatorie)
    id_calatorie = 5
    zi_inceput = 10
    luna_inceput = 11
    an_inceput = 2021
    zi_sfarsit = 16
    luna_sfarsit = 12
    an_sfarsit = 2021
    destinatie = "Franta"
    pret = 100
    calatorie = creeaza_calatorie(id_calatorie, zi_inceput, luna_inceput, an_inceput, zi_sfarsit, luna_sfarsit,an_sfarsit, destinatie, pret)
    adauga_calatorie_lista(calatorii, calatorie)
    destinatie_data="Germania"
    pret_dat= 25.10
    assert(filtrare_pret_destinatie(calatorii,destinatie_data,pret_dat) == [[5, 10, 11, 2021, 16, 12, 2021, 'Franta', 100]])
    luna_data=12
    assert(filtrare_luna(calatorii,luna_data) == [[2, 15, 1, 2020, 16, 1, 2020, 'Berlin', 20.1]])


def ruleaza_teste_stergere_calatorii():
    calatorii = []
    l_undo=[]
    id_calatorie = 2
    zi_inceput = 15
    luna_inceput = 1
    an_inceput = 2020
    zi_sfarsit = 16
    luna_sfarsit = 1
    an_sfarsit = 2020
    destinatie = "Berlin"
    pret = 20.1
    calatorie = creeaza_calatorie(id_calatorie, zi_inceput, luna_inceput, an_inceput, zi_sfarsit, luna_sfarsit, an_sfarsit, destinatie, pret)
    adauga_calatorie_lista(calatorii, calatorie)
    id_calatorie = 5
    zi_inceput = 10
    luna_inceput = 11
    an_inceput = 2021
    zi_sfarsit = 16
    luna_sfarsit = 12
    an_sfarsit = 2021
    destinatie = "Franta"
    pret = 100
    calatorie = creeaza_calatorie(id_calatorie, zi_inceput, luna_inceput, an_inceput, zi_sfarsit, luna_sfarsit, an_sfarsit, destinatie, pret)
    adauga_calatorie_lista(calatorii, calatorie)
    destinatie_data="Franta"
    assert(stergere_destinatie(calatorii,l_undo,destinatie_data) == [[2, 15, 1, 2020, 16, 1, 2020, 'Berlin', 20.1]])
    id_calatorie = 5
    zi_inceput = 10
    luna_inceput = 11
    an_inceput = 2021
    zi_sfarsit = 16
    luna_sfarsit = 11
    an_sfarsit = 2021
    destinatie = "Franta"
    pret = 100
    calatorie = creeaza_calatorie(id_calatorie, zi_inceput, luna_inceput, an_inceput, zi_sfarsit, luna_sfarsit, an_sfarsit, destinatie, pret)
    adauga_calatorie_lista(calatorii, calatorie)
    numar_zile_dat = 5
    assert(stergere_nrzile(calatorii,l_undo,numar_zile_dat)==[[5, 10, 11, 2021, 16, 11, 2021, 'Franta', 100]])
    id_calatorie = 2
    zi_inceput = 15
    luna_inceput = 1
    an_inceput = 2020
    zi_sfarsit = 16
    luna_sfarsit = 1
    an_sfarsit = 2020
    destinatie = "Berlin"
    pret = 20.1
    calatorie = creeaza_calatorie(id_calatorie, zi_inceput, luna_inceput, an_inceput, zi_sfarsit, luna_sfarsit, an_sfarsit, destinatie, pret)
    adauga_calatorie_lista(calatorii, calatorie)
    pret_dat=50
    assert(stergere_pret(calatorii,l_undo,pret_dat)==[[2, 15, 1, 2020, 16, 1, 2020, 'Berlin', 20.1]])


def ruleaza_teste_undo():
    undo = []
    calatorie1 = [[2, 15, 1, 2020, 16, 1, 2020, 'Berlin', 20.1]]
    calatorie2 = [[5, 10, 11, 2021, 16, 11, 2021, 'Franta', 100],[2, 15, 1, 2020, 16, 1, 2020, 'Berlin', 20.1]]
    add_to_undo(calatorie1, undo)
    assert undo == [[[2, 15, 1, 2020, 16, 1, 2020, 'Berlin', 20.1]]]


def ruleaza_toate_testele():
    ruleaza_teste_calatorie()
    ruleaza_teste_validator_calatorie()
    ruleaza_teste_repository_calatorii()
    ruleaza_teste_service_calatorie()
    ruleaza_teste_stergere_calatorii()
    ruleaza_teste_cautare_calatorii()
    ruleaza_teste_rapoarte_calatorii()
    ruleaza_teste_filtrare_calatorii()
    ruleaza_teste_undo()
    print("teste rulate cu succes \n")