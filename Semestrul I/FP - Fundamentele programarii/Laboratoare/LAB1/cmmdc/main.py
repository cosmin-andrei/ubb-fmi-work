a=int(input("a="))
b=int(input("b="))

while a!=b:
    if a>b:
        a=a-b
    else:
        b=b-a

print(a)
