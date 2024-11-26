# main.py
from FIP import adauga_in_fip, obtine_fip
from matching import tokenizeaza, este_token_valid


def analizeaza_cod_sursa(cale_intrare, cale_iesire):
    with open(cale_intrare, "r") as fisier_intrare:
        cod_sursa = fisier_intrare.readlines()

    with open(cale_iesire, "w") as fisier_iesire:
        for linie_nr, linie in enumerate(cod_sursa, start=1):
            tokenuri = tokenizeaza(linie)
            for token in tokenuri:
                if este_token_valid(token):
                    adauga_in_fip(token, linie_nr)
                else:
                    fisier_iesire.write(f"Eroare lexicala: token invalid '{token}' la linia {linie_nr}\n")

        # Scrierea FIP-ului în fișierul de ieșire
        fisier_iesire.write("FIP:\n")
        for token, linie in obtine_fip():
            fisier_iesire.write(f"{token} - linia {linie}\n")


if __name__ == "__main__":
    analizeaza_cod_sursa("program.txt", "rezultat.txt")
