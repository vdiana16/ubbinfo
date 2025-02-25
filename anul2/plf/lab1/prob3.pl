%    3.
%    a. Sa se scrie un predicat care transforma o lista intr-o multime, in 
%    ordinea primei aparitii. Exemplu: [1,2,3,1,2] e transformat in [1,2,3].
% el = number
% list = el*
%
% lista_multime(L:list, Rez:list)
%    model de flux: (i,o) or (i,i) - determinist
%    L - the list of elements
%    Rez - the list of elements transformed into a set
lista_multime(L, Rez) :- lista_multime_aux(L, [], Rez).

% lista_in_multime(L:list, Col:list, Rez:list)
%     model de flux(i,i,o) - determinist
%     L - the list of elements
%     Col - the collector variable
%     Rez - the list of elements transformed into a set

lista_multime_aux([], Col, Col).                             %Cazul de baza: daca lista este vida, Rez = Col
lista_multime_aux([H | T], Col, Rez) :-
    not(membru(H, Col)),                                     %Daca H nu a fost introdus in Col, il adaug la finalul listei
    adaugfinal(H, Col, ColT),                                %   si continui procesarea recursiva a listei
    lista_multime_aux(T, ColT, Rez).
lista_multime_aux([H | T], Col, Rez) :-
    membru(H, Col),                                          %Daca H a fost introdus in Col, continui procesarea recursiva a listei
    lista_multime_aux(T, Col, Rez).

%membru(E:el, L:list)
%     model de flux(i,i) - determinist
%     E - the element whose membership in the list is verified
%     L - the list of elements


membru(E, [E | _]).                                          %Cazul de baza: daca elementul e capul listei, true
membru(E, [_ | L]) :- membru(E, L).                          %       altfel: se continua recursiv pentru restul listei

% adaugfinal(E:el, L:list, Rez:list)
%     model de flux(i, i, o) - determinist
%     E - the element to be inserted at the end of the list
%     L - the list of elements
%     Rez - the list of elements after insertion the element
adaugfinal(E, [], [E]).                                     %Cazul de baza: daca lista este vida, adaug E in lista
adaugfinal(E, [H | T], [H | Rez]) :- adaugfinal(E, T, Rez). %       altfel: se continua recursiv pentru restul listei


go5 :- lista_multime([1,2,3,1,2],[1,2,3]).
go6 :- lista_multime([],[]).
go7 :- lista_multime([1,2,3],[1,2,3]).
go8 :- lista_multime([1,1,1],[1]).
go9 :- lista_multime([2,2,1,3,3,5,4,5,1,5],[2,1,3,5,4]).
