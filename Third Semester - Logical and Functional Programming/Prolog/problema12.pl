%a) Sa se inlocuiasca toate aparitiile unui element dintr-o lista cu un
% alt element.

%inloc(L:list, E:integer, F:integer, R:list)
%(i, i, i, o)
inloc([], _, _, []).
inloc([H | T], E, F, [F | R]) :-
    H =:= E,
    !,
    inloc(T, E, F, R).
inloc([H | T], E, F, [H | R]) :-
    inloc(T, E, F, R).



% b) Se da o lista eterogena, formata din numere intregi si liste de
% numere intregi. Se cere ca toate aparitiile elementului maxim (dintre
% valorile intregi ale listei) sa fie inlocuite in fiecare sublista cu
% maximul sublistei respective. De ex:
%[1, [2, 5, 7], 4, 5, [1, 4], 3, [1, 3, 5, 8, 5, 4], 5, [5, 9, 1], 2] =>
%[1, [2, 7, 7], 4, 5, [1, 4], 3, [1, 3, 8, 8, 8, 4], 5, [9, 9, 1], 2]

%maxim(A:integer, B:integer, M:integer)
%(i, i, o)
maxim(A, B, A) :-
    A >= B,
    !.
maxim(A, B, B) :-
    A < B,
    !.

%maxim_lista(L:list, Max:integer)
%(i, o)
maxim_lista([], -999).
maxim_lista([H | T], Max) :-
    maxim_lista(T, MaxT),
    maxim(H, MaxT, Max).

%extrage_numere(L:list, R:list)
%(i, o)
extrage_numere([], []).
extrage_numere([H | T], [H | R]) :-
    \+ is_list(H),
    !,
    extrage_numere(T, R).
extrage_numere([_ | T], R) :-
    extrage_numere(T, R).

%inlocuire_maxim(L:list, Max:integer, R:list)
%(i, i, o)
inlocuire_maxim([], _, []).
inlocuire_maxim([H | T], Max, [HS | R]) :-
    is_list(H),
    !,
    maxim_lista(H, MaxL),
    inloc(H, Max, MaxL, HS),
    inlocuire_maxim(T, Max, R).
inlocuire_maxim([H | T], Max, [H | R]) :-
    inlocuire_maxim(T, Max, R).

%rezolvare(L:list)
%(i, o)
rezolvare(L) :-
    extrage_numere(L, N),
    maxim(N, Max),
    inlocuire_maxim(L, Max, R),
    write(R), nl.






