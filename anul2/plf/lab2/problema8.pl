%a) Definiti un predicat care determina succesorul unui numar
% reprezentat cifra cu cifra intr-o lista. De ex: [1 9 3 5 9 9] => [1 9
% 3 6 0 0]

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


%succesor(L:list, R:list)
%(i, o)
succesor(L, R) :-
    inversare(L, [], LI),
    suma_cu_transport(LI, [1], 0, Rez),
    inversare(Rez, [], R).

% b) Se da o lista eterogena, formata din numere intregi si liste de
% cifre. Pentru fiecare sublista sa se determine succesorul numarului
% reprezentat cifra cu cifra de lista respectiva. De ex:
%[1, [2, 3], 4, 5, [6, 7, 9], 10, 11, [1, 2, 0], 6] =>
%[1, [2, 4], 4, 5, [6, 8, 0], 10, 11, [1, 2, 1], 6]

%succesori_liste(L:list, R:list)
%(i, o)
succesori_liste([], []).
succesori_liste([H | T], [HR | TR]) :-
    is_list(H),
    !,
    succesor(H, HR),
    succesori_liste(T, TR).
succesori_liste([H | T], [H | TR]) :-
     succesori_liste(T, TR).
