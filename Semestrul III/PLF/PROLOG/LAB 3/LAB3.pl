%elimina un element dintr-o lista
%sterge(X: integer, L: list, Rez: list)
%sterge(o,i,o)
%X: elementul care trebuie eliminat
%L: lista cu elemente
%Rez: lista rezultata dupa eliminarea primei aparitii
sterge(H, [H|T], T).
sterge(X, [H|T], [H|Rez]) :-
    sterge(X, T, Rez).

%permutarea unei liste
%permutare(L: list,Rez: list)
%permutare(i,o)
%L: lista pentru care fac permutare
%Rez: permutarea propriu zisa
permutare([], []).
permutare(L, [H|Rez]) :-
    sterge(H, L, Rez1),
    permutare(Rez1, Rez).

%verific conditia cu >=M
% diferenta(L: list, M: integer)
% diferenta(i,i)
% L: lista elementelor pentru care verific conditia
% M: cu care compar propriu zis
diferenta([], _).
diferenta([_], _).
diferenta([H1,H2|T], M) :-
    D is abs(H2-H1),
    D >= M,
    diferenta([H2|T], M).

% genereaza lista de elemente de la 1 la n
% generare_l(S: integer, N: integer, Rez: list)
% generare_l(i,i,o)
% S: de unde pornesc cu generarea elem (capat interval)
% N: pana unde generez elem (capat interval)
% Rez: lista generata
generare_l(N, N, [N]).
generare_l(S, N, [S|Rez]) :-
    S<N,
    S1 is S+1,
    generare_l(S1, N, Rez).

%generare(N:integer, M:integer, Perm:list)
%generare(i, i, o)
%N: pana unde generez elementele listei
%M: cu care compar diferenta a doua elem consecutive
%Perm: lista care respecta conditia
generare(N, M, Perm) :-
    generare_l(1, N, LN),
    permutare(LN, Perm),
    diferenta(Perm, M).










