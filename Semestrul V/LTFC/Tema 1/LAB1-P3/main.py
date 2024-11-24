import re


def read_file(filename):
    cuvinte = []
    with open(filename, 'r') as f:
        lines = f.readlines()
        for line in lines:
            cuvinte.extend(line.split())

    return cuvinte


def read_keywords(filename):
    keywords = {}
    with open(filename, 'r') as f:
        lines = f.readlines()
        for line in lines:
            splits = line.split(":")
            keywords[splits[1]] = splits[0]

    return keywords


# result - map
def write_to_file(result, filename):
    with open(filename, 'w') as f:
        for key, value in result.items():
            f.write(f"{key}: {value}\n")


identifier_pattern = re.compile(r'^[a-zA-Z]{3}\w*$|^[a-zA-Z]{1,2}$')
constant_pattern = re.compile(r'^\d+\.\d+$|^\b\d{1,10}\b$|^"[^"]*"\s*<\s*[0-9]+\.[0-9]+\s*,\s*[0-9]+\.[0-9]+\s*>$')


def is_identifier(atom: str) -> bool:
    return identifier_pattern.match(atom) is not None


def is_constant(atom: str) -> bool:
    return constant_pattern.match(atom) is not None


def verifyCode(filename):
    keywords = change_key_value(read_keywords('keywords.txt'))
    contor =0
    with open(filename, 'r') as f:
        lines = f.readlines()
        for line in lines:
            contor += 1
            cuvinte = line.split()
            for cuv in cuvinte:
                cuv = cuv.strip()
                if not is_identifier(cuv) and not is_constant(cuv) and cuv not in keywords:
                     print(cuv)
                     print("Eroare la linia ", contor)
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
    # inverseaza cheile cu valorile
    keywords = {value: key for key, value in keywords.items()}
    for key, value in keywords.items():
        keywords[key] = value[:-1]
    return keywords


def FIP():
    cuv = read_file("input.txt")
    keywords = read_keywords("keywords.txt")
    keywords = change_key_value(keywords)
    print(keywords)
    result = []

    for i in range(0, len(cuv), 2):
        if i + 1 < len(cuv):
            if cuv[i] in keywords.keys() and (cuv[i + 1] in ts_const or cuv[i + 1] in ts_ID):
                if cuv[i + 1] in ts_const:
                    # indicele din ts_const
                    position = ts_const.index(cuv[i + 1])
                    result.append(keywords[cuv[i]])
                    result.append(position)
                if cuv[i + 1] in ts_ID:
                    position = ts_ID.index(cuv[i + 1])
                    result.append(keywords[cuv[i]])
                    result.append(position)
            else:
                if cuv[i] in keywords.keys() and not (cuv[i + 1] in ts_const or cuv[i + 1] in ts_ID):
                    result.append(keywords.get(cuv[i]))
                    result.append("-1")

    with open("fip.txt", 'w') as f:
        for i in range(0, len(result), 2):
            if i + 1 < len(result):
                f.write(f"{result[i]} : {result[i + 1]}\n")


def main():
    verifyCode("input.txt")
    ts_id_const()
    ts_ID_map = {element: index for index, element in enumerate(ts_ID)}
    ts_const_map = {element: index for index, element in enumerate(ts_const)}
    write_to_file(ts_ID_map, "ts_ID.txt")
    write_to_file(ts_const_map, "ts_const.txt")
    FIP()


if __name__ == "__main__":
    main()
