%candidat(N:integer, I:integer)
%model de flux: (i, o) - nedeterminist
% N - limita maxima a intervalului din care putem genera o solutie
% I - candidatul la solutie
candidat(N, N).           %daca candidatul a ajuns la N, acesta
                          %   lua valoarea lui N
candidat(N, I) :-         %altfel se cauta o valoare                                               % pentru I, decrementand N
    N > 1,
    N1 is N - 1,
    candidat(N1, I).

%apare(E:integer, L:list)
%model de flux: (i, i)
% E - elementul pe care il cautam in lista
% L - lista in care cautam aparitia unui element
apare(E, [E | _]).                   %daca elementul coincide cu primule
                                     %      din lista este returnat
apare(E, [_ | T]) :-                 %altfel parcurg recursiv lista
    apare(E, T).

%solutie_aux(N:integer, M:integer, L:list, Lg:integer, Col:list)
%model de flux: (i, i, o, i, i) - nedeterminist
% N - limita maxima a intervalului din care se pot alege valori pentru
%     solutie
% M - numaurul care trebuie sa fie mai mic decat diferenta in
%     modul intre oricare doua numere aflate pe pozitii consecutive
% L - o solutie care indeplineste proprietatea
% Lg - lungimea solutiei
% Col - o solutie partiala posibila care indeplineste proprietatea
solutie_aux(N, _, Col, N, Col) :- !.         %daca solutia are lungimea n
                                             %  returnez solutia
solutie_aux(N, M, L, Lg, [H | T]) :-         %altfel adaug inca un candidat
    candidat(N, I),                          %  la solutie
    abs(H - I) >= M,
    \+apare(I, [H | T]),
    Lg1 is Lg + 1,
    solutie_aux(N, M, L, Lg1, [I | [H | T]]).


%solutie(N:integer, M:integer, L:list)
%model de flux: (i, i, o) - nedeterminist
% N - limita maxima a intervalului din care se pot alege valori pentru
%     solutie
% M - numaurul care trebuie sa fie mai mic decat diferenta in
%     modul intre oricare doua numere aflate pe pozitii consecutive
% L - solutiile care indeplinesc proprietatea
solutie(N, M, L) :-
    candidat(N, I),
    solutie_aux(N, M, L, 1, [I]).


%genereaza_toate_solutiile(N:integer, M:integer, L:list)
%model de flux: (i, i, o) - nedeterminist
% N - limita maxima a intervalului din care se pot alege valori pentru
%     solutie
% M - numaurul care trebuie sa fie mai mic decat diferenta in
%     modul intre oricare doua numere aflate pe pozitii consecutive
% L - solutiile care indeplinesc proprietatea ceruta
genereaza_toate_solutiile(N, M, L) :-
    findall(S, solutie(N, M, S), L),
    write(L).


%afiseaza_solutii(L:list)
%model de flux: (i)
% L - lista cu toate solutiile
afiseaza_solutii([]).
afiseaza_solutii([H | T]) :-
    write(H), nl,                %afisez solutia si trec la linie noua
    afiseaza_solutii(T).















