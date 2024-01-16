%a
dif([],_,[]).
dif([H|T],B,Rez):-
    member(H,B),
    dif(T,B,Rez).

dif([H|T],B,[H|Rez]):-
    dif(T,B,Rez).

%b
app([],[]).
app([H|T],[H,1|Rez]):-
    H mod 2 =:= 0,
    app(T, Rez).
app([H|T],[H|Rez]):-
    app(T,Rez).


