import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

'''
Se cunosc date despre angajatii unei companii, date salvate in fisierul "data/employees.csv".

1.a. Sa se stabileasca:

numarul de angajati
numar si tipul informatiilor (proprietatilor) detinute pentru un angajat
numarul de angajati pentru care se detin date complete
valorile minime, maxime, medii pentru fiecare proprietate
in cazul proprietatilor nenumerice, cate valori posibile are fiecare astfel de proprietate
daca sunt valori lipsa si cum se poate rezolva aceasta problema

1.b. Sa se vizualizeze:

distributia salariilor acestor angajati pe categorii de salar
distributia salariilor acestor angajati pe categorii de salar si echipa din care fac parte
angajatii care pot fi considerati "outlieri"
'''

'''
numar_angajati(file) - returneaza numarul de angajati
file - fisierul din care se citesc datele
'''


def numar_angajati(file):
    data = pd.read_csv(file)
    return len(data)


'''
nr_info(file) - returneaza numarul si tipul informatiilor (proprietatilor) detinute pentru un angajat
file - fisierul din care se citesc datele
'''


def nr_info(file):
    data = pd.read_csv(file)
    return len(data.columns)


'''
nr_angajati_info(file) - returneaza numarul de angajati pentru care se detin date complete
file - fisierul din care se citesc datele
'''


def nr_angajati_info(file):
    data = pd.read_csv(file)
    return data.dropna().shape[0]
    # k = 0
    # with open(file, "r") as file_reader:
    #     reader = csv.reader(file_reader)
    #     for angajat in reader:
    #         if '' not in angajat:
    #             k += 1
    # return k


'''
is_number(s) - verifica daca un string reprezinta un numar
s - stringul de verificat
'''


def is_number(s):
    try:
        float(s)
        return True
    except ValueError:
        return False


'''
medie(file) - valorile minime, maxime, medii pentru fiecare proprietate
file - fisierul din care se citesc datele
'''


def medie(file):
    data = pd.read_csv(file)

    min_salariu = data['Salary'].min()
    medie_salariu = data['Salary'].mean()
    max_salariu = data['Salary'].max()

    min_bonus = data['Bonus %'].min()
    medie_bonus = data['Bonus %'].mean()
    max_bonus = data['Bonus %'].max()

    print("Minim salariu:", min_salariu)
    print("Medie salariu:", medie_salariu)
    print("Maxim salariu:", max_salariu)
    print("Minim bonus:", min_bonus)
    print("Medie bonus:", medie_bonus)
    print("Maxim bonus:", max_bonus)


'''
valori_posibile(file) - in cazul proprietatilor nenumerice, cate valori posibile are fiecare astfel de proprietate
file - fisierul din care se citesc datele

nunique() - returneaza numarul de valori unice din fiecare coloana
'''


def valori_posibile(file):
    data = pd.read_csv(file)
    nonnumeric_columns = data.select_dtypes(exclude=np.number).columns
    values = data[nonnumeric_columns].nunique()
    for field, count in values.items():
        print(f"Numar valori posibile '{field}': {count}")


'''
val_lipsa(file) - afiseaza valorile lipsa si completeaza cu "NULL" valorile lipsa
file - fisierul din care se citesc datele
'''


def val_lipsa(file):
    data = pd.read_csv(file)
    lipsa = data.isnull().sum()
    print("Valori lipsa\n", lipsa)
    data.fillna("NULL", inplace=True)
    data.to_csv(file, index=False)


def main():
    file = "employees.csv"
    print(numar_angajati(file))
    print(nr_info(file))
    print(nr_angajati_info(file))
    medie(file)
    valori_posibile(file)
    val_lipsa(file)


main()


def teste():
    file = "employees.csv"
    assert numar_angajati(file) == 1000
    assert nr_info(file) == 8
    assert nr_angajati_info(file) == 764


teste()

'''
Sa se vizualizeze:

distributia salariilor acestor angajati pe categorii de salar
distributia salariilor acestor angajati pe categorii de salar si echipa din care fac parte
angajatii care pot fi considerati "outlieri"
'''

'''
distributie_salar(file) - distributia salariilor acestor angajati pe categorii de salar
file - fisierul din care se citesc datele

hist() - metoda care afiseaza histograma
'''


def distributie_salar(file):
    data = pd.read_csv(file)

    plt.hist(data['Salary'], bins=6, edgecolor='black')
    plt.xlabel('Salariu')
    plt.ylabel('Numar angajați')
    plt.grid()
    plt.show()


'''distributie_salar_echipa(file) - distributia salariilor acestor angajati pe categorii de salar si echipa din care 
fac parte file - fisierul din care se citesc datele

groupby() - metoda care grupeaza datele dupa o anumita coloana
dropna() - metoda care elimina valorile lipsa
hist() - metoda care afiseaza histograma
'''


def distributie_salar_echipa(file):
    data = pd.read_csv(file)
    grouped_data = data.dropna(subset=['Salary']).groupby('Team')  # practic organizez salariile pe echipe

    for team, group in grouped_data:
        plt.hist(group['Salary'], bins='auto', edgecolor='black', alpha=0.7, label=f'Echipa {team}')
        plt.xlabel('Salariu')
        plt.ylabel('Numar angajați')
        plt.legend()
        plt.grid()
        plt.show()


'''
distribution_outliers(file) - angajatii care pot fi considerati "outlieri"
file - fisierul din care se citesc datele

outlier - valoare care se abate semnificativ de la media distribuției

mean() - metoda care calculeaza media
std() - metoda care calculeaza deviatia standard
boxplot() - metoda care afiseaza diagrama boxplot
'''


def distributie_outlieri(file):
    data = pd.read_csv(file)
    mean = data['Salary'].mean()  # media
    std_dev = data['Salary'].std()  # deviatia standard
    # print(mean + 3 * std_dev)
    outliers = data[data['Salary'] > mean + 3 * std_dev]

    # print(outliers)

    plt.boxplot(outliers['Salary'], vert=False)
    plt.xlabel('Salariu')
    plt.ylabel('Outlieri')
    plt.grid()
    plt.show()


'''
main2() - functia care apeleaza cele 3 functii de vizualizare
'''


def main2():
    file = "employees.csv"
    distributie_salar(file)
    distributie_salar_echipa(file)
    distributie_outlieri(file)


main2()

'''
normalizarea datelor - procesul de transformare a datelor intr-un format standard, astfel incat sa fie usor de
comparator si de analizat. '''

'''
normalizare(file) - normalizarea datelor - salariul, bonusul, echipa
file - fisierul din care se citesc datele

 '''
# def normalizare(file):
#     data = pd.read_csv(file)
#
#     # normalizare salariu si bonus prin clipping
#     # se determina salariu/bonus per echipa
#
#     for team in data['Team'].unique():
#         team_data = data[data['Team'] == team]
#         salary = team_data['Salary']
#         bonus = team_data['Bonus %']

# return data

# print(normalizare("employees.csv"))
