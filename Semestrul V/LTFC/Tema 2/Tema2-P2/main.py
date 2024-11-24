from AF import AF
from Tranzitie import Tranzitie


def read_file(filename):
    cuvinte = []
    with open(filename, 'r') as f:
        lines = f.readlines()
        for line in lines:
            cuvinte.extend(normalize_line(line))

    return cuvinte


# elimin spatii inutile
def normalize_line(line):
    separatori = ['(', ')', '{', '}', ';', '!=', '>>', '<<', '-', '+', '==', '>', '<', '=']
    rezultat = []
    cuvant = ""
    i = 0

    while i < len(line):
        if line[i].isspace():  # ignore spaces
            if cuvant:
                rezultat.append(cuvant)
                cuvant = ""
        elif line[i:i + 2] in separatori:  # operatori cu 2 caract
            if cuvant:
                rezultat.append(cuvant)
                cuvant = ""
            rezultat.append(line[i:i + 2])
            i += 1
        elif line[i] in separatori:
            if cuvant:
                rezultat.append(cuvant)
                cuvant = ""
            rezultat.append(line[i])
        else:
            cuvant += line[i]
        i += 1

    if cuvant:
        rezultat.append(cuvant)

    return rezultat


def read_keywords(filename):
    keywords = {}
    with open(filename, 'r') as f:
        lines = f.readlines()
        for line in lines:
            splits = line.split(":")
            keywords[splits[1].strip()] = splits[0].strip()

    return keywords


def write_to_file(result, filename):
    with open(filename, 'w') as f:
        for key, value in result.items():
            f.write(f"{key}: {value}\n")


def is_identifier(atom: str) -> bool:
    return AF_identificatori.verifica_stare(atom)


def is_constant(atom: str) -> bool:
    return AF_intregi.verifica_stare(atom) or AF_reale.verifica_stare(atom)


def verifyCode(filename):
    keywords = change_key_value(read_keywords('keywords.txt'))
    contor = 0
    with open(filename, 'r') as f:
        lines = f.readlines()
        for line in lines:
            contor += 1
            cuvinte = normalize_line(line)
            for cuv in cuvinte:
                cuv = cuv.strip()
                if not is_identifier(cuv) and not is_constant(cuv) and cuv not in keywords:
                    print(f"Eroare la linia {contor}: simbol invalid -> '{cuv}'")
                    break

    keywords = read_keywords('keywords.txt')
    for cuv in read_file("input.txt"):
        if not is_identifier(cuv) and not is_constant(cuv):
            if cuv not in keywords:
                return False,

    return True


ts_ID = []
ts_const = []


def binary_search(arr, low, high, x):
    if high >= low:
        mid = (high + low) // 2
        if arr[mid] == x:
            return mid
        elif arr[mid] > x:
            return binary_search(arr, low, mid - 1, x)
        else:
            return binary_search(arr, mid + 1, high, x)

    else:
        return low


def ts_id_const():
    cuv = read_file("input.txt")
    keywords = read_keywords("keywords.txt")

    for cuvant in cuv:
        if cuvant not in keywords.values():
            if is_identifier(cuvant):
                if cuvant not in ts_ID:
                    poz = binary_search(ts_ID, 0, len(ts_ID) - 1, cuvant)
                    ts_ID.insert(poz, cuvant)

            if is_constant(cuvant):
                if cuvant not in ts_const:
                    poz = binary_search(ts_const, 0, len(ts_const) - 1, cuvant)
                    ts_const.insert(poz, cuvant)


def change_key_value(keywords):
    # inversare cheie-valoare
    return {value.strip(): key.strip() for key, value in keywords.items()}


def FIP():
    cuv = read_file("input.txt")
    keywords = read_keywords("keywords.txt")
    keywords = change_key_value(keywords)

    result = []

    for cuvant in cuv:
        if cuvant in keywords:
            result.append(f"{keywords[cuvant]} : -1")
        elif cuvant in ts_ID:
            position = ts_ID.index(cuvant)
            result.append(f"1 : {position}")
        elif cuvant in ts_const:
            position = ts_const.index(cuvant)
            result.append(f"2 : {position}")
        else:
            result.append(f": -1")

    with open("fip.txt", 'w') as f:
        for entry in result:
            f.write(f"{entry}\n")


def split_line(lista, linie):
    while linie:
        cuvant, _, linie = linie.partition(',')
        lista.append(cuvant)


def citeste_fisier(nume_fisier):
    alph = []
    staa = []
    st_final = []
    tran = []

    with open(nume_fisier, "r") as file:
        split_line(alph, file.readline().strip())
        split_line(staa, file.readline().strip())
        st_init = file.readline().strip()
        split_line(st_final, file.readline().strip())

        for line in file:
            source_state, line = line.split(",", 1)
            destination_state, value = line.split(",", 1)
            tran.append(Tranzitie(source_state, destination_state, value.strip()))

    return alph, staa, st_init, st_final, tran


def main():
    read_file("input.txt")
    verifyCode("input.txt")

    ts_id_const()
    ts_ID_map = {element: index for index, element in enumerate(ts_ID)}
    ts_const_map = {element: index for index, element in enumerate(ts_const)}
    write_to_file(ts_ID_map, "ts_ID.txt")
    write_to_file(ts_const_map, "ts_const.txt")
    FIP()


if __name__ == "__main__":
    alfabet, stari, stare_initiala, stari_finale, tranzitii = citeste_fisier("af/gramatica_intregi.txt")
    AF_intregi = AF(alfabet, stari, stare_initiala, tranzitii, stari_finale)
    alfabet2, stari2, stare_initiala2, stari_finale2, tranzitii2 = citeste_fisier("af/gramatica_reale.txt")
    AF_reale = AF(alfabet2, stari2, stare_initiala2, tranzitii2, stari_finale2)
    alfabet3, stari3, stare_initiala3, stari_finale3, tranzitii3 = citeste_fisier("af/gramatica_identificatori.txt")
    AF_identificatori = AF(alfabet3, stari3, stare_initiala3, tranzitii3, stari_finale3)
    main()
