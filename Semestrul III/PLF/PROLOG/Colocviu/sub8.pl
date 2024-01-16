candidat(E, [E|_]).
candidat(E, [_|T]):-
    candidat(E, T).

comb(L, K, R):-
    candidat(E, L),
    comb_aux(L, K, [E], E, 1, R).


%comb_aux(L, K, C, S, Lg, R).
comb_aux(_, K, C, S, K, C):-
    S mod 2 =:= 0.
comb_aux(L, K, [H|C], S, Lg, R):-
    candidat(E, L),
    not(candidat(E, [H|C])),
    S1 is S+E,
    E<H,
    Lg1 is Lg+1,
    comb_aux(L,K,[E,H|C],S1,Lg1,R).

main(L, K, R):-
    findall(R1, comb(L, K, R1), R).
