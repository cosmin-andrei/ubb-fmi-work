"""Se da un fisier care contine un text (format din mai multe propozitii) in limba romana - a se vedea fisierul
”data/texts.txt”. Se cere sa se determine si sa se vizualizeze:

numarul de propozitii din text;
numarul de cuvinte din text
numarul de cuvinte diferite din text
cel mai scurt si cel mai lung cuvant (cuvinte)
textul fara diacritice
sinonimele celui mai lung cuvant din text
"""
import string

import spacy
import unidecode as uni
import nltk as nl
import rowordnet as rwn

'''
NLTK (Natural Language Toolkit)
- tokenizeaza propozitiile intr-un text
- divizeaza textul in cuvinte
'''

'''
propozitii(text) -> int
text: str
returneaza numarul de propozitii din text
'''


def propozitii(text):
    # nl.download('punkt')
    sentences = nl.tokenize.sent_tokenize(text)
    return len(sentences)


'''
cuvinte(text) -> int
text: str
returneaza numarul de cuvinte din text
'''


def cuvinte(text):
    words = nl.tokenize.word_tokenize(text)
    words = [word for word in words if word not in string.punctuation]
    return len(words)


'''
cuvinte_dif(text) -> int
text: str
returneaza numarul de cuvinte diferite din text
'''


def cuvinte_dif(text):
    words = nl.tokenize.word_tokenize(text)
    words = [word for word in words if word not in string.punctuation]
    words = [word.lower() for word in words]
    words_unice = set(words)
    return len(words_unice)


'''
minim(text) -> str
text: str
returneaza cel mai scurt cuvant din text
'''


def minim(text):
    words = nl.tokenize.word_tokenize(text)
    words = [word for word in words if word not in string.punctuation]
    min_word = min(words, key=len)
    return min_word


'''
maxim(text) -> str
text: str
returneaza cel mai lung cuvant din text
'''


def maxim(text):
    words = nl.tokenize.word_tokenize(text)
    words = [word for word in words if word not in string.punctuation]
    max_word = max(words, key=len)
    return max_word


'''
fara_diacritice(text) -> str
text: str
returneaza textul fara diacritice

translateaza textul in cod ascii
'''


def fara_diacritice(text):
    return uni.unidecode(text)


'''
lemma(cuvant) -> list
cuvant: str'''


def lemma(cuvant):
    nlp = spacy.load('ro_core_news_sm')
    doc = nlp(cuvant)
    return [token.lemma_ for token in doc]


'''
sinonime(text) -> list
text: str
returneaza sinonimele celui mai lung cuvant din text'''


def sinonime(text):
    word = maxim(text)
    wn = rwn.RoWordNet()
    doc = lemma(word)[0]
    synset_ids = wn.synsets(literal=str(doc))
    synonyms = []
    for synset_id in synset_ids:
        synset = wn.synset(synset_id)
        for literal in synset.literals:
            if literal != str(doc):
                synonyms.append(literal)
    return synonyms


'''
main()
citeste textul din fisier
apeleaza functiile de mai sus
afiseaza rezultatele
'''


def main():
    with open("texts.txt", "r", encoding="utf-8") as file:
        text = file.read()

    print("Numar propozitii text: ", propozitii(text))
    print("Numar cuvinte text: ", cuvinte(text))
    print("Numar cuvinte dif text: ", cuvinte_dif(text))
    print("Cel mai scurt cuvant din text: ", minim(text))
    print("Cel mai lung cuvant din text: ", maxim(text))
    print(fara_diacritice(text))
    print("Sinonimele celui mai lung cuvant din text: ", sinonime(text))


main()


def teste():
    text = """Mesaj de informare: 
    Cursul și laboratoarele de Inteligență Artificială vor fi o 
    provocare pentru toți. Suntem convinși că veți realiza proiecte 
    foarte interesante. Vă încurajăm să adresați întrebări atunci 
    când ceva nu e clar, atât în mod live, cât și folosind platforma 
    Teams, canalul ”general”. 
    Dacă ați citit până aici, vă rugăm să lăsați un mesaj pe canalul 
    general cu textul ”Am citit textul pentru problema 3”. 
    Mesaj de informare generat de ChatGPT:
    Stimați cursanți,
    Suntem încântați să vă avem în echipa noastră pentru Cursul și 
    laboratoarele de Inteligență Artificială. Această experiență va 
    fi o adevărată provocare, dar suntem convinși că veți realiza 
    proiecte extrem de interesante.
    Vă încurajăm să fiți activi și să adresați întrebări atunci când 
    ceva nu este clar. Fie că este vorba de o discuție în timp real 
    sau prin intermediul platformei Teams, canalul ”general”, suntem 
    aici să vă sprijinim.
    Succes și să înceapă aventura AI!
    Cu considerație, Echipa de Inteligență Artificială"""

    assert propozitii(text) == 10
    assert cuvinte(text) == 162
    assert cuvinte_dif(text) == 90
    assert minim(text) == "o"
    assert maxim(text) == "laboratoarele"


teste()
