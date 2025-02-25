%a. Sa se scrie un predicat care substituie intr-o lista un element prin
% altul.

%substituie(L:list, E:integer, A:integer, R:list)
%(i, i, i, o)
substituie([], _, _, []).
substituie([H | T], E, A, [A | T]) :-
    H =:= E,
    !.
substituie([_ | T], E, A, R) :-
    substituie(T, E, A, R).



%b. Sa se construiasca sublista (lm, ..., ln) a listei (l1, ..., lk).

%sublista(L:list, M:integer, N:integer, P:integer, R:list)
%(i, i, i, i, o)
sublista([], _, _, _, []) :- !.
sublista(_, _, N, P, []) :-
    P > N,
    !.
sublista([H | T], M, N, P, [H | R]) :-
    P >= M,
    P =< N,
    P1 is P + 1,
    sublista(T, M, N, P1, R),
    !.
sublista([_ | T], M, N, P, R) :-
    P < M,
    P1 is P + 1,
    sublista(T, M, N, P1, R).
