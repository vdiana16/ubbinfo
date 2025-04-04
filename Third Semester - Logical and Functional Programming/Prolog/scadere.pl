% scadere_cu_imprumut(L1:list, L2:list, Imprumut:integer, Dif:list)
% (i, i, i, o)

scadere_cu_imprumut([], [], 0, []) :- !.
scadere_cu_imprumut([], [], 1, [-1]) :- !. % Caz special pentru împrumut final
scadere_cu_imprumut([H1 | T1], [], Imprumut, [H2 | TS]) :-
    % Calculăm diferența cu împrumut
    Dif is H1 - Imprumut,
    % Verificăm dacă este necesar împrumut
    (Dif < 0 ->
        H2 is Dif + 10,
        NImprumut is 1
    ;
        H2 is Dif,
        NImprumut is 0
    ),
    scadere_cu_imprumut(T1, [], NImprumut, TS).

scadere_cu_imprumut([], [H2 | T2], Imprumut, [H3 | TS]) :-
    % Calculăm diferența cu împrumut din lista L2
    Dif is -H2 - Imprumut,
    % Verificăm dacă este necesar împrumut
    (Dif < 0 ->
        H3 is Dif + 10,
        NImprumut is 1
    ;
        H3 is Dif,
        NImprumut is 0
    ),
    scadere_cu_imprumut([], T2, NImprumut, TS).

scadere_cu_imprumut([H1 | T1], [H2 | T2], Imprumut, [H3 | TS]) :-
    % Calculăm diferența cu împrumut pentru ambele liste
    Dif is H1 - H2 - Imprumut,
    % Verificăm dacă este necesar împrumut
    (Dif < 0 ->
        H3 is Dif + 10,
        NImprumut is 1
    ;
        H3 is Dif,
        NImprumut is 0
    ),
    scadere_cu_imprumut(T1, T2, NImprumut, TS).
