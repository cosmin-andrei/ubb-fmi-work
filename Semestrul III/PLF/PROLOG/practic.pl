%adaugam elementele din a doua lista la prima lista
%my_append(L1: list, L2:list, Rez: list)
%my_append(i,i,o)
%L1: lista la care adaugam elementele listei L2
%L2: lista din care vom adauga elementele la lista L1
my_append([],L,L).
my_append([H|T],L,[H|Rez]):-
    my_append(T,L,Rez).

%creez perechi cu E1 si fiecare element din lista L
%creare_multime(E: integer, L:list, Rez:list).
%creare_multime(i,i,o)
%E: elementul cu care vom crea perechi
%L: lista de elemente care vor forma perechi cu E
%Rez: rezultatul - perechile de numere
creare_multime(_,[],[]).
creare_multime(E, [H|T], [R1|Rez]):-
    my_append([E],[H],R1),
    creare_multime(E,T,Rez).

%Creez multimea tuturor perechilor din lista
%multimi(L:list ,Rez:list).
%multimi(i,o).
%L: lista pentru care voi forma perechile de numere
%Rez: rezultatul: multimea tuturor perechilor din lista
multimi([],[]).
multimi([H|T], R2):-
    creare_multime(H,T,R1),
    my_append(R1,Rez,R2),
    multimi(T, Rez).

