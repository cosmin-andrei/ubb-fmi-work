# pb1
import time


def pb1(text):
    start_time = time.perf_counter()

    cuvinte = text.split()
    cuvinte.sort()
    end_time = time.perf_counter()
    elapsed_time = end_time - start_time
    print("Elapsed time pb 1: ", elapsed_time)

    return cuvinte[-1]


# Exemplu de utilizare
text = "Ana are mere rosii si galbene"
ultim_cuv = pb1(text)
print("Ultimul cuvânt din punct de vedere alfabetic:", ultim_cuv)

# pb 2
import math

"""
    Calculează distanța Euclidiană între două puncte într-un spațiu bidimensional.

    Argumente:
    p1 (tuple): Coordonatele primului punct, de forma (x1, y1).
    p2 (tuple): Coordonatele celui de-al doilea punct, de forma (x2, y2).

    Returnează:
    float: Distanța Euclidiană între cele două puncte.
    """


def pb2(p1, p2):
    start_time = time.perf_counter()

    x1, y1 = p1
    x2, y2 = p2
    distanta = math.sqrt((x2 - x1) ** 2 + (y2 - y1) ** 2)

    end_time = time.perf_counter()
    elapsed_time = end_time - start_time
    print("Elapsed time pb 2: ", elapsed_time)

    return distanta


# Exemplu de utilizare
punct1 = (1, 5)
punct2 = (4, 1)
print("Distanța Euclidiană între", punct1, "și", punct2, "este", pb2(punct1, punct2))

# pb3
"""
    Calculează produsul scalar al doi vectori rari.

    Argumente:
    vector1 (list): Primul vector.
    vector2 (list): Al doilea vector.

    Returnează:
    float: Produsul scalar al celor doi vectori.
    """


def pb3(vector1, vector2):
    start_time = time.perf_counter()

    if len(vector1) != len(vector2):
        raise ValueError("Vectorii trebuie să aibă aceeași lungime")
    produs = 0
    for i in range(len(vector1)):
        produs += vector1[i] * vector2[i]

    end_time = time.perf_counter()
    elapsed_time = end_time - start_time
    print("Elapsed time pb 3: ", elapsed_time)

    return produs


# Exemplu de utilizare
vector1 = [1, 0, 2, 0, 3]
vector2 = [1, 2, 0, 3, 1]
print("Produsul scalar al celor doi vectori este:", pb3(vector1, vector2))

# pb4
"""
    Determină cuvintele care apar exact o singură dată într-un text.

    Argumente:
    text (str): Textul în care se caută cuvintele.

    Returnează:
    set: Un set cu cuvintele care apar o singură dată în text.
    """


def pb4(text):
    start_time = time.perf_counter()

    cuvinte = text.split()
    frecventa_cuvinte = {}
    for cuvant in cuvinte:
        frecventa_cuvinte[cuvant] = frecventa_cuvinte.get(cuvant, 0) + 1
    cuvinte_unice = {cuvant for cuvant, frecventa in frecventa_cuvinte.items() if frecventa == 1}

    end_time = time.perf_counter()
    elapsed_time = end_time - start_time
    print("Elapsed time pb 4: ", elapsed_time)

    return cuvinte_unice


# Exemplu de utilizare
text = "ana are ana are mere rosii ana"
print("Cuvintele care apar exact o singură dată în text sunt:", pb4(text))


# pb5
def pb5(nums):
    start_time = time.perf_counter()
    """
    Identifică valoarea care se repetă de două ori într-un șir.

    Argumente:
    nums (list): Șirul de numere.

    Returnează:
    int: Valoarea care se repetă de două ori în șir.
    """
    # Inițializăm un dicționar pentru a număra de câte ori apare fiecare valoare
    aparitii = {}

    alt = 0
    # Parcurgem lista de numere
    for num in nums:
        # Incrementăm numărul de apariții al fiecărei valori în dicționar
        aparitii[num] = aparitii.get(num, 0) + 1

        # Dacă o valoare are două apariții, o returnăm
        if aparitii[num] == 2:
            alt = num

    end_time = time.perf_counter()
    elapsed_time = end_time - start_time
    print("Elapsed time pb 5: ", elapsed_time)
    return alt


# Exemplu de utilizare
nums = [1, 2, 3, 4, 2]
print("Valoarea care se repetă de două ori în șir este:", pb5(nums))


