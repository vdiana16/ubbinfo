%a. Sa se scrie un predicat care elimina dintr-o lista toate elementele
% care se repeta (ex: l=[1,2,1,4,1,3,4] => l=[2,3])

%contor_elem(L:list, E:integer, C:integer)
%(i, o)
contor_elem([], _, 0).
contor_elem([H | T], E, C) :-
    H = E,
    !,
    contor_elem(T, E, C1),
    C is C1 + 1.
contor_elem([_ | T], E, C) :-
    contor_elem(T, E, C).

%elimina(L:list, E:integer, R:list)
%(i, i, o)
elimina([], _, []).
elimina([H | T], E, [H | R]) :-
    H \= E,
    !,
    elimina(T, E, R).
elimina([_ | T], E, R) :-
    elimina(T, E, R).

%elimina_duplicate(L:list, R:list)
%(i, o)
elimina_duplicate([], []).
elimina_duplicate([H | T], R) :-
    contor_elem([H | T], H, C),
    C > 1,
    !,
    elimina([H | T], H, T1),
    elimina_duplicate(T1, R).
elimina_duplicate([H | T], [H | R]) :-
    elimina_duplicate(T, R).

% b. Sa se elimine toate aparitiile elementului maxim dintr-o lista de
% numere intregi.

%cauta_maxim(L:list, Max:integer)
%(i, o)
cauta_maxim([], -999).
cauta_maxim([H | T], Max) :-
    cauta_maxim(T, MaxT),
    H >= MaxT,
    !,
    Max is H.
cauta_maxim([_ | T], Max) :-
    cauta_maxim(T, Max).

%elimina_maxim(L:list, R:list)
%(i, o)
elimina_maxim([], []).
elimina_maxim([H | T], R) :-
    cauta_maxim([H | T], Max),
    elimina([H | T], Max, R).






