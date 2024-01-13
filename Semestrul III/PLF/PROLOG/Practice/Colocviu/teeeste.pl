/*p(I, Y, V):-
    V>2, !, K is I-2, Y is K+V-1.
p(_, Y, V):-
    Y is V+1.


f(100, 0):-!.
f(I,Y):-
    J is I+1,
    f(J, V),
    p(I,Y,V).*/

f(100, 0):-!.
f(I, Y):- J is I+1, f(J,V), V>2, !, K is I-2, Y is K+V-1.
f(I, Y):- J is I+1, f(J,V), Y is V+1.



