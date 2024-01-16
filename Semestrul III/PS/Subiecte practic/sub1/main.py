# grupa 223/1
from math import comb
from random import sample

import numpy as np


# B - bilele extrase au aceeasi culoare
# A - cel putin o bila are culoarea albastra

# c- P(B|A)

def problema1():
    nr_simulari = 1000
    simulari_A = 0
    simulari_B = 0

    for _ in range(nr_simulari):
        bile_extrase = sample(['red', 'blue', 'green'], counts=[7, 5, 3], k=3)

        A = False
        for bila in bile_extrase:
            if bila == 'blue':
                A = True

        if A == True:
            simulari_A = simulari_A + 1

        B = True

        for i in range(1, 3):
            if bile_extrase[i] != 'red':
                B = False

        if B == True:
            simulari_B = simulari_B + 1

    print("Cel putin o bila are culoarea albastra - ", simulari_A / nr_simulari)
    print("Bilele extrase au aceeasi culoare - ", simulari_B / nr_simulari)
    print("Rez prin simulari repetate: ", simulari_B / simulari_A)

    prob1 = comb(5, 3) / comb(15, 3)  # toate bilele sunt albastre
    prob2 = 1 - comb(5, 3) / comb(15, 3)
    print("Probabilitate teoretica: ", prob1 / prob2)


problema1()


# grupa222

def problema2():
    nr_simulari = 2000
    simulari_a = 0
    simulari_b = 0
    simulari_ab = 0

    for _ in range(nr_simulari):
        bile_extrase = sample([1, 2, 3], counts=[6, 3, 4], k=3)

        A = False
        if bile_extrase[0] != bile_extrase[1]:
            if bile_extrase[1] != bile_extrase[2]:
                A = True

        if A == True:
            simulari_a += 1

        B = False
        for bila in bile_extrase:
            if bila == 1:
                B = True

        if B == True:
            simulari_b += 1

        if A is True and B is True:
            simulari_ab += 1

    print("Prob event a", simulari_a / nr_simulari)
    print("Prob event b", simulari_b / nr_simulari)
    print("Prob C simulari rep", simulari_ab / simulari_a)

    prob_A = comb(6, 3) / comb(13, 3)
    prob_B = 1 - comb(9, 3) / comb(13, 3)  # Probabilitatea să nu existe 1 în cele trei extrase
    prob_A_intersect_B = comb(5, 2) / comb(13, 3)  # Numărul moduri de a extrage 3 bile diferite cu cel puțin o bilă 1

    prob_B_given_A = prob_A_intersect_B / prob_A
    print("Probabilitate teoretică P(B|A):", prob_B_given_A)


problema2()

def problema3():
    nr_simulari = 5000
    simulari_a=0
    simulari_b=0

    for _ in range(nr_simulari):
        acumulatori_selectati = sample([0,1],counts=[3,7],k=3)

        count_desc=0
        for acm in acumulatori_selectati:
            if acm == 0:
                count_desc += 1

        if count_desc == 1:
            simulari_a += 1

        if count_desc == 0:
            simulari_b += 1

    print("A: ", simulari_a/nr_simulari)
    print("B: ", simulari_b/nr_simulari)
    prob1 = comb(7,3)/comb(10,3)
    print("Prob teoretica: ", prob1)


problema3()


def problema4():
    nr_simulari = 1000
    cA =0
    cB =0
    for _ in range(nr_simulari):
        v=np.concatenate([np.random.normal(-1,1,2), np.random.normal(0,1,3)])

        count=0
        for val in v:
            if val <

