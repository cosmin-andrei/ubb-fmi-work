#problema 1

# import random
# from math import comb, perm
#
# simulari = 1000
# urna = ['rosu']*5 + ['albastru']*3 + ['verde']*2
# simulari_adev=0
#
# for _ in range(simulari):
#     extragere = random.sample(urna, 3)
#
#     A=False
#     for bila in extragere:
#         if bila == 'rosu':
#             A=True
#
#     B=True
#     for i in range(1,3):
#         if extragere[i] != extragere[0]:
#             B=False
#
#
#     if A==True and B==True:
#         simulari_adev = simulari_adev+1
#
# prob1 = simulari_adev/simulari
# print(prob1, "\n")
#
# #toate sunt rosii
# probabilitate_rosii = comb(5,3)/comb(10,3)
#
# #cel putin una este rosie
# probabilitateA = 1 - comb(5, 0) * comb(5,3) / comb(10,3)
#
# prob2 = probabilitate_rosii/probabilitateA
# print(prob2)


# #prob 2
# from random import randrange
# from matplotlib.pyplot import bar, hist, grid, show, legend
#
# #simulare aruncare zar
# data = [randrange(1,7) for _ in range(500)]
#
# #muchii histograma
# bin_edges = [k+0.5 for k in range(1,7)]
#
# #afisare histograma cu frecvente relative
# hist(data, bins = bin_edges, density = True, rwidth = 0.9, color = 'green', edgecolor = 'black', alpha = 0.5, label = 'frecvente relative')
#
# #calcul prob teoretica
# distribution = dict([(i,1/6) for i in range(1,7)])
#
# #afisare bare coresp prob
# bar(distribution.keys(), distribution.values(), width = 0.85, color = 'red', edgecolor = 'black', alpha= 0.6, label = 'probabilitati')
#
# #adaugare legenda
# legend(loc = 'lower left')
# grid()
# show()


# prob 3

# import numpy as np
# import matplotlib.pyplot as plt
# from scipy.stats import binom
#
# # Definirea parametrilor distribuției binomiale
# n = 5  # Numărul de încercări (extrageri)
# p = 6 / 10  # Probabilitatea de a extrage o bilă cu cifra 1
#
# # a) Generarea listei de 1000 de valori pentru X
# sample_size = 1000
# X_values = np.random.binomial(n, p, sample_size)
#
# # b) Afișarea histogramelor cu frecvențele relative și valorile teoretice
# plt.hist(X_values, bins=np.arange(0, 6), density=True, rwidth=0.9, color='green', edgecolor='black', alpha=0.5, label='frecvente relative')
#
# # Calculul valorilor teoretice pentru distribuția binomială
# x = np.arange(0, 6)
# pmf_values = binom.pmf(x, n, p)
# plt.bar(x, pmf_values, width=0.85, color='red', edgecolor='black', alpha=0.6, label='probabilitati')
#
# # Adăugarea legendei și afișarea grilei
# plt.legend(loc='upper right')
# plt.grid()
#
# # c) Estimarea probabilității P(2 < X ≤ 5) folosind funcția cdf
# P_2_to_5 = binom.cdf(5, n, p) - binom.cdf(2, n, p)
# print("Estimarea probabilității P(2 < X ≤ 5):", P_2_to_5)
#
# # Afișarea graficului
# plt.show()


#problema 4

# import random
# import matplotlib.pyplot as plt
#
# # Numărul de simulări
# num_simulări = 10000
#
# # Lista pentru stocarea probabilităților de câștig pentru fiecare număr
# probabilități_de_câștig = []
#
# # Parcurgem toate numerele posibile pe care le poate indica jucătorul
# for număr_indicat in range(3, 19):
#     câștiguri = 0
#
#     for _ in range(num_simulări):
#         zaruri = [random.randint(1, 6) for _ in range(3)]
#         sumă_zaruri = sum(zaruri)
#
#         if sumă_zaruri == număr_indicat:
#             câștiguri += 1
#
#     probabilitate_câștig = câștiguri / num_simulări
#     probabilități_de_câștig.append(probabilitate_câștig)
#
# # Afișarea histogramelor și probabilităților
# numere_indicate = list(range(3, 19))
# plt.bar(numere_indicate, probabilități_de_câștig, width=0.85, color='green', edgecolor='black', alpha=0.5, label='probabilitati')
# plt.xlabel("Număr indicat de jucător")
# plt.ylabel("Probabilitate de câștig")
# plt.grid()
# plt.show()
#
# # Găsirea numărului cu cea mai mare probabilitate de câștig
# cel_mai_bun_număr = numere_indicate[probabilități_de_câștig.index(max(probabilități_de_câștig))]
# print("Cel mai bun număr indicat pentru a avea cele mai bune șanse de a câștiga:", cel_mai_bun_număr)
#
# from scipy.stats import nbinom
# import numpy as np
#
# # Definirea parametrilor distribuției binomiale negative
# p = 1/6  # Probabilitatea de a obține numărul dorit pe un singur zar
# n = 3  # Numărul de aruncări de zar
#
# # Calculul probabilităților teoretice pentru fiecare număr
# numere_indicate = np.arange(3, 19)
# probabilități_teoretice = [nbinom.pmf(k - 3, n, p) for k in numere_indicate]
#
# # Afișarea histogramelor și probabilităților
# plt.bar(numere_indicate, probabilități_teoretice, width=0.85, color='blue', edgecolor='black', alpha=0.5, label='probabilitati teoretice')
# plt.xlabel("Număr indicat de jucător")
# plt.ylabel("Probabilitate de câștig (teoretic)")
# plt.grid()
# plt.show()
#
# # Găsirea numărului cu cea mai mare probabilitate de câștig
# cel_mai_bun_număr_teoretic = numere_indicate[probabilități_teoretice.index(max(probabilități_teoretice))]
# print("Cel mai bun număr indicat pentru a avea cele mai bune șanse de a câștiga (teoretic):", cel_mai_bun_număr_teoretic)
#
