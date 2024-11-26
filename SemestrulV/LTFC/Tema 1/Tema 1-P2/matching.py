# matching.py
def tokenizeaza(linie):
    # Simplă tokenizare folosind spații; îmbunătățită după necesități.
    return linie.split()

def este_token_valid(token):
    # Exemplu simplificat pentru validarea unui token.
    return token.isalnum()  # Considerăm tokenuri valide doar cele alfanumerice.
