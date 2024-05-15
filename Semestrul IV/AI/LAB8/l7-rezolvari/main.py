generated_input = "The purple pride Which on thy sport, Cannot dispraise, but in the world's false subtleties."
text_input = "If not from my love's breath? The purple pride"

import nltk
from nltk.translate.bleu_score import sentence_bleu

nltk.download('punkt')


def calculate_bleu_score(text1, generated):
    generated_tokens = nltk.word_tokenize(generated.lower())  # tokenizare
    text_tokenized = nltk.word_tokenize(text1.lower())  # tokenizare pentru fiecare poezie din corpus
    bleu_scores = sentence_bleu([text_tokenized], generated_tokens)
    print(bleu_scores)


calculate_bleu_score(text_input, generated_input)
