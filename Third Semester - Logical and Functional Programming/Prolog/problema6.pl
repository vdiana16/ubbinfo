%a) Intr-o lista L sa se inlocuiasca toate aparitiile unui element E cu
%elementele unei alte liste, L1. De ex: inloc([1,2,1,3,1,4],1,[10,11],X)
%va produce X=[10,11,2,10,11,3,10,11,4].

%adaugalista(L:list, S:list, R:list)
%(i, i, o)
adaugalista([], S, S).
adaugalista([H | T], S, [H | R]) :-
    adaugalista(T, S, R).

%inlocuire_element_lista(L:list, E:integer, S:list, R:list)
%(i, i, i, o)
inlocuire_element_lista([], _, _, []).
inlocuire_element_lista([H | T], E, S, R) :-
    H =:= E,
    !,
    inlocuire_element_lista(T, E, S, Rez),
    adaugalista(S, Rez, R).
inlocuire_element_lista([H | T], E, S, [H | R]) :-
    inlocuire_element_lista(T, E, S, R).



% b) Se da o lista eterogena, formata din numere intregi si liste de
% numere intregi. In fiecare sublista sa se inlocuiasca toate aparitiile
% primului element din sublista cu o lista data. De ex:
%[1, [4, 1, 4], 3, 6, [7, 10, 1, 3, 9], 5, [1, 1, 1], 7] si [11, 11] =>
% [1, [11, 11, 1, 11, 11], 3, 6, [11, 11, 10, 1, 3, 9], 5, [11 11 11 11
% 11 11], 7]

%extreage_prim(L:list, E:integer)
%(i, o)
extrage_prim([H | _], H).

%inlocuieste(L:list, S:list, R:list)
%(i, i, i, o)
inlocuieste([], _, []).
inlocuieste([H | T], S, [HR | R]) :-
    is_list(H),
    !,
    extrage_prim(H, H1),
    inlocuire_element_lista(H, H1, S, HR),
    inlocuieste(T, S, R).
inlocuieste([H | T], S, [H | R]) :-
    inlocuieste(T, S, R).
