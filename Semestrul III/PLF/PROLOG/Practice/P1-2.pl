%8a

nuApare(_, []).
nuApare(X, [H|T]):-
    X \== H,
    nuApare(X, T).

esteMultime([]).
esteMultime([H|T]):-
    nuApare(H, T),
    esteMultime(T).

%8b
% Sa se scrie un predicat care elimina primele 3 aparitii ale unui
% element intr-o lista. Daca elementul apare mai putin de 3 ori, se va
% elimina de cate ori apare.


%7a

append([],L2,L2).
append([H|T],L2,[H|L3]):-
    append(T,L2,L3).

reuniune([],L2,Rez):-
    append(Rez,L2).
reuniune([H|T],L2,[H|Rez]):-
    nuApare(H,L2),
    reuniune(T,L2,Rez).
reuniune([H|T],L2,Rez):-
    not(nuApare(H,L2)),
    intersectie(T,L2,Rez).


%9a Sa se scrie un predicat care intoarce intersectia a doua multimi

intersectie([],_,[]).
intersectie([H|T],L2,[H|Rez]):-
    not(nuApare(H,L2)),
    intersectie(T,L2,Rez).
intersectie([H|T],L2,Rez):-
    nuApare(H,L2),
    intersectie(T,L2,Rez).

%10a Sa se intercaleze un element pe pozitia a n-a a unei liste.
intercalare([],0,_,_,[]).
intercalare([_|T],I,E,N,[E|Rez]):-
    N =:= I,
    intercalare(T,I1,E,N,Rez),
    I is I1+1.
intercalare([H|T],I,E,N,[H|Rez]):-
    intercalare(T,I1,E,N,Rez),
    I is I1+1.


