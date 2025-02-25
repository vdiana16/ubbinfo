% a. Sa se scrie un predicat care sa testeze daca o lista formata din
% numere intregi are aspect de "vale"(o multime se spune ca are aspect
% de "vale" daca elementele descresc pana la un moment dat, apoi cresc.
% De ex. 10 8 6 9 11 13).

%vale(L:list, F:integer)
%(i, i)
vale([_], 0).
vale([H1, H2 | T], F) :-
    H1 > H2,
    F =\= 0,
    vale([H2 | T], 1),
    !.
vale([H1, H2 | T], F) :-
    H1 < H2,
    F =\= -1,
    vale([H2 | T], 0),
    !.

%vale_p(L:list)
%(i)
vale_p(L) :-
    vale(L, -1).


%b. Sa se calculeze suma alternanta a elementelor unei liste
%(l1 - l2 + l3 ...).

%suma_alternanta(L:list, S:integer)
%(i, o)
suma_alternanta([], 0).
suma_alternanta([H], H) :- !.
suma_alternanta([H1, H2 | T], S) :-
    suma_alternanta(T, S1),
    S is S1 + H1 - H2.

