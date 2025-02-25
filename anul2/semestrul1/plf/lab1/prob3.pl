% a. Sa se scrie un predicat care transforma o lista intr-o multime, in
% ordinea primei aparitii. Exemplu: [1,2,3,1,2] e transformat in
% [1,2,3].

%membru(E:integer, L:list)
%(i, i)
membru(E, [E | _]).
membru(E, [_ | T]) :-
    membru(E, T).

%lista_multime(L:list, Col:list, R:list)
%(i, o)
%Col - variabila colectoare ce tine lista de elemente deja adaugate
lista_multime([], _, []).
lista_multime([H | T], Col, [H | R]) :-
    \+ membru(H, Col),
    !,
    lista_multime(T, [H | Col], R).
lista_multime([_ | T], Col, R) :-
    lista_multime(T, Col, R).

%lista_multime_p(L:list, R:list)
%(i, o)
lista_multime_p(L, R) :-
    lista_multime(L, [], R).


% b. Sa se scrie o functie care descompune o lista de numere intr-o lista
% de forma [ lista-de-numere-pare lista-de-numere-impare] (deci lista cu
% doua elemente care sunt liste de intregi), si va intoarce si numarul
% elementelor pare si impare.

% lista_pareimpare(L:list, Cp:integer, Ci:integer, R:list)
% (i, i, i, i, o)
lista_pareimpare([], 0, 0, [[], []]).
lista_pareimpare([H | T], Cp, Ci, [[H | Lp], Li]) :-
    H mod 2 =:= 0,
    lista_pareimpare(T, Cp1, Ci, [Lp, Li]),
    Cp is Cp1 + 1.
lista_pareimpare([H | T], Cp, Ci, [Lp, [H | Li]]) :-
    H mod 2 =\= 0,
    lista_pareimpare(T, Cp, Ci1, [Lp, Li]),
    Ci is Ci1 + 1.








