%a)Definiti un predicat care determina produsul unui numar reprezentat
%cifra cu cifra intr-o lista cu o anumita cifra. De ex: [1 9 3 5 9 9] * 2
% => [3 8 7 1 9 8]

%produs_cu_transport(L:list, C:integer, TR:integer, R:list)
%(i, i, o)
produs_cu_transport([], _, 0, []) :- !.
produs_cu_transport([], _, T, [T]) :-
    T > 0,
    !.
produs_cu_transport([H | T], C, TR, [HP | TP]) :-
    Prod is H * C + TR,
    HP is Prod mod 10,
    NT is Prod // 10,
    produs_cu_transport(T, C, NT, TP).

%invers(L:list, Col:list, R:list)
%(i, i, o)
invers([], Col, Col).
invers([H | T], Col, R) :-
    invers(T, [H | Col], R).

%produs(L:list, C:integer, R:list)
%(i, o)
produs(L, C, R) :-
    invers(L, [], LI),
    produs_cu_transport(LI, C, 0, Rez),
    invers(Rez, [], R).

% b) Se da o lista eterogena, formata din numere intregi si maximum 9
% liste de numere intregi. Sa se inlocuiasca fiecare sublista cu
% rezultatul inmultirii sublistei cu numarul de ordine al sublistei
% (prima sublista cu 1, a 2-a cu 2, etc.). De ex:
%[1, [2, 3], [4, 1, 4], 3, 6, [7, 5, 1, 3, 9], 5, [1, 1, 1], 7] =>
%[1, [2, 3], [8, 2, 8], 3, 6, [2, 2, 5, 4, 1, 7], 5, [4, 4, 4], 7]

%inmultire_liste(L:list, P:integer, R:list)
%(i, i, o)
inmultire_liste([], _, []).
inmultire_liste([H | T], P, [HS | TS]) :-
    is_list(H),
    !,
    produs(H, P, HS),
    P1 is P + 1,
    inmultire_liste(T, P1, TS).
inmultire_liste([H | T], P, [H | TS]) :-
     inmultire_liste(T, P, TS).


afisare(L, R) :-
    inmultire_liste(L, 1, R),
    write(R), nl.







