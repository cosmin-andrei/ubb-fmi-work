candidat(E, [E|_]).
candidat(E,[_|T]):-
    candidat(E,T).

combaux(_,K,K,P,P,C,C):-!.
combaux(L,I,K,Pc,P,C,[H|T]):-
    I<K,
    candidat(El,L),
    El<H,
    P1 is Pc*El,
    P1=<P,
    I1 is I+1,
    combaux(L,I1,K,P1,P,C,[El|[H|T]]).

comb(L,K,P,C):-
    candidat(E, L),
    E=<P,
    combaux(L,1,K,E,P,[E],C).

main(L,K,P,Rez):-
    findall(C, comb(L, K, P, C), Rez).
