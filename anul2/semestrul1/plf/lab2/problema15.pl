%a) Sa se determine cea mai lunga secventa de numere pare consecutive
% dintr-o lista (daca sunt mai multe secvente de lungime maxima, una
% dintre ele).

%adauga(L:list, S:list, R:list)
%(i, i, o)
adauga([], L, L).
adauga([H | T], S, [H | R]) :-
    adauga(T, S, R).

%secv_max_para(L:list, R:list)
%(i, o)
secv_max_para(L, R) :-
    secv_para(L, 0, 0, [], [], R).

% secv_para(L:list, Lg:integer, LgMax:integer, SCrt:list, SMax:list,
% Max:list)
%(i, i, i, i, i, o)
secv_para([], 0, _, [], [], []).
secv_para([], Lg, LgMax, SCrt, _, Max) :-
    Lg > LgMax,
    Max = SCrt.
secv_para([], Lg, LgMax, _, SMax, Max) :-
    Lg =< LgMax,
    Max = SMax.
secv_para([H | T], Lg, LgMax, SCrt, SMax, Max) :-
    H mod 2 =:= 0,
    Lg1 is Lg + 1,
    adauga(SCrt, [H], SNoua),
    secv_para(T, Lg1, LgMax, SNoua, SMax, Max).
secv_para([H | T], Lg, LgMax, SCrt, _, Max) :-
    H mod 2 =:= 1,
    Lg > LgMax,
    secv_para(T, 0, Lg, [], SCrt, Max).
secv_para([H | T], Lg, LgMax, _, SMax, Max) :-
    H mod 2 =:= 1,
    Lg =< LgMax,
    secv_para(T, 0, LgMax, [], SMax, Max).


% b) Se da o lista eterogena, formata din numere intregi si liste de
% numere intregi. Sa se inlocuiasca fiecare sublista cu cea mai lunga
% secventa de numere pare consecutive din sublista respectiva. De ex:
% [1, [2, 1, 4, 6, 7], 5, [1, 2, 3, 4], 2, [1, 4, 6, 8, 3], 2, [1, 5], 3]
% =>[1, [4, 6], 5, [2], 2, [4, 6, 8], 2, [], 3]

inloc_secv([],[]).
inloc_secv([H|T], [Rezultat | Rez]) :-
    is_list(H),
    secv_max_para(H, Rezultat),
    inloc_secv(T, Rez).

inloc_secv([H|T], [H|Rez]) :-
    not(is_list(H)),
    inloc_secv(T, Rez).












