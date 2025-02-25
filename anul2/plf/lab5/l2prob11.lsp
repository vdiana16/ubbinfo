; Se da un arbore de tipul (a (b) (c (d) (e))). Sa se afiseze nivelul
; (si lista corespunzatoare a nodurilor) avand un numar maxim de noduri.
; Nivelul radacinii este 0.

; nr_noduri - functie care primeste ca parametri un arbore, un nivel si un nivel curent si returneaza numarul de noduri de pe nivelul dat
; l - arborele lista de tipul 2
; nivel - nivelul pentru care se doreste numarul de noduri, integer
; nivelc - nivelul curent, integer
; output - numarul de noduri de pe nivelul dat
(defun nr_noduri(l nivel nivelc)
    (cond
        ((null l) 0)
        ((equal nivel nivelc) (+ 1 (nr_noduri (cadr l) nivel (+ nivelc 1)) (nr_noduri (caddr l) nivel (+ nivelc 1))))
        (t (+ (nr_noduri (cadr l) nivel (+ nivelc 1)) (nr_noduri (caddr l) nivel (+ nivelc 1))))
    )
)

; nr_nivele - functie care primeste ca parametri un arbore si un numar si returneaza numarul de nivele al arborelui
; l - arborele lista de tipul 2
; nivele - numarul de nivele, integer
; output - numarul de nivele al arborelui
(defun nr_nivele(l nivele)
    (cond
        ((null l) nivele)
        (t (max (nr_nivele (cadr l) (+ nivele 1)) (nr_nivele (caddr l) (+ nivele 1))))
    )
)

; nivel_maxim - functie care primeste ca parametri un arbore, numarul de nivele, un nivel curent, un numar maxim si un nivel maxim si returneaza nivelul cu cel mai mare numar de noduri
; l - arborele lista de tipul 2
; nrNivele - numarul de nivele al arborelui, integer
; nivelCurent - nivelul curent, integer
; maxim - numarul maxim de noduri de pe un nivel, integer
; nivelRet - nivelul cu cel mai mare numar de noduri, integer, OUTPUT
(defun nivel_maxim(l nrNivele nivelCurent maxim nivelRet)
    (cond
        ((> nivelCurent nrNivele) nivelRet)
        ((> (nr_noduri l nivelCurent 0) maxim) (nivel_maxim l nrNivele (+ nivelCurent 1) (nr_noduri l nivelCurent 0) nivelCurent))
        (t (nivel_maxim l nrNivele (+ nivelCurent 1) maxim nivelRet))
    )
)

; nivel_maximMain - functie care primeste ca parametru un arbore si returneaza nivelul cu cel mai mare numar de noduri
; l - arborele lista de tipul 2
(defun nivel_maximMain(l)
    (nivel_maxim l (nr_nivele l 0) 0 -1 0)
)

; lista_noduri - functie care primeste ca parametri un arbore, un nivel si un nivel maxim si returneaza lista nodurilor de pe nivelul dat
; l - arborele lista de tipul 2
; nivel - nivelul pentru care se doreste lista de noduri, integer
; nivelMaxim - nivelul maxim, integer
; output - lista nodurilor de pe nivelul dat
(defun lista_noduri(l nivel nivelMaxim)
    (cond
        ((null l) nil)
        ((= nivel nivelMaxim) (append (list (car l)) (lista_noduri (cadr l) (+ nivel 1) nivelMaxim) (lista_noduri (caddr l) (+ nivel 1) nivelMaxim)))
        (t (append (lista_noduri (cadr l) (+ nivel 1) nivelMaxim) (lista_noduri (caddr l) (+ nivel 1) nivelMaxim)))
    )
)

; lista_noduriMain - functie care primeste ca parametru un arbore si returneaza lista nodurilor de pe nivelul cu cel mai mare numar de noduri
; l - arborele lista de tipul 2
(defun lista_noduriMain(l)
    (lista_noduri l 0 (nivel_maximMain l))
)


(print (nivel_maximMain '(1 (2 (4 () (7)) ()) (3 (5) (6)))))
(print (lista_noduriMain '(1 (2 (4 () (7)) ()) (3 (5) (6)))))