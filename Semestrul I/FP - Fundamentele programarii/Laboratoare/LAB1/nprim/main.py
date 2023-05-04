n=int(input("Introduceti nr:"))
i=2 #int
ok=1 #int
if n<2:
    print("Numarul nu este prim")
else:
    while i<=n/2:
        if n%i==0:
            print("Numarul nu este prim")
            ok=0
            break
        i=i+1
    if ok==1:
        print("Numarul este prim")
