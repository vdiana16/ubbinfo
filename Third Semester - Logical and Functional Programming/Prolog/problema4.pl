%a)Sa se interclaseze fara pastrarea dublurilor doua liste sortate.

%interclasare(L1:list, L2:list, R:list)
%(i, i, o)
interclasare(L1, [], L1) :- !.
interclasare([], L2, L2) :- !.
interclasare([H1 | T1], [H2 | T2], [H1 | R]) :-
    H1 < H2,
    !,
    interclasare(T1, [H2 | T2], R).
interclasare([H1 | T1], [H2 | T2], [H2 | R]) :-
    H1 > H2,
    !,
    interclasare([H1 | T1], T2, R).
interclasare([H1 | T1], [H2 | T2], [H2 | R]) :-
    H1 =:= H2,
    !,
    interclasare(T1, T2, R).

%b) Se da o lista eterogena, formata din numere intregi si liste de
%numere sortate. Sa se interclaseze fara pastrarea dublurilor toate
%sublistele. De ex:
%[1, [2, 3], 4, 5, [1, 4, 6], 3, [1, 3, 7, 9, 10], 5, [1, 1, 11], 8]
% =>[1, 2, 3, 4, 6, 7, 9, 10, 11].

%elimin_dubluri(L:list, R:list)
%(i, o)
elimin_dubluri([], []) :- !.
elimin_dubluri([H], [H]) :- !.
elimin_dubluri([H1, H2 | T], R) :-
    H1 =:= H2,
    !,
    elimin_dubluri([H2 | T], R).
elimin_dubluri([H1, H2 | T], [H1 | R]) :-
    elimin_dubluri([H2 | T], R).

%interclasare_liste(L:list, R:list)
%(i, o)
interclasare_liste([], []) :- !.
interclasare_liste([H | T], R) :-
    is_list(H),
    !,
    interclasare_liste(T, R1),
    interclasare(H, R1, R).
interclasare_liste([_ | T], R) :-
    interclasare_liste(T, R).


%inter(L:list, R:list)
%(i, o)
inter(L, R) :-
    interclasare_liste(L, R1),
    elimin_dubluri(R1, R).








