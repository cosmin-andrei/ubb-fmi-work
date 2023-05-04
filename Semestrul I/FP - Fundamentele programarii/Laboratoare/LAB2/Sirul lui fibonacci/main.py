n = int(input('Introdu n'))
a=1
b=1
m=a+b
k=3
while m<=n:
    a=b
    b=m
    m=a+b
    k=k+1
print('Cel mai mic numar',m)