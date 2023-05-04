#define menu
def menu():
    print("1. Introduceti lista de numere")
    print("2. Rezolvati exercitiul 4")
    print("3. Rezolvati exercitiul 6")
    print("4. Rezolvati exercitiul 10")
    print("5. Terminare")

#input_numbers_list
def input_list():
    input_string = input("Introduceti lista de numere:")
    lista = input_string.split()
    #convert to int
    for i in range(len(lista)):
        lista[i] = int(lista[i])
    return lista

#exercitiul 6
def ex6(l):

    poz1=0
    poz2=0
    maxim=-1
    i=0

    while i<=(len(l)-1):
        j=i+1
        k=0
        while j<=(len(l)-1):
            if l[i]==l[j]:
                if maxim<k:
                    poz1=i
                    poz2=j-1
                    maxim=k
                    k=0
                    break
                break
            else:
                k=k+1
            j=j+1

        if(maxim<k):
            poz1=i
            poz2=j
            maxim=k

        i = i + 1

    if maxim == -1:
        print("Nu exista")
    else:
        print(l[poz1:poz2])

    lista=[]
    for i in range(poz1,poz2):
        lista.append(l[i])
    return lista

#exercitiul 10
def ex10(l):

    poz1 = 0
    poz2 = 0
    maxim = -1
    i = 0

    while i <= (len(l) - 1):
        j = i
        k = 0
        while j <= (len(l) - 3):
            if (l[j+1]-l[j]>0) and (l[j+2]-l[j+1]>0):
                if maxim < k:
                    poz1 = i
                    poz2 = j-3
                    maxim = k
                break
            elif (l[j+1]-l[j]<0) and (l[j+2]-l[j+1]<0):
                if maxim < k:
                    poz1 = i
                    poz2 = j-1
                    maxim = k
                break
            else:
                k = k + 1

            j = j + 1

        if (maxim < k):
            poz1 = i
            poz2 = j
            maxim = k

        i = i + 1

    if poz2==len(l)-2:
        poz2=poz2+2

    if maxim == -1:
        print("Nu exista")
    else:
        print(l[poz1:poz2])

#exercitiul 4
def ex4(l):

    poz1=0
    poz2=0
    maxim=-1
    i=0

    while i<=(len(l)-1):
        j=i
        k=0
        while j<=(len(l)-1):
            if prim(l[j])==False:
                if maxim<k:
                    poz1=i
                    poz2=j-1
                    maxim=k
                    k=0
                    break
                break
            else:
                k=k+1
            j=j+1

        if(maxim<k):
            poz1=i
            poz2=j
            maxim=k

        i = i + 1

    if maxim == -1:
        print("Nu exista")
    else:
        print(l[poz1:poz2])

def prim(nr):
    d=2
    while d <= nr/2:
        if nr%d == 0:
            return False
        d=d+1
    return True

#testare
def testare():
    assert ex6([5,10,3,2,4,5,6,7,8]) == [10,3,2,4,5,6,7,8]
    assert ex6([3,10,3,2,5,6,3,2]) == [10,3,2,5,6,3,2]
    assert ex6([-5,3-2,1,-6,4,-3]) == [-5,3-2,1,-6,4,-3]
    print("Testele au mers blanita")


#principal code segment
def main():
    menu()
    while True:
        ex=input("Comanda ")
        if ex=="1":
            l=input_list()
            print(l)

        elif ex=="2":
            ex4(l)

        elif ex=="3":
            ex6(l)


        elif ex=="4":
            ex10(l)

        elif ex=="5":
            exit()

        else:
            print("Mai baga o fisa")
            menu()

testare()
main()