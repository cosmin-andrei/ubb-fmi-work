insereaza(E, L, [E|L]).
insereaza(E, [H|T], [H|Rez]):-
    insereaza(E, T, Rez).

elimin(E,L,[E|L]).
elimin(E,[A|L],[A|X]):-
    elimin(E,L,X).
