#1
from math import log
from random import random

import numpy as np
from numpy import random
from matplotlib import pyplot as plt
from scipy.stats import uniform, expon
from matplotlib.pyplot import bar, show, hist, grid, legend, xticks, yticks, plot

#pseudo aleatoare
def generare_numere(x, p, N):
   return random.choice(x, N, p=p)

def simulare_sanguina(N):
    valori = ['0','A','B','AB']
    probabilitati = [0.46, 0.40, 0.10, 0.04]

    U = generare_numere(valori, probabilitati, N)

    frecventa = {}
    for grupa in valori:
        frecventa[grupa] = np.sum(U == grupa) / N

    plt.bar(frecventa.keys(), frecventa.values(), align='center', alpha=0.7)
    plt.bar(valori, probabilitati, width=0.5)
    plt.xlabel('Grupa')
    plt.ylabel('Frecventa')
    plt.show()

simulare_sanguina(1000)



#2i
#valori pseudo aleatoare
def func(alpha, N):
    U = uniform.rvs(size=N)
    X = [-1/alpha*log(1-U[i]) for i in range(N)]
    return X

def i_afis():
    alpha = 1/12
    data = func(alpha, 1000)
    plt.hist(data, bins=12, density = True,range=(0,60))
    x = range(60)
    plt.plot(x,expon.pdf(x,loc=0,scale=1/alpha),'r-')
    xticks(range(0,60,5))
    grid()
    show()

i_afis()

#2ii

def estimare_ii(N):
    alpha=1/12
    X=func(alpha, N)
    count=0
    for i in range (N):
        if X[i]>=5:
            count = count + 1
    print(count/N)
    prob = 1-expon.cdf(5, loc=0, scale=1/alpha)
    print(prob)


estimare_ii(1000)
