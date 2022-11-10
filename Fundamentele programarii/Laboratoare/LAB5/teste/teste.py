from business.service_calatorii import adauga_calatorie_service
from domain.calatorie import creeaza_calatorie, get_id_calatorie, get_zi_inceput, get_luna_inceput, get_an_inceput, \
    get_zi_sfarsit, get_luna_sfarsit, get_an_sfarsit, get_destinatie, get_pret, set_zi_inceput_calatorie, \
    set_luna_inceput_calatorie, set_an_inceput_calatorie, set_luna_sfarsit_calatorie, set_zi_sfarsit_calatorie, \
    set_an_sfarsit_calatorie, set_pret_calatorie, set_destinatie_calatorie
from infrastructura.cautare_calatorii import cautare_datesejur, cautare_destinatie_pret, cautare_datasf
from infrastructura.repository_calatorii import numar_calatorii_lista, adauga_calatorie_lista
from infrastructura.stergere_calatorii import stergere_destinatie, stergere_nrzile, stergere_pret
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
    calatorii={}
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
    assert(len(calatorii) == 0)
    adauga_calatorie_lista(calatorii,calatorie)
    assert(len(calatorii) == 1)

def ruleaza_teste_service_calatorie():
    calatorii={}
    id_calatorie = 2
    zi_inceput = 15
    luna_inceput = 12
    an_inceput = 2020
    zi_sfarsit = 16
    luna_sfarsit = 12
    an_sfarsit = 2020
    destinatie = "Berlin"
    pret = 20.1
    assert(len(calatorii)==0)
    adauga_calatorie_service(calatorii,id_calatorie, zi_inceput, luna_inceput, an_inceput, zi_sfarsit, luna_sfarsit, an_sfarsit, destinatie, pret)
    assert(len(calatorii)==1)

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
        adauga_calatorie_service(calatorii,id_calatorie, zi_inceput, luna_inceput, an_inceput, zi_sfarsit, luna_sfarsit, an_sfarsit, destinatie, pret)
        assert False
    except ValueError as ve:
        assert(str(ve)=="id invalid!\nzi inceput invalida!\nluna inceput invalida!\nzi sfarsit invalid!\nluna sfarsit invalid!\nanul este invalid!\ndestinatia este invalida!\npret invalid!\n")

def ruleaza_teste_cautare_calatorii():
    calatorii = {}
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
    assert(lista == {1: [2, 15, 12, 2020, 16, 12, 2020, 'Berlin', 20.1], 2: [5, 10, 11, 2021, 16, 12, 2021, 'Franta', 100]})
    destinatie = "Berlin"
    pret=23.555
    lista = cautare_destinatie_pret(calatorii,destinatie,pret)
    assert(lista == {1: [2, 15, 12, 2020, 16, 12, 2020, 'Berlin', 20.1]})
    lista = cautare_datasf(calatorii,zi_sfarsit,luna_sfarsit,an_sfarsit)
    assert(lista == {2: [5, 10, 11, 2021, 16, 12, 2021, 'Franta', 100]})

def ruleaza_teste_stergere_calatorii():
    calatorii = {}
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
    stergere_destinatie(calatorii,calatorie,destinatie_data)
    assert(len(calatorii)==1)
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
    stergere_nrzile(calatorii,calatorie,numar_zile_dat)
    assert(len(calatorii)==1)
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
    stergere_pret(calatorii,calatorie,pret_dat)
    assert(len(calatorii)==1)

def ruleaza_toate_testele():
    ruleaza_teste_calatorie()
    print("toate testele calatorie au mers blanitza!")
    ruleaza_teste_validator_calatorie()
    print("toate testele validare calatorie au mers blanitza!")
    ruleaza_teste_repository_calatorii()
    print("toate testele repository calatorie au mers blanitza!")
    ruleaza_teste_service_calatorie()
    print("toate testele service calatorie au mers blanitza!")
    ruleaza_teste_stergere_calatorii()
    print("toate testele stergere calatrii au mers blanitza!")
    ruleaza_teste_cautare_calatorii()
    print("toate testele cautare calatorii au mers blanitza!")