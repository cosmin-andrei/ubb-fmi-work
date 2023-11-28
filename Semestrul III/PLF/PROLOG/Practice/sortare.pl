%insertion(L, E, Rez)
insertion(E,[],[E]).
%insertion(E,[H|T],[H|Rez]):-
 %   E>H,
  %  insertion(T,E,Rez).
insertion(E,[H|T],[E,H|T]):-
    E=<H.
insertion(E,[H|T],[H|Rez]):-
    E>H,
    insertion(E,T,Rez).


%sortare(L,Rez)
sortare([],[]).
sortare([H|T], Sorted):-
    sortare(T, SortedT),
    insertion(H, SortedT, Sorted).
