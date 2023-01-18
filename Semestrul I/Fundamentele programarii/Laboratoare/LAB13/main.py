'''
created by @cosmin

Se dă un întreg pozitiv, găsiți toate descompunerile în sumă de numere prime.
'''

# varianta recursiva
def prime_recursiva(n, prime, start, suma, lista):

    if consistent(lista, suma, n):
        if solution(suma, n):
            print(lista)
            return

    if suma>n:
        return

    for i in range(start, len(prime)):
        prim = prime[i]
        lista.append(prim)
        prime_recursiva(n, prime, i, suma+prim, lista)
        lista.pop()

def solution(suma, n):
    return suma == n
def consistent(lista, suma, n):
    return len(lista)>=2

#iterativ
def prime_nerecursiva(n, prime):
    desc = [(0, [], 0)]

    while desc:
        suma, lista, start = desc.pop()

        if suma == n:
            print(lista)

        elif suma<n:
            for i in range(start, len(prime)):
                prim = prime[i]
                desc.append((suma+prim,lista+[prim],i))


def generare_prime(n):
    prime = []
    for numar in range(2, n):
        for prim in prime:
            if numar % prim == 0:
                break
        else:
            prime.append(numar)
    return prime

def main():
    prime = generare_prime(100)
    n = int(input())
    prime_recursiva(n, prime, 0, 0, [])
    print("\n")
    prime_nerecursiva(n, prime)

main()


