%a. Sa se scrie un predicat care intoarce intersectia a doua multimi.

%membru(E:integer, L:list)
%(i, i)
membru(E, [E | _]).
membru(E, [_ | T]) :-
    membru(E, T).

%intersectie(A:list, B:list, C:list)
%(i, i, o)
intersectie([], _, []).
intersectie([HA | TA], B, [HA | C]) :-
    membru(HA, B),
    !,
    intersectie(TA, B, C).
intersectie([_ | TA], B, C):-
    intersectie(TA, B, C).



% b. Sa se construiasca lista (m, ..., n), adica multimea numerelor
% intregi din intervalul [m, n].

%lista(M:integer, N:integer, R:lista)
%(i, i, o)
lista(N, N, [N]) :- !.
lista(M, N, [M | R]) :-
    M < N,
    M1 is M + 1,
    lista(M1, N, R).

afiseaza(M, N) :-
    lista(M, N, R),
    write(R), nl.
