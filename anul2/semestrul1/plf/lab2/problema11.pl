%a) Se da o lista de numere intregi. Se cere sa se scrie de 2 ori in
% lista fiecare numar prim.

%prim(N:integer, D:integer, F:integer)
%(i, i, o)
prim(2, _, 1) :- !.
prim(N, D, 0) :-
    D < N,
    N mod D =:= 0,
    !.
prim(N, D, F) :-
    D * D =< N,
    N mod D =\= 0,
    !,
    D1 is D + 1,
    prim(N, D1, F).
prim(N, D, 1) :-
    D * D > N,
    !.

%este_prim(N:integre)
%(i)
este_prim(N) :-
    N > 1,
    prim(N, 2, F),
    F =:= 1.

%dublare_prim(L:list, R:list)
%(i, o)
dublare_prim([], []).
dublare_prim([H | T], [H, H | R]) :-
    este_prim(H),
    !,
    dublare_prim(T, R).
dublare_prim([H | T], [H | R]) :-
    dublare_prim(T, R).


% b) Se da o lista eterogena, formata din numere intregi si liste de
% numere intregi. Se cere ca in fiecare sublista sa se scrie de 2 ori
% fiecare numar prim. De ex:
%[1, [2, 3], 4, 5, [1, 4, 6], 3, [1, 3, 7, 9, 10], 5] =>
%[1, [2, 2, 3, 3], 4, 5, [1, 4, 6], 3, [1, 3, 3, 7, 7, 9, 10], 5]


%dublare_prim_liste(L:list, R:list)
%(i, o)
dublare_prim_liste([], []) :- !.
dublare_prim_liste([H | T], [HS | R]) :-
    is_list(H),
    !,
    dublare_prim(H, HS),
    dublare_prim_liste(T, R).
dublare_prim_liste([H | T], [H | R]) :-
    dublare_prim_liste(T, R).








