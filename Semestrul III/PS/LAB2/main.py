#exercitiul 1
import random
from random import randint
from numpy.random import randint

#a
def simulari(nr_simulari, nr_persoane):
    k=0
    for _ in range (nr_simulari):
        zile = [randint(1,365) for _ in range (nr_persoane)]
        if(rn(zile)):
            k=k+1

    probabilitate = k/nr_simulari
    return probabilitate

def rn(zile):
    for i in range (len(zile)):
        for j in range(i+1, len(zile)):
            if zile[j] == zile[i]:
                return True
    return False

#b
def probabilitate(n):
    p = 1.0
    for i in range(n):
        p = p * (365-i)/365

    return 1-p

print(simulari(100,23))
print(probabilitate(23))
