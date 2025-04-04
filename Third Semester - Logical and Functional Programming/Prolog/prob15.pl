
adauga([], L, L).

adauga([H|T], L2, [H|TR]) :-
    adauga(T, L2, TR).



secv_pare(Lista, Rezultat):-
    pare(Lista,[],[],0,0,Rezultat).



adauga([], L, L).

adauga([H|T], L2, [H|TR]) :-
    adauga(T, L2, TR).


secv_pare(Lista, Rezultat):-
    pare(Lista,[],[],0,0,Rezultat).

% pare(L:lista, Secv_Curenta:lista, Secv_Max:lista, Lungime:intreg,
% Lungime_Max:intreg, Max:lista)
pare([],[],[],0,_,[]).

pare([], Secv_Curenta, _, Lungime, Lungime_Max, Max):-
    Lungime > Lungime_Max,
    Max = Secv_Curenta.

pare([], _, Secv_Max, Lungime, Lungime_Max, Max):-
    Lungime =< Lungime_Max,
    Max = Secv_Max.

pare([H|T], Secv_Curenta, Secv_Max, Lungime, Lungime_Max, Max):-
    H mod 2 =:= 0,
    Lungime1 is Lungime + 1,
    adauga(Secv_Curenta, [H], Secv_Noua),
    pare(T, Secv_Noua, Secv_Max, Lungime1, Lungime_Max, Max).

pare([H|T], Secv_Curenta, _, Lungime, Lungime_Max, Max) :-
    H mod 2 =:= 1,
    Lungime > Lungime_Max,
    pare(T, [], Secv_Curenta, 0, Lungime, Max).

pare([H|T], _, Secv_Max, Lungime, Lungime_Max, Max) :-
    H mod 2 =:= 1,
    Lungime =< Lungime_Max,
    pare(T, [], Secv_Max, 0, Lungime_Max, Max).

