%a.Sa se scrie un predicat care transforma o lista intr-o multime, in
% ordinea ultimei aparitii. Exemplu: [1,2,3,1,2] e transformat in
% [3,1,2].

%membru(E:integer, L:list)
%(i, i)
membru(E, [E | _]).
membru(E, [_ | T]) :-
    membru(E,T).

%lista_multime(L:list, R:list)
%(i, o)
lista_multime([], []).
lista_multime([H], [H]) :- !.
lista_multime([H | T], R) :-
    lista_multime(T, R1),
    \+ membru(H, R1),
    R = [H | R1],
    !.
lista_multime([_ | T], R) :-
    lista_multime(T, R).


% b. Sa se calculeze cel mai mare divizor comun al elementelor unei
% liste.

%cmmdc(A:integer, B:integer, D:integer)
%(i, i, o)
cmmdc(A, 0, A) :-
    A =\= 0,
    !.
cmmdc(A, B, D) :-
    R is A mod B,
    cmmdc(B, R, D).

%cmmdc_lista(L:list, D:integer)
%(i, o)
cmmdc_lista([], 0).
cmmdc_lista([H | T], D) :-
    cmmdc_lista(T, D1),
    cmmdc(H, D1, D).



