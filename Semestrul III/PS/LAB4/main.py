# problema 1
# Un punct material se deplaseaz  pe axa real  dintr-un nod spre un nod vecin, la ecare pas,
# cu probabilitatea p ∈ (0, 1) la dreapta ³i cu probabilitea 1 − p la stânga. Nodurile sunt centrate în
# numerele întregi, iar nodul iniµial este 0:
from random import random, sample

import numpy as np
from matplotlib import pyplot as plt
from scipy.stats import bernoulli, binom
from scipy.stats import hypergeom, geom


# a
def mersaleator(p, nr_pasi):
    pozitii = [0]

    for _ in range(nr_pasi):
        x = bernoulli.rvs(p)
        pas = 2 * x - 1
        pozitii.append(pozitii[-1] + pas)

    return pozitii


nr_pasi = 10
p = 0.5
pozitii = mersaleator(p, nr_pasi)
print(pozitii)


# b

def simulari_multiple(nr_simulari, nr_pasi, p):
    pozitii_finale = []

    for _ in range(nr_simulari):
        pozitii = mersaleator(p, nr_pasi)
        pozitii_finale.append(pozitii[-1])

    plt.hist(pozitii_finale, bins=range(min(pozitii_finale), max(pozitii_finale) + 2))
    plt.show()


nr_simulari = 1000
nr_pasi = 10
p = 0.6
simulari_multiple(nr_simulari, nr_pasi, p)


# c
def simulari_cerc(nr_simulari, nr_pasi, p, nr_noduri):
    pozitii_finale = []

    for _ in range(nr_simulari):

        poz = 0

        # simulez deplasarea pe cerc
        for _ in range(nr_pasi):
            move_right = np.random.rand() < p
            poz = (poz + 1) % nr_noduri if move_right else (poz - 1) % nr_noduri
        pozitii_finale.append(poz)

    plt.hist(pozitii_finale, bins=range(nr_noduri + 1), align='left', edgecolor='black')
    plt.show()


simulari_cerc(nr_simulari, nr_pasi, p, 10)

# generaµi o list  care conµine, pentru ecare simulare, num rul de bilete necâ³tig toare (care au cel
# mult 2 numere câ³tig toare) pân  la primul bilet câ³tig tor (care are cel puµin 3 numere câ³tig toare).

# 2 Un juc tor de Loto 6/49 î³i cump r  câte un bilet pentru ecare extrage efectuat  de loteria
# român  pân  când reu³e³te s  nimereasc  un bilet cu cel puµin 3 numere câ³tig toare. Folosind
# metodele claselor de mai jos,

# a generaµi o list  care conµine, pentru ecare simulare, num rul de bilete necâ³tig toare (care au cel
# mult 2 numere câ³tig toare) pân  la primul bilet câ³tig tor (care are cel puµin 3 numere câ³tig toare).

# probabilitate bilet castigator
probabilitate_c = 0
for k in range(3, 7):
    prob = hypergeom.pmf(k, 49, 6, 6)
    probabilitate_c = probabilitate_c + prob

necastigator = geom.rvs(probabilitate_c, size=1000)

prim_castig = 1 - geom.cdf(9, probabilitate_c)
print(prim_castig)

p_simulat = sum(x >= 10 for x in necastigator)
print(p_simulat / 1000)

# b
# p = sum(1 for l in necastigator if l>=10) / nr_simulari
# p_teoretica = (1-1)
