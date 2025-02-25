%a. Sa se intercaleze un element pe pozitia a n-a a unei liste.

%intercaleaza(L:list, N:integer, E:integer, P:integer, R:list)
%(i, i, i, i, o)
intercaleaza([], _, _, _, []).
intercaleaza([H | T], N, E, P, [E , H | T]) :-
    P =:= N,
    !.
intercaleaza([H | T], N, E, P, [H | R]) :-
    P1 is P + 1,
    intercaleaza(T, N, E, P1, R).

%intercaleaza_p(L:list, N:integer, E:integer, R:list)
%(i, i, i, o)
intercaleaza_p(L, N, E, R) :-
    intercaleaza(L, N, E, 1, R).

%b. Definiti un predicat care intoarce cel mai mare divizor comun al
% numerelor dintr-o lista.

%cmmdc(A:integer, B:integer, D:integer)
%(i, o, i)
cmmdc(A, 0, A) :-
    A =\= 0,
    !.
cmmdc(0, B, B) :-
    B =\= 0,
    !.
cmmdc(A, B, D) :-
    A >= B,
    !,
    R is B mod A,
    cmmdc(B, R, D).
cmmdc(A, B, D) :-
    cmmdc(B, A, D).

%cmmdc_lista(L:list, R:integer)
%(i, o)
cmmdc_lista([], 0).
cmmdc_lista([H], H) :-!.
cmmdc_lista([H | T], R) :-
    cmmdc_lista(T, R1),
    cmmdc(H, R1, R).

