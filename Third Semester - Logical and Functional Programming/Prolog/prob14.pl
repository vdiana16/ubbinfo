%a. Sa se scrie un predicat care testeaza egalitatea a doua multimi,
% fara sa se faca apel la diferenta a doua multimi.

membru(E, [E | _]).
membru(E, [_ | T]) :-
    membru(E, T).

%elimina(L:list, E:integer, R:list)
%(i, i, o)
elimina([E | T], E, T).
elimina([H | T], E, [H | R]) :-
    elimina(T, E, R).


%egalitate_multimi(A:list, B:list)
%(i, i)
egalitate_multimi([], []).
egalitate_multimi([HA | TA], B) :-
    membru(HA, B),
    elimina(B, HA, B_fara_A),
    egalitate_multimi(TA, B_fara_A),
    !.

%multimi_egale(A:list, B:list)
%(i, i)
multimi_egale(A, B) :-
    egalitate_multimi(A, B),
    egalitate_multimi(B, A).


%b. Definiti un predicat care selecteaza al n-lea element al unei liste.

%selecteaza_n(L:list, N:integer, E:integer)
%(i, i, o)
selecteaza_n([], _, []).
selecteaza_n([H | _], 1, H) :- !.
selecteaza_n([_ | T], N, R) :-
    N1 is N - 1,
    selecteaza_n(T, N1, R).




