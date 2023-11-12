/* a) Intr-o lista L sa se inlocuiasca toate aparitiile unui element E cu elementele unei alte liste, L1. De ex: inloc([1,2,1,3,1,4],1,[10,11],X) va produce X=[10,11,2,10,11,3,10,11,4].

b) Se da o lista eterogena, formata din numere intregi si liste de
numere intregi. In fiecare sublista sa se inlocuiasca toate aparitiile
primului element din sublista cu o lista data. De ex: [1, [4, 1, 4], 3,
6, [7, 10, 1, 3, 9], 5, [1, 1, 1], 7] si [11, 11] => [1, [11, 11, 1, 11,
11], 3, 6, [11, 11, 10, 1, 3, 9], 5, [11 11 11 11 11 11], 7]

*/

%a)
%append(L1,L2,Rez)
%L1 - Lista pe care o inseram (input)
%L2 - Lista in care inseram (input)
%Rez - Rezultat (output)

append([],L,L).
append([H|T],L,[H|Rez]):-
    append(T,L,Rez).

% inlocuire(L,E,L1,Rez)
% L-lista in care inlocuim (input)
% E - elem pe care il inlocuim (input)
% L1 - Lista cu care inlocuim
% Rez - rezultatul (output)

inlocuire([],_,_,[]).
inlocuire([H|T],E,L1,[H|R]):-
    H\=E,
    inlocuire(T,E,L1,R).
inlocuire([H|T],E,L1,R):-
    H=E,
    inlocuire(T,E,L1,R1),
    append(L1,R1,R).

%b)

%primulEl(L,Rez)
%L - lista din care extragem primul element (input)
%Rez - reztultatul: primul element (output)

primulEl([H|_],H).

%inlocuireB(L1,L2,Rez)
%L1 - Lista in care inlocuim (input)
%L2 - Lista cu care inlocuim (input)
%Rez - rezultatul: lista modificata (output)

inlocuireB([],_,[]).

inlocuireB([H|T],L2,[H|R]):-
    \+ is_list(H),
    inlocuireB(T,L2,R).

inlocuireB([H|T],L2,[R1|R]):-
    is_list(H),
    primulEl(H,E),
    inlocuire(H,E,L2,R1),
    inlocuireB(T,L2,R).


