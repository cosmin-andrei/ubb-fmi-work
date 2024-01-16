candidat(E,[E|_]).
candidat(E,[_|T]):-
    candidat(E,T).

submultimi([],[]).
submultimi(L, R):-
    candidat(E, L),
    sub_aux(L, [E], E, R).

sub_aux(_, C, S, C):-
    S mod 2 =:= 0.
sub_aux(L, [H|C], S, R):-
    candidat(E, L),
    not(candidat(E,[H|C])),
    E<H,
    S1 is S+E,
    sub_aux(L, [E,H|C], S1, R).


