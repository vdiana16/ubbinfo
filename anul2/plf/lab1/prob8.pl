%a. Sa se scrie un predicat care testeaza daca o lista este multime.

%membru(E:integer, L:list)
%(i, i)
membru(E, [E | _]).
membru(E, [_ | T]) :-
    membru(E, T).

%verific_multime(L:list)
%(i)
verific_multime([]).
verific_multime([H | T]) :-
    \+ membru(H, T),
    verific_multime(T).


% b. Sa se scrie un predicat care elimina primele 3 aparitii ale unui
% elemnt intr-o lista. Daca elementul apare mai putin de 3 ori, se va
% elimina de cate ori apare.

%elimina_k(L:list, E:integer, K:integer, R:list)
%(i, i, o)
elimina_k([], _, _, []).
elimina_k(L, _, 0, L) :- !.
elimina_k([H | T], E, K, R) :-
    H =:= E,
    K1 is K - 1,
    elimina_k(T, E, K1, R),
    !.
elimina_k([H | T], E, K, [H | R]) :-
    elimina_k(T, E, K, R).

elimina_3(L, E, R) :-
    elimina_k(L, E, 3, R).
