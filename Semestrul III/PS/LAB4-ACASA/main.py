import numpy as np
import matplotlib.pyplot as plt

#problema 1

#Un punct material se deplaseaza  pe axa reala  dintr-un nod spre un nod vecin, la fiecare pas, cu probabilitatea p ∈ (0, 1) la dreapta si cu probabilitea 1 − p la stânga. Nodurile sunt centrate în
#numerele întregi, iar nodul initial este 0:
#a) Simulati o astfel de deplasare cu numar dat de pasi, cu probabilitatea p ∈ (0, 1), si returnati
#pozitiile curente la fieecare pas
def simulate_displacement(num_steps, probability):
    #Initializez pozitia curenta pe axa reala cu 0 si creez o lista pt a stoca pozitiile
    current_position = 0
    positions = [current_position]

    #iterez prin numarul de pasi
    for _ in range(num_steps):

        #generez o valoare aleatoare intre 0 si 1 pentru a decide daca ma deplasez la dreapta sau la stanga
        move_right = np.random.rand() < probability

       #actualizez pozitia curenta
        current_position = current_position + 1 if move_right else current_position - 1

       #adaug pozitia curenta
        positions.append(current_position)

    #returnez lista de pozitii
    return positions

# Exemplu de utilizare:
num_steps = 10
probability = 0.7
positions = simulate_displacement(num_steps, probability)
print(positions)


#b) Simulati de 1000 ori o astfel de deplasare cu un numar dat de pasi, cu probabilitatea p ∈ (0, 1), si afisati histograma pozitiilor finale.
def simulate_multiple_displacements(num_simulations, num_steps, probability):

    #lista cu pozitiile finale ale simularilor
    final_positions = []

    #iterez numarul de simulari
    for _ in range(num_simulations):
       #apelare functie de la pct a pt a obtine pozitiile
        positions = simulate_displacement(num_steps, probability)

        #adaug ultima pozitie din simulare la lista
        final_positions.append(positions[-1])

    #generare histograma folosind plt.hist
    #specific interval, aliniez si specific culori
    plt.hist(final_positions, bins=range(min(final_positions), max(final_positions) + 2), align='left', edgecolor='black')
   #etichete axe x si y
    plt.xlabel('Final Positions')
    plt.ylabel('Frequency')
    plt.title('Histogram of Final Positions after {} Steps ({} simulations)'.format(num_steps, num_simulations))
    plt.show()

# Exemplu de utilizare:
num_simulations = 1000
simulate_multiple_displacements(num_simulations, num_steps, probability)


#c) Rezolvati cerinta b) de mai sus pentru o deplasare pe un cerc cu n ∈ N noduri
def simulate_circular_displacement(num_simulations, num_steps, num_nodes):
    #lista unde stochez pozitiile finale
    final_positions = []

    #iterez nr simulari multiple pe cerc
    for _ in range(num_simulations):
        #pozitie curenta pe cerc
        current_position = 0

        #simulez deplasarea pe cerc
        for _ in range(num_steps):
            #generez o valoare intre 0 si 1 pt a decide daca ma deplasez la stanga sau la dreapta
            move_right = np.random.rand() < probability

            #actualizez pozitia curenta pe cerc
            current_position = (current_position + 1) % num_nodes if move_right else (current_position - 1) % num_nodes
        #adaug pozitia finala
        final_positions.append(current_position)

    plt.hist(final_positions, bins=range(num_nodes + 1), align='left', edgecolor='black')
    plt.xlabel('Final Positions on the Circle')
    plt.ylabel('Frequency')
    plt.title('Histogram of Final Positions on the Circle after {} Steps ({} simulations)'.format(num_steps, num_simulations))
    plt.show()

# Exemplu de utilizare:
num_nodes = 10
simulate_circular_displacement(num_simulations, num_steps, num_nodes)


#problema 2
import random

class SimulatorLoto:
    def __init__(self, numere_totale=49, numere_selectate=6):
        self.numere_totale = numere_totale
        self.numere_selectate = numere_selectate
        self.bilete_necastigatoare = 0

    def genereaza_bilet(self):
        return random.sample(range(1, self.numere_totale + 1), self.numere_selectate)

    def simulare_pana_la_castig(self):
        bilete_necastigatoare = 0

        while True:
            bilet = self.genereaza_bilet()
            bilete_necastigatoare += 1

            if self.numere_castigatoare(bilet) >= 3:
                break

        self.bilete_necastigatoare = bilete_necastigatoare

    def numere_castigatoare(self, bilet):
        # Simulam numarul de numere castigatoare din bilet (pot fi ajustate pentru cazul real)
        numere_castigatoare = random.sample(bilet, 3)
        return len(set(numere_castigatoare))

# i) Generare lista cu numarul de bilete necastigatoare pana la primul bilet castigator
simulator = SimulatorLoto()
num_simulari = 1000
rezultate = []

for _ in range(num_simulari):
    simulator.simulare_pana_la_castig()
    rezultate.append(simulator.bilete_necastigatoare)

# ii) Estimarea probabilitatii si afisarea valorii teoretice
num_bilete_succesive = 10
probabilitate_experimentala = sum(1 for x in rezultate if x >= num_bilete_succesive) / num_simulari
probabilitate_teorica = (1 - 1 / (num_bilete_succesive + 1)) ** (num_bilete_succesive - 1)

print("Probabilitate experimentala:", probabilitate_experimentala)
print("Probabilitate teoretica:", probabilitate_teorica)
