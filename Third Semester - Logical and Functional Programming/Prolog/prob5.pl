%a. Sa se scrie un predicat care sterge toate aparitiile unui anumit
% atom dintr-o lista.

%sterge_atom(L:list, A:atom, R:list)
%(i, i, o)
sterge_atom([], _, []) :- !.
sterge_atom([H | T], A, R) :-
    H = A,
    sterge_atom(T, A, R).
sterge_atom([H | T], A, [H | R]) :-
    H \= A,
    sterge_atom(T, A, R).



% B. Definiti un predicat care, dintr-o lista de atomi, produce o lista
% de perechi (atom n), unde atom apare in lista initiala de n ori. De ex:
% numar([1, 2, 1, 2, 1, 3, 1], X) va produce X = [[1, 4], [2, 2], [3,1]].

%contor_atom(L:list, A:atom, C:integer)
%(i, i, o)
contor_atom([], _, 0) :- !.
contor_atom([H | T], A, C) :-
    H = A,
    contor_atom(T, A, C1),
    C is C1 + 1.
contor_atom([H | T], A, C) :-
    H \= A,
    contor_atom(T, A, C).

%numar_atomi(L:list, X:list)
%(i, o)
numar_atomi([], []) :- !.
numar_atomi([H | T], [[H, C] | X]) :-
    contor_atom([H | T], H, C),
    sterge_atom(T, H, R),
    !,
    numar_atomi(R, X).




