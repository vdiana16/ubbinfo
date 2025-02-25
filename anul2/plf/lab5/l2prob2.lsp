;2.Sa se tipareasca lista nodurilor de pe nivelul k dintr-un arbore de tipul (1).
 
;De exemplu arborele
;  A
; / \
;B   C
;   / \
;  D   E
;se poate reprezenta astfel in primul mod:
;(A 2 B 0 C 2 D 0 E 0) (1)


;Functie care parcurge subarborele stang
;l - lista su forma careia e reprezentat arborele
;n - numarul de nodurilor
;m - numarul de muchii

(defun parcurge_sub_stang (l n m)
	(cond
		((null l) nil)
		((= n (+ 1 m)) nil)
		(t (cons (car l) (cons (cadr l) (parcurge_sub_stang (cddr l) (+ 1 n) (+ (cadr l) m)))))
		
	) 
)

;Functie principala de parcurgere a subarborelui stang
;l - lista su forma careia e reprezentat arborele
(defun parcurgere_stang (l)
	(parcurge_sub_stang (cddr l) 0 0)
)


;Functie care parcurge subarborele drept
;l - lista su forma careia e reprezentat arborele
;n - numarul de nodurilor
;m - numarul de muchii

(defun parcurge_sub_drept (l n m)
	(cond
		((null l) nil)
		((= n (+ 1 m)) l)
		(t (parcurge_sub_drept (cddr l) (+ 1 n) (+ (cadr l) m)))
		
	) 
)

;Functie principala de parcurgere a subarborelui drept
;l - lista su forma careia e reprezentat arborele
(defun parcurgere_drept (l)
	(parcurge_sub_drept (cddr l) 0 0)
)

;Functie care colecteaza nodurile de pe nivelul k al arborelui binar
(defun gaseste_noduri_nivel (l nivel k)
	(cond
		((null l) nil)
		((equal nivel k) (list (car l)))
		(t (append (gaseste_noduri_nivel (parcurgere_stang l) (+ 1 nivel) k) (gaseste_noduri_nivel (parcurgere_drept l) (+ 1 nivel) k)))
	)
)

;Functia principala care returneaza solutia problemei
(defun main (l k)
	(gaseste_noduri_nivel l 0 k)
)

(print (main '(A 2 B 0 C 2 D 0 E 0) 3))
(print (main '(A 2 B 1 H 1 I 1 J 0 C 2 D 2 F 1 K 0 G 0 E 0) 2))