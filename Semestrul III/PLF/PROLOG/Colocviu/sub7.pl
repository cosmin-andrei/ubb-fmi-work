candidat(E,[E|_]).
candidat(E,[_|T]):-
    candidat(E,T).

submultimi(L, R):-
    candidat(E,L),
    lungime(L,N),
    sub_aux(L,N,[E],1,R).

sub_aux(_,N,C,Lg,C):-
    Lg>=2,
    Lg=<N.
sub_aux(L,N,[H|C],Lg,R):-
    candidat(E, L),
    not(candidat(E,[H|C])),
    E<H,
    Lg<N,
    Lg1 is Lg+1,
    sub_aux(L,N,[E,H|C],Lg1,R).

lungime([], 0).
lungime([_|T],N):-
    lungime(T,N1),
    N is N1 + 1.

main(L, R):-
    findall(R1, submultimi(L,R1),R).
