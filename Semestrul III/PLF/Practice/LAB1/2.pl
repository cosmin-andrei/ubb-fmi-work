divizor(X,Y,Rez):-
    X =:= Y,
    Rez is X.

divizor(X,Y,Rez):-
    X>Y,
    Z is X-Y,
    divizor(Z,Y,Rez).

divizor(X,Y,Rez):-
    Z is Y-X,
    divizor(X,Z,Rez).

multipl(X,Y,Rez):-
    divizor(X,Y,R1),
    Rez is (X*Y)/R1.

funct_a([],_).
funct_a([H1,H2|T],Rez):-
    multipl(H1,H2,R1),
    Rez is R1,
    multiplu([R1|T],Rez).
