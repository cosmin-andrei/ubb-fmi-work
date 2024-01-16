candidat(E, [E|_]).
candidat(E, [_|T]):-
    candidat(E,T).

lungime([],0).
lungime([_|T], R):-
    lungime(T,R1),
    R is R1+1.

permutari(L, N, R):-
    candidat(E,L),
   % lungime(L,N),
    perm_aux(L,[E],N,1,R).

perm_aux(_,C,N,N,C).
perm_aux(L, [H|C], N, Lg, R):-
    candidat(E, L),
    not(candidat(E,[H|C])),
    Diff is E-H,
    M is abs(Diff),
    M >= 2,
    Lg1 is Lg+1,
    perm_aux(L,[E,H|C],N,Lg1,R).

generare(N, N, [N]).
generare(I, N, [I|T]):-
    I1 is I+1,
    generare(I1, N, T).

main(N, R):-
    generare(1, N, L),
    permutari(L, N, R).
