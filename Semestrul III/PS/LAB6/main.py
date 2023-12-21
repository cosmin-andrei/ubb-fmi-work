import mean
from scipy.stats import norm, expon, uniform
from numpy import mean, std, linspace, multiply, exp
from matplotlib.pyplot import show, hist, grid, legend, xticks, plot
from scipy.integrate import quad

simulari = [1000,2000,5000]

def pb1():
    data = norm.rvs(loc=165,scale=10,size=1000)

    #i)
    hist(data, bins=16, range=(130, 211), density=True, alpha=0.5, color='blue', label='Histograma')
    x = linspace(130, 210, 1000)
    plot(x, norm.pdf(x, loc=165, scale=10), 'r-', lw=2, label='Densitatea normala')
    legend()
    show()

    #ii)

    #simulat
    mean_simulat = data.mean()
    std_simulat = data.std()
    proportie = mean((data >= 160) & (data <= 170))

    mean_exact = 165
    std_exact = 10
    proportie_exact = norm.cdf(170, loc=165, scale=10) - norm.cdf(160, loc=165, scale=10)

    print("Valoare simulata", proportie)
    print("Valoarea exacta", proportie_exact)

pb1()

#problema 2

def pb2(N):
    T1 = expon.rvs(loc=0, scale=5, size=N)
    T2 = uniform.rvs(loc=4, scale=2, size=N)

    meanTotal = mean(multiply(T1, 0.4) + multiply(T2, 0.6))
    stdTotal = std(multiply(T1, 0.4) + multiply(T2, 0.6))

    print("Valoare medie a timpului: ", meanTotal)
    print("Deviatie standard: ", stdTotal)

    #b
    prob_estimata= 0.4*mean(T1<5)+0.6*mean(T2<5)
    print("Probabilitate estimata: ", prob_estimata)

    #c
    prob=0.4*expon.cdf(5,loc=0,scale=5) + 0.6*0.5
    print("Probabilitate teoretica: ", prob)

pb2(10000)


a=-1
b=3
#Problema 3

def g(x):
    return exp(-x**2)

def pb3(n):
    n_valori = uniform.rvs(loc=a, scale=b-a, size=n)
    funct=g(n_valori)
    est = (b-a)*mean(funct)
    integral, _ = quad(g, a, b)
    print("Estimare Monte Carlo: ", integral)

pb3(10000)