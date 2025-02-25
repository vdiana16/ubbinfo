%a. Sa se scrie un predicat care intoarce reuniunea a doua multimi.

%membru(E:integer, L:list)
%(i, i)
membru(E, [E | _]).
membru(E, [_ | T]) :-
    membru(E, T).


%reuniune(A:list, B:list, R:list)
%(i, i, o)
reuniune([], [], []) :- !.
reuniune(A, [], A) :- !.
reuniune(A, [HB | TB], R) :-
    \+ membru(HB, A),
    !,
    reuniune(A, TB, R1),
    R = [HB | R1].
reuniune(A, [_ | TB], R) :-
    reuniune(A, TB, R).


%b. Sa se scrie un predicat care, primind o lista, intoarce multimea
% tuturor perechilor din lista. De ex, cu [a, b, c, d] va produce
% [[a, b], [a, c], [a, d], [b, c], [b, d], [c, d]].

%perechi(L:list, E:integer, R:list)
%(i, i, o)
perechi([], _, []).
perechi([H | T], E, [[E, H] | R]) :-
    perechi(T, E, R).

%adauga(S:list, L:list R:list)
%(i, o)
adauga([], L, L).
adauga([H | T], L, [H | R]) :-
    adauga(T, L, R).

%multime_perechi(L:list, R:list)
%(i, o)
multime_perechi([], []).
multime_perechi([H | T], R) :-
    perechi(T, H, P),
    multime_perechi(T, R1),
    adauga(P, R1, R).


afiseaza(L) :-
    multime_perechi(L, R),
    write(R), nl.
