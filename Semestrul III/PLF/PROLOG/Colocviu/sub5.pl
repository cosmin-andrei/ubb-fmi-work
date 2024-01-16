candidat(E,[E|_]).
candidat(E,[_|T]):-
    candidat(E,T).

isPar(E, 1, 0):-
    E mod 2 =:= 0.
isPar(E, 0, 1):-
    E mod 2 =:= 1.

submult(L,N,R):-
    candidat(E,L),
    isPar(E,Ep,Eimp),
    sub_aux(L,Ep,Eimp,N,1,[E],R).

sub_aux(_,Ep,Eimp,N,N,C,C):-
    Ep mod 2 =:= 0,
    Eimp mod 2 =:= 1.
sub_aux(L,Ep,Eimp,N,Lg,[H|C],R):-
    candidat(E,L),
    not(candidat(E,C)),
    isPar(E, Ep1, Eimp1),
    E<H,
    Ep2 is Ep1 + Ep,
    Eimp2 is Eimp1+Eimp,
    Lg1 is Lg+1,
    sub_aux(L,Ep2,Eimp2,N, Lg1,[E,H|C],R).

generate(N,N,[N]).
generate(I,N,[I|T]):-
    I1 is I+1,
    generate(I1, N, T).

main(A, B, R):-
    N is B-A+1,
    generate(A,B,L),
    submult(L,N,R).
