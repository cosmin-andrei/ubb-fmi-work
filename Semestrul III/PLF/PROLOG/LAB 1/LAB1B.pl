%sterge(L,N,Rez)
%L - lista initiala (input)
%N - pozitia de pe care sterg elementul (input)
%Rez - Lista rezultat (output)

%daca lista e goala, returnez lista goala
sterge([], _, []).

%daca n=1, returnez lista
%T - tail
sterge([_|T], N, T):-
    N=1.

%H - head
%daca n!=1, adaug primul element la rezolvare
sterge([H|T], N, [H|R]):-
    N \= 1,
    N1 is N-1,
    sterge(T, N1, R).
