candidat(E,[E|_]).
candidat(E,[_|T]):-
    candidat(E,T).

aranjamente(L, S, K, R):-
    candidat(E,L),
    S1 is S-E,
    aranj_aux(L,S1,K,[E],1,R).

aranj_aux(_,0,K,C,K,C).
aranj_aux(L,S,K,C,Lg,R):-
    candidat(E,L),
    not(candidat(E,C)),
    S1 is S-E,
    Lg1 is Lg + 1,
    aranj_aux(L,S1,K,[E|C],Lg1,R).

generate(N,N,[N]).
generate(I,N,[I|T]):-
    I1 is I+1,
    generate(I1,N,T).

main(L,K,S,R):-
   % S1 is S-1,
    %generate(1,S1,L),
    aranjamente(L,S,K,R).
