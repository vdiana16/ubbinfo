%a) Definiti un predicat care determina predecesorul unui numar
% reprezentat cifra cu cifra intr-o lista. De ex: [1 9 3 6 0 0] => [1 9
% 3 5 9 9]

%scadere_cu_imprumut(L:list, I:integer, D:list)
%(i, i, o)
scadere_cu_imprumut([], 0, []) :- !.
scadere_cu_imprumut([0], 1, [9]) :- !.
scadere_cu_imprumut([H1], 1, [HD]) :-
    HD is H1 - 1,
    HD >= 0,
    !.
scadere_cu_imprumut([0 | T1], 1, [9 | TD]) :-
    scadere_cu_imprumut(T1, 1, TD).
scadere_cu_imprumut([H1 | T1], 1, [HS | TS]) :-
    HS is H1 - 1,
    HS >= 0,
    scadere_cu_imprumut(T1, 0, TS).
scadere_cu_imprumut([H1 | T1], 0, [H1 | T1]) :- !.

% inversare(L:list, Col:list, R:list)
% (i, i, o)

inversare([], Col, Col).
inversare([H | T], Col, R) :-
    inversare(T, [H | Col], R).

% predecesor(L:list, R:list)
% (i, o)

predecesor([0], [0]) :- !.  % Predecesorul pentru 0 ramâne 0
predecesor(L, R) :-
    inversare(L, [], LI),
    scadere_cu_imprumut(LI, 1, Rez),
    inversare(Rez, [], R).

%format(L:list, R:list)
%(i, o)
format_n([0 | L], L) :- !.
format_n(L, L).

pred(L, R1) :-
    predecesor(L, R),
    format_n(R, R1).

%b) Se da o lista eterogena, formata din numere intregi si liste de
% cifre. Pentru fiecare sublista sa se determine predecesorul numarului
% reprezentat cifra cu cifra de lista respectiva. De ex:
%[1, [2, 3], 4, 5, [6, 7, 9], 10, 11, [1, 2, 0], 6] =>
%[1, [2, 2], 4, 5, [6, 7, 8], 10, 11, [1, 1, 9] 6]


%predecesor_lista(L:list, R:list)
%(i, o)
predecesor_lista([],[]).
predecesor_lista([H | T], [HR | TR]) :-
    is_list(H),
    !,
    predecesor(H, HR),
    predecesor_lista(T, TR).
predecesor_lista([H | T], [H | TR]) :-
    predecesor_lista(T, TR).







