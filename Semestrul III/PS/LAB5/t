#pb 1
from scipy.stats import uniform

def generare_numere_pseudo_aleatoare(N, a, b):
    # Generăm N numere pseudo-aleatoare conform distribuției uniforme
    numere_aleatoare = uniform.rvs(loc=a, scale=b-a, size=N)

    return numere_aleatoare

# Exemplu de utilizare cu distribuție uniformă
a = 1  # Limita inferioară a intervalului
b = 5  # Limita superioară a intervalului

N = 10  # Numărul de numere pseudo-aleatoare dorite
rezultat = generare_numere_pseudo_aleatoare(N, a, b)

print("Numere pseudo-aleatoare generate:", rezultat)


#pb 2
import matplotlib.pyplot as plt
import numpy as np

def simuleaza_grupa_sanguina(N):
    # Probabilități date pentru fiecare grupă sanguină
    probabilitati = [0.46, 0.40, 0.10, 0.04]
    grupe_sanguine = ['0', 'A', 'B', 'AB']

    # Simulează N observări aleatoare ale grupei sanguine
    observatii = np.random.choice(grupe_sanguine, size=N, p=probabilitati)

    # Calculează frecvența relativă a apariției fiecărei grupe sanguine
    frecventa_relativa = {grupa: np.sum(observatii == grupa) / N for grupa in grupe_sanguine}

    # Afișează histograma
    plt.bar(frecventa_relativa.keys(), frecventa_relativa.values(), align='center', alpha=0.7, label='Observat')

    # Afișează probabilitățile teoretice
    plt.plot(grupe_sanguine, probabilitati, 'ro-', label='Teoretic')

    plt.xlabel('Grupa sanguina')
    plt.ylabel('Frecventa relativa')
    plt.legend()
    plt.show()

# Exemplu de utilizare
N = 1000  # Numărul de simulări
simuleaza_grupa_sanguina(N)


#pb2
from scipy.stats import uniform
import matplotlib.pyplot as plt
import numpy as np

def generate_exp(N, alpha):
    # Generăm N numere pseudo-aleatoare conform distribuției uniforme
    numere_aleatoare_uniforme = uniform.rvs(size=N)

    # Calculăm inversa funcției distribuției cumulative a exponentialului
    numere_aleatoare_exponentiale = -alpha * np.log(1 - numere_aleatoare_uniforme)

    return numere_aleatoare_exponentiale

# Parametrii distribuției Exponential(α)
alpha = 2.0
N = 1000

# Generăm N numere pseudo-aleatoare conform distribuției Exponential(α)
random_numbers = generate_exp(N, alpha)

# Afișăm histograma rezultatelor pentru a verifica distribuția
plt.hist(random_numbers, bins=50, density=True, alpha=0.7, color='blue', edgecolor='black')
plt.title('Histograma generată')
plt.xlabel('Valoare')
plt.ylabel('Frecvență relativă')
plt.show()


