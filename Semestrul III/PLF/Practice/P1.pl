%2

% Sa se scrie un predicat care adauga dupa 1-ul, al 2-lea, al 4-lea, al
% 8-lea ... element al unei liste o valoare v data.

verif_putere(I):-
    I =:= 1.
verif_putere(I):-
    I mod 2 =:=0,
    I1 is I//2,
    verif_putere(I1).

adaugaV([],_,_,[]).
adaugaV([H|T],V,I,[H, V|Rez]):-
    I1 is I+1,
    verif_putere(I1),
    adaugaV(T, V, I1, Rez).
adaugaV([H|T],V,I,[H|Rez]):-
    I1 is I+1,
    adaugaV(T, V, I1, Rez).


%3
% Sa se scrie un predicat care transforma o lista intr-o multime, in
% ordinea primei aparitii. Exemplu: [1,2,3,1,2] e transformat in [1,2,3].

multime([],[]).
multime([H|T],Rez):-
    member(H,T),
    multime(T,Rez).
multime([H|T],[H|Rez]):-
    not(member(H,T)),
    multime(T,Rez).

% Sa se scrie o functie care descompune o lista de numere intr- lista de
% forma [ lista-de-numere-pare lista-de-numere-impare] (deci lista cu
% doua elemente care sunt liste de intregi), si va intoarce si numarul
% elementelor pare si impare.

descompunere([],0,0,[[],[]]).
descompunere([H|T],P,I,[[H|Pare],Impare]):-
    H mod 2 =:= 0,
    descompunere(T,P1,I,[Pare, Impare]),
    P is P1+1.
descompunere([H|T],P,I,[Pare,[H|Impare]]):-
    H mod 2 =:= 1,
    descompunere(T, P, I1, [Pare,Impare]),
    I is I1+1.

%5
% Sa se scrie un predicat care sterge toate aparitiile unui anumit atom
% dintr-o lista.

sterge_atom([],_,[]).
sterge_atom([H|T],E,Rez):-
    H =:= E,
    sterge_atom(T,E,Rez).
sterge_atom([H|T],E,[H|Rez]):-
    sterge_atom(T,E,Rez).

% Definiti un predicat care, dintr-o lista de atomi, produce o lista de
% perechi (atom n), unde atom apare in lista initiala de n ori. De ex:
% numar([1, 2, 1, 2, 1, 3, 1], X) va produce X = [[1, 4], [2, 2], [3,
% 1]].

nr_aparitii([],_,0).
nr_aparitii([H|T],E,Rez):-
    H =:= E,
    nr_aparitii(T,E,R1),
    Rez is R1+1.
nr_aparitii([_|T],E,Rez):-
    nr_aparitii(T,E,Rez).

frecventa([],[]).
frecventa([H|T],[[H,R1]|Rez]):-
    nr_aparitii([H|T],H,R1),
    sterge_atom([H|T],H,R2),
    frecventa(R2,Rez).

%6
% Sa se scrie un predicat care elimina dintr-o lista toate elementele
% care se repeta (ex: l=[1,2,1,4,1,3,4] => l=[2,3])

elim_dubluri([],[]).
elim_dubluri([H|T],[H|Rez]):-
    sterge_atom(T,H,R1),
    elim_dubluri(R1,Rez).

% Sa se elimine toate aparitiile elementului maxim dintr-o lista de
% numere intreg

maxim([X],X).
maxim([H|T],Maxim):-
    maxim(T, MaximT),
    Maxim is max(H, MaximT).

elim_max([],[]).
elim_max(L,Rez):-
    maxim(L,R1),
    sterge_atom(L,R1,Rez).

%7
%Sa se scrie un predicat care intoarce reuniunea a doua multimi

append_unicat([],X,X).
append_unicat([H|T],L2,X):-
    nr_aparitii(L2,H,Rez),
    Rez = 0,
    append_unicat(T,L2,X).
append_unicat([H|T],L2,[H|X]):-
    append_unicat(T,L2,X).

% Sa se scrie un predicat care, primind o lista, intoarce multimea
% tuturor perechilor din lista. De ex, cu [a, b, c, d] va produce [[a,
% b], [a, c], [a, d], [b, c], [b, d], [c, d]].



formare_perechi(_,[],[]).
formare_perechi(H,[H1|T],[[H,H1]|Rez]):-
    formare_perechi(H, T, Rez).

multime_perechi([],[]).
multime_perechi([H|T],[R1|Rez]):-
    formare_perechi(H,T,R1),!,
    multime_perechi(T,Rez).

%8
%Sa se scrie un predicat care testeaza daca o lista este multime.

nuApare([],_).
nuApare([H|T],X):-
    X\==H,
    nuApare(T,X).

esteMultime([]).
esteMultime([H|T]):-
    nuApare(H,T),
    esteMultime(T).

%7a
%Sa se scrie un predicat care intoarce reuniunea a doua multimi.

reuniune([],[]).
reuniune([H|L1],[H|T]):-
    nr_aparitii(L1, H, Rez),
    Rez<1,
    reuniune(L1,T).
reuniune(L1,[H|T]):-
    nr_aparitii(L1,H,Rez),
    Rez>1,
    reuniune(L1,T).


