%a) Definiti un predicat care determina suma a doua numere scrise in
% reprezentare de lista.


%suma_cu_transport(L1:list, L2:list, Transport:integer, Sum:list)
%(i, i, i, o)
suma_cu_transport([], [], 0, []) :-
    !.
suma_cu_transport([], [], T, [T]) :-
    T > 0,
    !.
suma_cu_transport([H1 | T1], [], T, [HS | TS]) :-
    Sum is H1 + T,
    HS is Sum mod 10,
    NT is Sum // 10,
    !,
    suma_cu_transport(T1, [], NT, TS).
suma_cu_transport([], [H2 | T2], T, [HS | TS]) :-
    Sum is H2 + T,
    HS is Sum mod 10,
    NT is Sum // 10,
    !,
    suma_cu_transport([], T2, NT, TS).
suma_cu_transport([H1 | T1], [H2 | T2], T, [HS | TS]) :-
    Sum is H1 + H2 + T,
    HS is Sum mod 10,
    NT is Sum // 10,
    !,
    suma_cu_transport(T1, T2, NT, TS).

%inversare(L:list, Col:list, R:list)
%(i, o)
inversare([], Col, Col).
inversare([H | T], Col, R) :-
    inversare(T, [H | Col], R).

%inversare(L:list, R:list)
%(i, o)
inversare_p(L, R) :-
    inversare(L, [], R).

%suma_liste(L1:list, L2:list, Sum:list)
%(i, i, o)
suma_liste(L1, L2, Sum) :-
    inversare_p(L1, R1),
    inversare_p(L2, R2),
    suma_cu_transport(R1, R2, 0, RSum),
    inversare_p(RSum, Sum).

% b) Se da o lista eterogena, formata din numere intregi si liste de
% cifre. Sa se calculeze suma tuturor numerelor reprezentate de
% subliste. De ex: [1, [2, 3], 4, 5, [6, 7, 9], 10, 11, [1, 2, 0], 6]=>
%[8, 2, 2].

%suma_liste_eterogene(L:list, S:list)
%(i, o)
suma_liste_eterogene([], []).
suma_liste_eterogene([H | T], S) :-
    is_list(H),
    !,
    suma_liste_eterogene(T, S1),
    suma_liste(H, S1, S).
suma_liste_eterogene([_ | T], S) :-
    suma_liste_eterogene(T, S).


