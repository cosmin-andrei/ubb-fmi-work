# 5 Pentru un șir cu n elemente care conține valori din mulțimea {1, 2, ..., n - 1}
# astfel încât o singură valoare se repetă de două ori, să se identifice acea valoare care se repetă.
# De ex. în șirul [1,2,3,4,2] valoarea 2 apare de două ori.

# lab1(n, v)
# n - numar de elemente din v
# v - vectorul de elemente
# returneaza valoarea care se repeta de doua ori in sirul v de doua ori
def pb5(n, v):
    vf = [0] * (n + 1)
    i = 0
    while i < n:
        if vf[v[i]] == 1:
            return v[i]
        else:
            vf[v[i]] = vf[v[i]] + 1
        i += 1


# 7. Să se determine al k-lea cel mai mare element al unui șir de numere cu n elemente (k < n). De ex. al 2-lea cel
# mai mare element din șirul [7,4,6,3,9,1] este 7.

# mergesort(v)
# v - vectorul pe care il sortez
# returneaza vectorul sortat prin merge sort
def mergesort(v):
    if len(v) > 1:
        m = len(v) // 2  # practic aici imi imparte intreg
        left = v[:m]
        right = v[m:]

        mergesort(left)
        mergesort(right)

        i = 0
        j = 0
        k = 0

        while i < len(left) and j < len(right):
            if left[i] <= right[j]:
                v[k] = left[i]
                i = i + 1
            else:
                v[k] = right[j]
                j = j + 1
            k = k + 1

        while i < len(left):
            v[k] = left[i]
            i = i + 1
            k = k + 1

        while j < len(right):
            v[k] = right[j]
            j = j + 1
            k = k + 1


# pb7(k, v)
# k - pozitia elementului din vector
# v - vectorul de elemente
# returneaza al k-lea element cel mai mare din vectorul v
def pb7(k, v):
    mergesort(v)
    return v[len(v) - k]


# 2. Să se determine distanța Euclideană între două locații identificate prin perechi de numere. De ex. distanța
# între (1,5) și (4,1) este 5.0

# returneaza distanta dintre cele doua puncte prin calcularea cu formula lui euclid

def pb2(a, b):
    return ((a[0] - b[0]) ** 2 + (a[1] - b[1]) ** 2) ** 0.5


# 3. Să se determine produsul scalar a doi vectori rari care conțin numere reale. Un vector este rar atunci când
# conține multe elemente nule. Vectorii pot avea oricâte dimensiuni. De ex. produsul scalar a 2 vectori
# unisimensionali [1,0,2,0,3] și [1,2,0,3,1] este 4.

# pb3(v1, v2)
# v1 - un vector
# v2 - al doilea vector
# returneaza produsul scalar a doi vectori
def pb3(v1, v2):
    i = 0
    s = 0

    while i < len(v1):
        s = s + v1[i] * v2[i]
        i += 1

    return s


# 4. Să se determine cuvintele unui text care apar exact o singură dată în acel text. De ex. cuvintele care apar o
# singură dată în ”ana are ana are mere rosii ana" sunt: 'mere' și 'rosii'.

# pb4(text)
# text - o propozitie
# returneaza un vector de cuvinte, care apar o singura data in propozitie

def pb4(text):
    text = text.strip()
    text = text.split()
    fr = {}
    for cuv in text:
        if cuv in fr.keys():
            fr[cuv] = fr[cuv] + 1
        else:
            fr[cuv] = 1

    return [c for c in fr if fr[c] == 1]


def teste():
    # lab1
    assert pb5(5, [1, 2, 3, 4, 2]) == 2
    assert pb5(2, [2, 2]) == 2
    assert pb5(4, [1, 2, 4, 2]) == 2

    # pb7
    assert pb7(2, [7, 4, 6, 3, 9, 1]) == 7
    assert pb7(3, [1, 1, 1, 1, 1]) == 1
    assert pb7(3, [5, 4, 4, 2, 1]) == 4

    # pb2
    assert pb2([1, 5], [4, 1]) == 5.0
    assert pb2([1, 10], [-5, 2]) == 10.0
    assert pb2([1, 2], [-5, 2]) == 6.0

    # pb3
    assert pb3([1, 0, 2, 0, 3], [1, 2, 0, 3, 1]) == 4
    assert pb3([0, 0, 2, 0, 3], [1, 2, 0, 3, 1]) == 3
    assert pb3([1, 1, 2, 0, 3], [1, 2, 0, 3, 1]) == 6

    # pb4
    assert pb4("ana are ana are mere rosii ana") == ['mere', 'rosii']
    assert pb4("ana maria ana andrei larisa") == ['maria', 'andrei', 'larisa']

    print("toate testele merg ok")


teste()
