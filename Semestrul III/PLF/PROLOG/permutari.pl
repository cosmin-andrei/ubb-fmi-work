insereaza(E,L,[E|L]).
insereaza(E,[H|T],[H|Rez]):-
    insereaza(E,T,Rez).

perm([],[]).
perm([E|T], P):-
    perm(T, L),
    insereaza(E,L,P).
