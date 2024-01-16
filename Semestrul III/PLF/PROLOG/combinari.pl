comb([H|_], 1, [H]).
comb([_|T], K, Rez):-
    comb(T, K, Rez).
comb([H|T], K, [H|Rez]):-
    K>1,
    K1 is K-1,
    comb(T, K1, Rez).


