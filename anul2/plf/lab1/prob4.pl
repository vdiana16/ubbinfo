%a. Sa se scrie un predicat care substituie intr-o lista un element
% printr-o  alta lista.

%inserare(Sub:list, L:list, R:list)
%(i, i, o)
inserare([], L, L).
inserare([H | T], L, [H | R]) :-
    inserare(T, L, R).

%substituie(L:list, E:integer, L:integer, R:list)
%(i, i, i, o), (i, i, i, i)
substituie([], _, _, []) :- !.
substituie(L, _, [], L) :- !.
substituie([H | T], E, L, R) :-
    H =:= E,
    !,
    inserare(L, T, R).
substituie([H | T], E, L, [H | R]) :-
    substituie(T, E, L, R).


%b. Sa se elimine elementul de pe pozitia a n-a a unei liste liniare.

%elimina_element(L:list, N:integer, I:integer, R:list)
%(i, i, o)
elimina_element([], _, _, []).
elimina_element([_ | T], N, I, T) :-
    I =:= N,
    !,
    I1 is I + 1,
    elimina_element(T, N, I1, T).
elimina_element([H | T], N, I, [H | R]) :-
    I1 is I + 1,
    elimina_element(T, N, I1, R).

%elimina_element_principal(L:list, N:integer, R:list)
%(i, i, o)
elimina_element_principal(L, N, R) :- elimina_element(L, N, 1, R).

