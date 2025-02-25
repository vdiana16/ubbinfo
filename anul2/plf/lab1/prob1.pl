% a. Sa se scrie un predicat care intoarce diferenta a doua multimi.

%apare(E:integer, L:list)
%(i, i)
%E - elementul cautat
%L - lista in care caut elementul
apare(E, [E | _]).
apare(E, [_ | T]) :-
    apare(E, T).

%diferenta_multimi(L:list, P:list, R:list)
%(i, i, o) - determinist
%L - prima multime
%P - a doua multime
%R - rezultatul dintre L - P
diferenta_multimi([], _, []).
diferenta_multimi([H | T], P, R) :-
    apare(H, P),
    !,
    diferenta_multimi(T, P, R).
diferenta_multimi([H | T], P, [H | R]) :-
    diferenta_multimi(T, P, R).



% b. Sa se scrie un predicat care adauga intr-o lista dupa fiecare
% element par valoarea 1.

adauga_dupa_par([], []).
adauga_dupa_par([H | T], [H, 1 | R]) :-
    H mod 2 =:= 0,
    !,
    adauga_dupa_par(T, R).
adauga_dupa_par([H | T], [H | R]) :-
    adauga_dupa_par(T, R).















