%a) Sa se adauge dupa fiecare element dintr-o lista divizorii
% elementului.

%divizori(E:integer, D:integer, R:list)
%(i, i, o)
divizori([], _, []).
divizori(E, D, []) :-
    D > E,
    !.
divizori(E, D, [D | R]) :-
    E mod D =:= 0,
    !,
    D1 is D + 1,
    divizori(E, D1, R).
divizori(E, D, R) :-
    D1 is D + 1,
    divizori(E, D1, R).

%adauga(L:list, S:list, R:list)
%(i, i, o)
adauga([], S, S).
adauga([H | T], S, [H | R]) :-
    adauga(T, S, R).

%adauga_divizori(L:list, R:list)
%(i, i, o)
adauga_divizori([], []).
adauga_divizori([H | T], [H | R]) :-
    divizori(H, 1, Div),
    adauga_divizori(T, R1),
    adauga(Div, R1, R).



% b) Se da o lista eterogena, formata din numere intregi si liste de
% numere intregi. Se cere ca in fiecare sublista sa se adauge dupa
% fiecare element divizorii elementului. De ex:
%[1, [2, 5, 7], 4, 5, [1, 4], 3, 2, [6, 2, 1], 4, [7, 2, 8, 1], 2] =>
% [1, [2, 5, 7], 4, 5, [1, 4, 2], 3, 2, [6, 2, 3, 2, 1], 4, [7, 2, 8, 2,
% 4, 1], 2]

%adauga_divizori_lista(L:list, R:list)
%(i, o)
adauga_divizori_lista([], []).
adauga_divizori_lista([H | T], [HS | R]) :-
    is_list(H),
    !,
    adauga_divizori(H, HS),
    adauga_divizori_lista(T, R).
adauga_divizori_lista([H | T], [H | R]) :-
    adauga_divizori_lista(T, R).







