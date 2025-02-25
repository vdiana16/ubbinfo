%a. Sa se scrie un predicat care se va satisface daca o lista are numar
% par de elemente si va esua in caz contrar, fara sa se numere
% elementele listei.

%paitate_lista(L:list)
%(i)
paritate_lista([]).
paritate_lista([_, _ | T]) :-
    paritate_lista(T).



%b. Sa se elimine prima aparitie a elementului minim dintr-o lista de
% numere intregi.

%minim(L:list, Min:integer)
%(i, o)
minim([], 999).
minim([H | T], Min) :-
    minim(T, MinT),
    H < MinT,
    !,
    Min is H.
minim([_ | T], Min) :-
    minim(T, Min).


%elimin_k_aparitii(L:list, K:integer, E:integer, R:list)
%(i, i, o)
elimin_k_aparitii([], 0, _, []).
elimin_k_aparitii([H | T], K, E, R) :-
    H =:= E,
    K > 0,
    K1 is K - 1,
    !,
    elimin_k_aparitii(T, K1, E, R).
elimin_k_aparitii([H | T], K, E, [H | R]) :-
    elimin_k_aparitii(T, K, E, R).

%elimin_1_minim(L:list, R:list)
%(i, o)
elimin_1_minim(L, R) :-
    minim(L, Min),
    elimin_k_aparitii(L, 1, Min, R).







