%predicatul de inlocuire
%sub(L,El,L2,Rez)

%L - lista initiala (input)
%El - elementul de substituit (input)
%L2 - lista cu care se substituie (input)
%Rez - Lista rezultat (output)

%L2 - lista a doua
%H1 - Head (primul element)
%L1 - Lista 2
append_n([],L2,L2). %caz 0

%se adauga primul element al primei liste la a doua lista
%[H1|L1] - cel putin un element
append_n([H1|T],L,[H1|REZ]) :- append_n(T,L,REZ).

%daca lista este goala, returnez lista
sub([], _, _, []).

% daca primul elem din lista este El, contatenez la continuarea
% rezolvarii
sub([H|T],El,L,R2) :-
    H = El,
    sub(T,El,L,R),
    append_n(L,R,R2).

%daca primul elem != El, iau primul elem si il adaug la rez
sub([H|T], El, L, [H|R]) :-
    H \= El,
    sub(T,El,L,R).











































