import random
from random import sample
from math import factorial
from itertools import permutations, combinations


#2
#a o lista cu toate permutarile cuvantului word
#b numar total permutari

def permutari():
    p = list(permutations("word"))
    k=0

    permutare_random = random.choice(p)
    print(permutare_random)
    for perm in p:
        print(perm)
        k=k+1
    print("Nr total permutari ", k)


permutari()


def aranjamente():

    p=list(permutations("cuvant",2))
    for i in p:
        print(i)

aranjamente()

print("\n")
def combinari():
    p=list(combinations("word", 2))
    for i in p:
        print(i)

combinari()