# pb 6
def pb6(nums):
    start_time = time.perf_counter()
    """
    Determină elementul majoritar dintr-un șir de numere întregi.

    Argumente:
    nums (list): Șirul de numere întregi.

    Returnează:
    int: Elementul majoritar din șir. Dacă nu există, se returnează None.
    """
    # Inițializăm candidatul pentru elementul majoritar și contorul asociat
    candidat = None
    contor = 0

    # Parcurgem lista de numere
    for num in nums:
        # Dacă contorul este 0, stabilim noul candidat
        if contor == 0:
            candidat = num
            contor = 1
        # Altfel, dacă numărul curent este egal cu candidatul, incrementăm contorul
        elif num == candidat:
            contor += 1
        # Altfel, decrementăm contorul
        else:
            contor -= 1

    # Verificăm dacă candidatul este elementul majoritar
    contor = 0
    for num in nums:
        if num == candidat:
            contor += 1

    end_time = time.perf_counter()
    elapsed_time = end_time - start_time
    print("Elapsed time pb 6: ", elapsed_time)
    if contor > len(nums) // 2:
        return candidat
    else:
        return None


# Exemplu de utilizare
nums = [2, 8, 7, 2, 2, 5, 2, 3, 1, 2, 2]
print("Elementul majoritar din șir este:", pb6(nums))


# pb7
def pb7(nums, k):
    start_time = time.perf_counter()
    """
    Determină al k-lea cel mai mare element dintr-un șir de numere.

    Argumente:
    nums (list): Șirul de numere.
    k (int): Poziția elementului căutat (1 pentru cel mai mare, 2 pentru al doilea cel mai mare, etc.).

    Returnează:
    int: Al k-lea cel mai mare element din șir.
    """
    # Sortăm șirul în ordine descrescătoare
    nums.sort(reverse=True)
    end_time = time.perf_counter()
    elapsed_time = end_time - start_time
    print("Elapsed time pb 7: ", elapsed_time)
    # Returnăm al k-lea element
    return nums[k - 1]


# Exemplu de utilizare
nums = [7, 4, 6, 3, 9, 1]
k = 2
print(f"Al {k}-lea cel mai mare element din șir este:", pb7(nums, k))


def pb8(n):
    start_time = time.perf_counter()
    """
    Generează toate numerele în reprezentare binară cuprinse între 1 și n.

    Argumente:
    n (int): Numărul maxim până la care se generează numerele în reprezentare binară.

    Returnează:
    list: Lista cu toate numerele în reprezentare binară cuprinse între 1 și n.
    """
    # Inițializăm lista de numere în reprezentare binară
    numere_binar = []

    # Parcurgem fiecare număr de la 1 la n și îl adăugăm la listă în reprezentare binară
    for i in range(1, n + 1):
        numere_binar.append(bin(i)[2:])  # [2:] pentru a elimina prefixul '0b'

    end_time = time.perf_counter()
    elapsed_time = end_time - start_time
    print("Elapsed time pb 8: ", elapsed_time)
    return numere_binar


# Exemplu de utilizare
n = 4
print("Numerele în reprezentare binară cuprinse între 1 și", n, "sunt:", pb8(n))


# pb9
def pb9(matrice, liste_perechi):
    start_time = time.perf_counter()
    """
    Calculează suma elementelor din sub-matricele identificate de fiecare pereche de coordonate.

    Argumente:
    matrice (list): Matricea de numere întregi.
    liste_perechi (list): Lista de perechi de coordonate.

    Returnează:
    list: Lista cu sumele elementelor pentru fiecare pereche de coordonate.
    """
    sume = []

    for pereche in liste_perechi:
        suma_submatrice = 0
        p, q = pereche[0]
        r, s = pereche[1]

        for i in range(p, r + 1):
            for j in range(q, s + 1):
                suma_submatrice += matrice[i][j]

        sume.append(suma_submatrice)

    end_time = time.perf_counter()
    elapsed_time = end_time - start_time
    print("Elapsed time pb 9: ", elapsed_time)
    return sume


