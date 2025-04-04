%a) Se da o lista de numere intregi. Se cere sa se adauge in lista dupa
% 1-ul element, al 3-lea element, al 7-lea elemen, al 15-lea element … o
% valoare data e.

%P=2*P+1
%adauga_dupa_val(L:list, E:integer, I:integer, P:integer, R:list)
%(i, i, i, i, o)
adauga_dupa_val([], _, _, _, []).
adauga_dupa_val([H | T], E, I, P, [H, E | TR]) :-
    I =:= P,
    !,
    P1 is P*2 + 1,
    I1 is I + 1,
    adauga_dupa_val(T, E, I1, P1, TR).
adauga_dupa_val([H | T], E, I, P, [H | TR]) :-
    I1 is I + 1,
    adauga_dupa_val(T, E, I1, P, TR).


% b) Se da o lista eterogena, formata din numere intregi si liste de
% numere intregi. Lista incepe cu un numar si nu sunt 2 elemente
% consecutive care sunt liste. Se cere ca in fiecare sublista sa se
% adauge dupa 1-ul, al 3-lea, al 7-lea… element valoarea care se gaseste
% inainte de sublista in lista eterogena. De ex:
%[1, [2, 3], 7, [4, 1, 4], 3, 6, [7, 5, 1, 3, 9, 8, 2, 7], 5] =>
%[1, [2, 1, 3], 7, [4, 7, 1, 4, 7], 3, 6, [7, 6, 5, 1, 6, 3, 9, 8, 2, 6,
%7], 5].

%adauga_dupa_val_liste(L:list, R:list)
%(i, o)
adauga_dupa_val_liste([], []).
adauga_dupa_val_liste([H], [H]) :- !.
adauga_dupa_val_liste([H1, H2 | T], [H1, HS | TR]) :-
    not(is_list(H1)),
    is_list(H2),
    !,
    adauga_dupa_val(H2, H1, 1, 1, HS),
    adauga_dupa_val_liste(T, TR).
adauga_dupa_val_liste([H | T], [H | TR]) :-
    adauga_dupa_val_liste(T, TR).
