%a. Sa se scrie un predicat care determina cel mai mic multiplu comun al
% elementelor unei liste formate din numere intregi.

%cmmdc(A:integer, B:integer, D:integer)
%(i, i, o)
cmmdc(A, 0, A):- !.
cmmdc(A, B, D) :-
    B > 0,
    R is A mod B,
    cmmdc(B, R, D).

%cmmmc(A:integer, B:integer, M:integer)
%(i, i, o)
cmmmc(A, B, M) :-
    cmmdc(A, B, D),
    M is abs(A*B) // D.

%cmmmc_lista(L:list, Cmmmc:integer)
%(i, o)
cmmmc_lista([], 0) :- !.
cmmmc_lista([H], H) :- !.
cmmmc_lista([H | T], Cmmmc) :-
    cmmmc_lista(T, CmmmcAux),
    cmmmc(H, CmmmcAux, Cmmmc).

%b. Sa se scrie un predicat care adauga dupa 1-ul, al 2-lea, al 4-lea,
% al 8-lea ...element al unei liste o valoare v data.

%adauga_putere2(L:list, V:integer, I:integer, Poz:integer, R:list)
%(i, i)
adauga_putere2([], _, _, _, []).
adauga_putere2([H | T], V, I, Poz, [H, V | R]) :-
    I =:= Poz,
    !,
    NextI is I + 1,
    NextPoz is Poz * 2,
    adauga_putere2(T, V, NextI, NextPoz, R).
adauga_putere2([H | T], V, I, Poz, [H | R]) :-
    NextPoz is Poz + 1,
    adauga_putere2(T, V, I, NextPoz, R).

%adauga_putere2_lista(L:list, V:integer, R:list)
%(i, i, o)
adauga_putere2_lista(L, V, R) :-
    adauga_putere2(L, V, 1, 1, R).

afiseaza(L) :-
    write(L), nl.
