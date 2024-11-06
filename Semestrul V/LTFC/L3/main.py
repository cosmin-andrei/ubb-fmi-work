import re

cod_atom = {
    "if": "1", "else": "2", "while": "3", "+": "4", "-": "5",
    "*": "6", "=": "7", "==": "8", "!=": "9", "<=": "10", ">=": "11",
    "<": "12", ">": "13", "(": "14", ")": "15",
    "{": "16", "}": "17", ";": "18", "<<": "19", ">>": "20",
    "int": "21", "cin": "22", "cout": "23", "endl": "24"
}


def remove_comments(line):
    """Elimină comentariile dintr-o linie."""
    line = re.sub(r'//.*$', '', line)  # Elimină comentariile de o linie
    line = re.sub(r'/\*.*?\*/', '', line, flags=re.DOTALL)  # Elimină comentariile pe mai multe linii
    return line


def lexical_analysis(file_path):
    try:
        with open(file_path, "r") as file:
            lines = file.readlines()
    except FileNotFoundError:
        print("Eroare la deschiderea fișierului!")
        return

    token_regex = re.compile(r"[a-zA-Z_]\w*|\d+|[+\-*/=(){};<>]|(==)|(!=)|(<=)|(>=)|(<<)|(>>)")
    invalid_token_regex = re.compile(r"[^\s\w+\-*/=(){};<>]")

    for line_number, line in enumerate(lines, start=1):
        line = remove_comments(line).strip()

        if not line:
            continue

        tokens = [match[0] for match in token_regex.findall(line) if match[0]]
        invalid_tokens = invalid_token_regex.findall(line)

        for token in tokens:
            if token not in cod_atom:
                if re.match(r"\d+", token) or re.match(r"[a-zA-Z_]\w*", token):
                    add_to_ts(token)

        for invalid_token in invalid_tokens:
            print(f"Eroare lexicală la linia {line_number}: {invalid_token}")

    for line_number, line in enumerate(lines, start=1):
        line = remove_comments(line).strip()

        if not line:
            continue

        tokens = [match[0] for match in token_regex.findall(line) if match[0]]

        for token in tokens:
            if token in cod_atom:
                add_to_fip(cod_atom[token], -1)
            elif re.match(r"\d+", token) or re.match(r"[a-zA-Z_]\w*", token):
                position = add_to_ts(token)
                add_to_fip("0", position)

fip = []

def add_to_fip(token, position):
    fip.append((token, position))

def save_fip(file_path):
    with open(file_path, "w") as fip_file:
        for entry in fip:
            fip_file.write(f"{entry[0]} {entry[1] if entry[1] != -1 else '-'}\n")

# ts.py
ts_map = {}
position_counter = 0


def add_to_ts(symbol):
    """Adaugă un simbol în tabela de simboluri (TS) și returnează poziția."""
    global position_counter
    if symbol in ts_map:
        return ts_map[symbol]

    position_counter += 1
    ts_map[symbol] = position_counter
    return position_counter


def save_ts(file_path):
    """Salvează TS în fișierul specificat."""
    with open(file_path, "w") as ts_file:
        for position, symbol in sorted(ts_map.items(), key=lambda x: x[1]):
            ts_file.write(f"{position} {symbol}\n")


if __name__ == "__main__":
    file_path = "cod.txt"
    lexical_analysis(file_path)
    save_fip("FIP.txt")
    save_ts("TS.txt")

    print("FIP și TS au fost salvate.")