# Exemplu de utilizare
matrice = [
    [0, 2, 5, 4, 1],
    [4, 8, 2, 3, 7],
    [6, 3, 4, 6, 2],
    [7, 3, 1, 8, 3],
    [1, 5, 7, 9, 4]
]
liste_perechi = [((1, 1), (3, 3)), ((2, 2), (4, 4))]
print("Suma elementelor din sub-matricele identificate de fiecare pereche de coordonate:", pb9(matrice, liste_perechi))


def pb10(matrice):
    start_time = time.perf_counter()
    """
    Identifică indexul liniei care conține cele mai multe elemente de 1 într-o matrice binară.

    Argumente:
    matrice (list): Matricea binară cu elemente sortate crescător pe linii.

    Returnează:
    int: Indexul liniei care conține cele mai multe elemente de 1.
    """
    max_elemente_1 = 0
    index_linie_max = -1

    # Parcurgem fiecare linie și numărăm elementele de 1
    for i, linie in enumerate(matrice):
        elemente_1 = linie.count(1)
        if elemente_1 > max_elemente_1:
            max_elemente_1 = elemente_1
            index_linie_max = i

    end_time = time.perf_counter()
    elapsed_time = end_time - start_time
    print("Elapsed time pb 10: ", elapsed_time)
    return index_linie_max


# Exemplu de utilizare
matrice = [
    [0, 0, 0, 1, 1],
    [0, 1, 1, 1, 1],
    [0, 0, 1, 1, 1]
]
print("Indexul liniei care conține cele mai multe elemente de 1:", pb10(matrice))


def teste():
    # pb1
    assert pb1("Ana are mere rosii si galbene") == "si"
    assert pb1("Ana are mere rosii galbene") == "rosii"
    assert pb1("Maria are un nou telefon") == "un"

    # pb2
    assert pb2([1, 5], [4, 1]) == 5.0
    assert pb2([1, 10], [-5, 2]) == 10.0
    assert pb2([1, 2], [-5, 2]) == 6.0

    # pb3
    assert pb3([1, 0, 2, 0, 3], [1, 2, 0, 3, 1]) == 4
    assert pb3([0, 0, 2, 0, 3], [1, 2, 0, 3, 1]) == 3
    assert pb3([1, 1, 2, 0, 3], [1, 2, 0, 3, 1]) == 6

    # pb4
    assert pb4("ana are ana are mere rosii ana") == {'mere', 'rosii'}
    assert pb4("ana maria ana andrei larisa") == {'maria', 'andrei', 'larisa'}

    # pb 5
    assert pb5([1, 2, 3, 4, 2]) == 2
    assert pb5([2, 2]) == 2
    assert pb5([1, 2, 4, 2]) == 2

    # pb6
    assert pb6([2, 8, 7, 2, 2, 5, 2, 3, 1, 2, 2]) == 2
    assert pb6([1, 8, 7, 1, 5, 2, 1, 1, 1, 1]) == 1
    assert pb6([1, 0, 5, 5, 0]) is None

    # pb7
    assert pb7([7, 4, 6, 3, 9, 1], 2) == 7
    assert pb7([1, 1, 1, 1, 1], 3) == 1
    assert pb7([5, 4, 4, 2, 1], 3) == 4

    # pb8
    assert pb8(4) == ['1', '10', '11', '100']
    assert pb8(5) == ['1', '10', '11', '100', '101']
    assert pb8(2) == ['1', '10']

    # pb9
    assert pb9([[0, 2, 5, 4, 1],
                [4, 8, 2, 3, 7],
                [6, 3, 4, 6, 2],
                [7, 3, 1, 8, 3],
                [1, 5, 7, 9, 4]],
               [((1, 1), (3, 3)), ((2, 2), (4, 4))]) == [38, 44]
    assert pb9([[0, 2, 5],
                [4, 8, 2],
                [6, 3, 4]],
               [((0, 0), (1, 1)), ((1, 1), (2, 2))]) == [14, 17]

    # pb10
    assert pb10([[0, 0, 0, 1, 1], [0, 1, 1, 1, 1], [0, 0, 1, 1, 1]]) == 1
    assert pb10([[0, 0, 0, 1, 1], [0, 1, 1, 1, 1], [1, 1, 1, 1, 1]]) == 2
    assert pb10([[0, 0, 1, 1, 1, 1], [0, 0, 0, 0, 1, 1], [0, 0, 0, 0, 1, 1], [0, 0, 0, 0, 1]]) == 0

    print("totul merge bine")


teste()
