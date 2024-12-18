/* pt o val n data sa se genereze lista permutarilor cu elemtenele n, n+1, ..., 2*n-1, avand prop ca val absoluta a diferentei dintre doua valori consec este <=2*/

insereaza(E,L,[E|L]).
insereaza(E,[H|T],[H|R]):-
    insereaza(E,T,R).

%generare_lista(N,L)

generare_lista(_, 0, []).
generare_lista(I, N, [I]):-
    N1 is 2*N-1,
    I=N1.
generare_lista(I, N, [I | R]) :-
    N1 is 2*N-1,
    I < N1,
    I1 is I+1,
    generare_lista(I1, N, R).

%perm(L, Rez).

perm([], []).
perm([E|T], R):-
    perm(T, L),
    insereaza(E, L, R).


