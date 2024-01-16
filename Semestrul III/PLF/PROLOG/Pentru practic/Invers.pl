my_append([],L,L).
my_append([H|T],L,[H|Rez]):-
    my_append(T,L,Rez).

invers([],[]).
invers([H|T],Rez):-
    my_append(R1,[H],Rez),
    invers(T,R1).
