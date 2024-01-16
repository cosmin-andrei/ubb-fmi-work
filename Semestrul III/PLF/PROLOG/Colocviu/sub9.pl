candidat(E, [E|_]).
candidat(E, [_|T]):-
    candidat(E,T).

lungime([], 0).
lungime([_|T], R):-
    lungime(T, R1),
    R is R1+1.

ultElem([E]):- E mod 2 =:= 1.
ultElem([_|T]):-
    ultElem(T).

aranj(L, N, S, R):-
    candidat(E, L),
    S1 is S-E,
    aranj_aux(L,N,1,[E],S1,R).

%aranj_aux(L,N,K,C,S,R)

aranj_aux(_,N,N,C,0,C):-
    ultElem(C).
aranj_aux(L,N,K,C,S,R):-
    candidat(E, L),
    not(candidat(E, C)),
    S1 is S-E,
    K1 is K+1,
    aranj_aux(L,N,K1,[E|C],S1,R).

main(L, N, S, R):-
    findall(R1, aranj(L, N, S, R1), R).
