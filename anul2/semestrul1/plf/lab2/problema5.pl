%a) Sa se determine pozitiile elementului maxim dintr-o lista liniara.
% De ex: poz([10,14,12,13,14], L) va produce L = [2,5].

%maxim(L:list, Max:integer)
%(i, o)
maxim([], -999).
maxim([H | T], Max) :-
    maxim(T, MaxT),
    H > MaxT,
    !,
    Max is H.
maxim([_ | T], Max) :-
    maxim(T, Max).

%poz_elem(L:list, E:integer, Poz:integer, R:list)
%(i, i, o)
poz_elem([], _, _, []).
poz_elem([H | T], E, Poz, [Poz | R]) :-
    H =:= E,
    !,
    Poz1 is Poz + 1,
    poz_elem(T, E, Poz1, R).
poz_elem([_ | T], E, Poz, R) :-
    Poz1 is Poz + 1,
    poz_elem(T, E, Poz1, R).

%rezolvare(L:list, R:list)
%(i, o)
rezolvare(L, R) :-
    maxim(L, Max),
    poz_elem(L, Max, 1, R).


% b) Se da o lista eterogena, formata din numere intregi si liste de
% numere intregi. Sa se inlocuiasca fiecare sublista cu pozitiile
% elementului maxim din sublista respectiva.
% De ex: [1, [2, 3], [4, 1,4], 3, 6, [7, 10, 1, 3, 9], 5, [1, 1, 1], 7]
% => [1, [2], [1, 3], 3, 6,[2], 5, [1, 2, 3], 7]

%inlocuire_pozitii_maxim(L:list, R:list)
%(i, o)
inlocuire_pozitii_maxim([], []).
inlocuire_pozitii_maxim([H | T], [HS | R]) :-
    is_list(H),
    maxim(H, Max),
    poz_elem(H, Max, 1, HS),
    inlocuire_pozitii_maxim(T, R).
inlocuire_pozitii_maxim([H | T], [H | R]) :-
    inlocuire_pozitii_maxim(T, R).












