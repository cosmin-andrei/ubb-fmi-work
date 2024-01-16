combSuma([H|_],1,H,[H]).
combSuma([_|T],K,S,Rez):-
    combSuma(T,K,S,Rez).
combSuma([H|T],K,S,[H|Rez]):-
    K>1,
    S1 is S-H,
    S1 > 0,
    K1 is K-1,
    combSuma(T,K1,S,Rez).

toateComb(L, K, S, LC):-
    findall(C, combSuma(L, K, S, C), LC).

candidat(E, [E|_]).
candidat(E, [_|T]):-
    candidat(E,T).

combSuma1(L,K,S,C):-
    candidat(E,L),
    E =< S,
    combaux(L,K,S,C,1,E,[E]).

combaux(_,K,S,C,K,S,C):-!.
combaux(L,K,S,C,Lg,Sum,[H|T]):-
    Lg<K,
    candidat(E,L),
    E<H,
    Sum1 is Sum+E,
    Sum1 =< S,
    Lg1 is Lg+1,
    combaux(L,K,S,C,Lg1,Sum1,[E|[H|T]]).

