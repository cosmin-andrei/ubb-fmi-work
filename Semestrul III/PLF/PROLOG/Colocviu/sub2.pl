%candidat

candidat(E,[E|_]).
candidat(E,[_|T]):-
    candidat(E,T).

perm(L,N,R):-
    candidat(E,L),
    perm_aux(L,[E],1,N,R).

%perm_aux(L,C,Lg,N,R)
perm_aux(_,C,N,N,C):-!.
perm_aux(L,[H|C],Lg,N,R):-
    candidat(E,L),
    Diff is E-H,
    M is abs(Diff),
    M =< 2,
    not(candidat(E,[H|C])),
    Lg1 is Lg+1,
    perm_aux(L,[E,H|C],Lg1,N,R).

%lungime(L,Rez)
lungime([],0).
lungime([_|T],Rez):-
    lungime(T,R1),
    Rez is R1+1.

%genereaza_lista(I,N,Rez)
generate(N,N,[N]).
generate(I,N,[I|T]):-
    I1 is I+1,
    generate(I1,N,T).

main(N,Rez):-
    N1 is 2*N-1,
    generate(N, N1, L),
    lungime(L, Lg),
    perm(L,Lg,Rez).
