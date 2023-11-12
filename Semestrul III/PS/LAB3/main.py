# problema 1
import random
from random import choices, sample, randrange
from math import comb, perm

import numpy as np
from matplotlib import pyplot as plt
from numpy import arange
from scipy.stats import binom

from matplotlib.pyplot import hist, bar, legend, grid, show


def problema1():
    nr_simulari = 10000
    simulari_A = 0
    simulari_B =0

    for _ in range(nr_simulari):
        bile_extrase = sample(['red', 'blue', 'green'], counts=[5,3,2], k=3)

        A = False
        for bila in bile_extrase:
            if bila == 'red':
                A = True

        if A == True:
            simulari_A += 1

        B = True
        for i in range(1,3):
            if bile_extrase[i] != 'red':
                B = False

        if B==True:
            simulari_B += 1

    print("Rez prin simulari repetate: ", simulari_B/simulari_A, "\n")

    prob1 = comb(5,3)/comb(10,3) #toate sunt rosii
    prob2 = 1 - comb(5,3)/comb(10,3)
    print("Rez teoretic: ", prob1/prob2, "\n")



def problema2():

    data = [randrange(1, 7) for _ in range(500)]
    bin_edges = [k+0.5 for k in range(7)]
    hist(data, bin_edges, density = True, rwidth = 0.9, color = 'green', edgecolor = 'black', alpha = 0.5, label = 'frecvente relative')
    distribution = dict([(i,1/6) for i in range(1,7)])
    bar(distribution.keys(), distribution.values(), width = 0.85, color = 'red', edgecolor = 'black', alpha = 0.6, label = 'probabilitati')
    legend(loc='lower left')
    grid()
    show()

def problema3():
    n=5
    p=0.6

    #lista de 1000 de valori
    X = binom.rvs (n, p, size=1000)

    #histograma frecventelor
    hist(X, bins = arange(0,6), density = True, rwidth = 0.9, color = 'green', edgecolor = 'black', alpha = 0.5, label = 'frecvente relative')
    pmf_val = binom.pmf(arange(0,6), n, p)
    bar(arange(0,6), pmf_val, width=0.85, color='red', edgecolor='black', alpha=0.6, label='probabilitati')
    legend(loc='lower left')
    grid()

    #estimare probabilitati
    P = binom.cdf(5, n, p) - binom.cdf(2, n, p)
    print("Estimare prob ", P)
    show()

#problema 4
def problema4():

    nr_simulari = 1000
    probabilitati = [sum(choices(range(1,7),k=3)) for _ in range(1000)]
    bin_edges = []
    hist(probabilitati, )
    bar(range(3,19), probabilitati[3:], width=0.6, color='red', edgecolor='black', alpha=0.6, label='probabilitati')
    legend(loc='lower left')
    grid()
    show()



# problema1()
# problema2()
#problema3()
problema4()