from random import sample
from math import factorial
import random
from math import perm, comb
from itertools import permutations, combinations


def permutari():
    print("---Permutari---")
    p = permutations("word")
    k = 0
    arr = random.choice(list(p))
    print(arr)
    for i in list(p):
        print(i)
        k = k + 1
    print("Numar de permutari", k)

def aranjamente(word, n, numar_total=False, aleator=False):
    print("\n---Aranjamente---")
    p=permutations(word,n)
    if numar_total==True:
        k=0
        for i in list(p):
           k=k+1
        print(k)
    elif aleator==True:
        arr=random.choice(list(p))
        print(arr)
    else:
        for i in list(p):
            print(i)

def combinari(word, n, numar_total=False, aleator=False):
    print("\n---Combinari---")
    p=combinations(word,n)
    if numar_total==True:
        k=0
        for i in list(p):
           k=k+1
        print(k)
    elif aleator==True:
        arr=random.choice(list(p))
        print(arr)
    else:
        for i in list(p):
            print(i)

permutari()
aranjamente("word", 2)
aranjamente('word',2,numar_total=True)
aranjamente('word',2,aleator=True)
combinari("word", 2)
combinari("word", 2, numar_total=True)
combinari("word", 2, aleator=True)