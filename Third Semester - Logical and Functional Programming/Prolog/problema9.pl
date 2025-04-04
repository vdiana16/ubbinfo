%a) Dandu-se o lista liniara numerica, sa se stearga toate secventele de
% valori consecutive. Ex: sterg([1, 2, 4, 6, 7, 8, 10], L) va produce
% L=[4, 10].

%sterge_consecutiv(L:list, R:list)
%(i, o)
sterge_consecutiv([], []).
sterge_consecutiv([H],[H]) :- !.
sterge_consecutiv([H1, H2],[]) :-
    H1 =:= H2 - 1,
    !.
sterge_consecutiv([H1, H2, H3 | T], R) :-
    H1 =:= H2 - 1,
    H2 =:= H3 - 1,
    !,
    sterge_consecutiv([H2, H3 | T], R).
sterge_consecutiv([H1, H2, H3 | T], R) :-
    H1 =:= H2 - 1,
    H2 =\= H3 - 1,
    !,
    sterge_consecutiv([H3 | T], R).
sterge_consecutiv([H1, H2 | T], [H1 | R]) :-
    sterge_consecutiv([H2 | T], R).


% b) Se da o lista eterogena, formata din numere intregi si liste de
% numere intregi. Din fiecare sublista sa se stearga toate secventele de
% valori consecutive. De ex:
%[1, [2, 3, 5], 9, [1, 2, 4, 3, 4, 5, 7, 9], 11, [5, 8, 2], 7] =>
%[1, [5], 9, [4, 7, 9], 11, [5, 8, 2], 7]

%sterge_cons_liste(L:list, R:list)
%(i, o)
sterge_cons_liste([], []).
sterge_cons_liste([H | T], [HR | TR]) :-
    is_list(H),
    !,
    sterge_consecutiv(H, HR),
    sterge_cons_liste(T, TR).
sterge_cons_liste([H | T], [H | TR]) :-
     sterge_cons_liste(T, TR).











