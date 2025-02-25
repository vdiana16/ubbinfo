%a) Sa se sorteze o lista cu eliminarea dublurilor. De ex: [4 2 6 2 3 4]
%=> [2 3 4 6]

%merge_sort(L:list, R:list)
%(i, o)
merge_sort([], []) :- !.
merge_sort([H], [H]) :- !.
merge_sort(L, R) :-
    split(L, Left, Right),
    merge_sort(Left, SLeft),
    merge_sort(Right, SRight),
    merge(SLeft, SRight, R).

%split(L:list, Left:list, Right:list)
%(i, o, o)
split([], [], []) :- !.
split([H], [H], []) :- !.
split([H1, H2 | T], [H1 | T1], [H2 | T2]) :-
    split(T, T1, T2).

%merge(Left:list, Right:list, Rez:list)
%(i, i, o)
merge(Rez, [], Rez) :- !.
merge([], Rez, Rez) :- !.
merge([H1 | T1], [H2 | T2], [H1 | Rez]) :-
    H1 < H2,
    !,
    merge(T1, [H2 | T2], Rez).
merge([H1 | T1], [H2 | T2], [H2 | Rez]) :-
    H1 > H2,
    !,
    merge([H1 | T1], T2, Rez).
merge([H1 | T1], [H2 | T2], [H2 | Rez]) :-
    H1 =:= H2,
    !,
    merge(T1, T2, Rez).


% b) Se da o lista eterogena, formata din numere intregi si liste de
% numere. Sa se sorteze fiecare sublista fara pastrarea dublurilor. De ex:
%[1, 2, [4, 1, 4], 3, 6, [7, 10, 1, 3, 9], 5, [1, 1, 1], 7] =>
%[1, 2, [1, 4], 3, 6, [1, 3, 7, 9, 10], 5, [1], 7].

%sortare_subliste(L:list, R:list)
%(i, o)
sortare_subliste([], []).
sortare_subliste([H | T], R) :-
    is_list(H),
    !,
    sortare_subliste(T, R1),
    merge_sort(H, S),
    R = [S | R1].
sortare_subliste([H | T], [H | R]) :-
    sortare_subliste(T, R).

afisare(L) :-
    sortare_subliste(L, R),
    write(R), nl.





