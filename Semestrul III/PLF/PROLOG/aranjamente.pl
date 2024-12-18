insereaza(E, L, [E|L]).
insereaza(E, [H|T], [H|Rez]):-
    insereaza(E, T, Rez).

comb([H|_], 1, [H]).
comb([_|T], K, Rez):-
    comb(T,K,Rez).
comb([H|T], K, [H|Rez]):-
    K1 is K-1,
    comb(T,K1,Rez).

perm([],[]).
perm([E|T], P):-
    perm(T, L),
    insereaza(E, L, P).


aranjamente(L,K,Rez):-
    comb(L,K,R1),
    perm(R1, Rez).

main(L,K,Rez):-
    findall(R1, aranjamente(L,K,R1), Rez).
