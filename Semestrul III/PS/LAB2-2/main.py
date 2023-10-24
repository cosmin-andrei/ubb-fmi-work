from matplotlib.pyplot import axis, plot
from random import random, uniform
from math import dist

A, B, C, D, E = [0,0], [1,0], [1,1], [0,1], [0.5, 0.5]


#a
def genereaza_puncte(N):
    puncte=[]
    for _ in range (N):
        x= uniform(0,1)
        y= uniform(0,1)
        puncte.append([x,y])
    return puncte

def in_cerc(punct):
    x, y = punct
    P = [x,y]
    #vector distanta
    return dist(P,E)<=0.5;

def ii(punct):
    x, y = punct
    P = [x,y]
    distanta_centru = dist(E,P)
    distanta_colturi = min(dist(A,P), dist(B,P), dist(C,P), dist(D,P))
    return distanta_centru<distanta_colturi




N_valori = [500,1000,2000]

for N in N_valori:
    puncte = genereaza_puncte(N)
    cerc = sum(1 for punct in puncte if in_cerc(punct))
    print(cerc/N)
    print("\n")
    patrat = sum(1 for punct in puncte if ii(punct))
    print(patrat/N)

