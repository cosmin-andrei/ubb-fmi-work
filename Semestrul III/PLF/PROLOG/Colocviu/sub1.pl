:- set_prolog_flag(stack_limit, 4_294_967_296).

insereaza(E, L, [E|L]).
insereaza(E,[H|T],[H|R]):-
    insereaza(E, T, R).

%genereaza_lista(I,N)

genereaza_lista(N,N,[N]).
genereaza_lista(I,N,[I|Rez]):-
    I1 is I+1,
    genereaza_lista(I1,N,Rez).

%candidat(L)
candidat(E,[E|_]).
candidat(E,[_|Rez]):-
    candidat(E,Rez).
mainly(K,S,R):-
    S1 is S-1,
    genereaza_lista(1,S1,L),
    aranjamente(L,K,R).


%aranjamente(L,K) = perm(comb(L,K))

aranjamente(L,K,R):-
    comb(L,K,R1),
    perm(R1,R).

%comb(L,K,S,C)

comb(_, 0, []).
comb(L,K,S,C):-
    candidat(E,L),
    E=<S,
    combaux(L,K,S,[E],1,E,C).

%combaux(L,K,S,C,Lg,Sc,C)
combaux(_,K,S,C,K,S,C).
combaux(L,K,S,C,Lg,Sc,C,[H|T]):-
    Lg<K,
    candidat(E,L),
    E<H,
    S1 is Sc+E,
    S1 =< S,
    Lg1 is Lg+1,
    combaux(L,K,S,C,Lg1,S1,C,[E|[H|T]]).

%perm(L,Rez)

perm([],[]).
perm([E|T],R):-
    perm(T,L),
    insereaza(E,L,R).
