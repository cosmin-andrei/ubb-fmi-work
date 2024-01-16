candidat(E,[E|_]).
candidat(E,[_|T]):-
    candidat(E,T).

submultimi(_, N, []):- N =<0.
submultimi(L, N, R):-
    candidat(E, L),
    sub_aux(L, [E], E, R).

%sub_aux(L,N,C,Lg,S,R)
sub_aux(_,C,S,C):-
    S mod 2 =:= 1.
sub_aux(L,[H|C],S,R):-
    candidat(E,L),
    not(candidat(E,[H|C])),
    E<H,
    S1 is S+E,
    sub_aux(L,[H,E|C],S1,R).

generate(N,N,[N]).
generate(I,N,[I|T]):-
    I1 is I+1,
    generate(I1,N,T).

lungime([],0).
lungime([_|T],R):-
    lungime(T,R1),
    R is R1+1.

main(A,B,R):-
    generate(A,B,L),
    lungime(L,N),
    submultimi(L,N,R).
