;6. Sa se construiasca lista nodurilor unui arbore de tipul (1) parcurs in inordine.

; As an example, the tree
;   A
;  / \
; B   C
;    / \
;   D   E
; is represented as follows:
; (A 2 B 0 C 2 D 0 E 0) (1)

(defun parcurgere_st (l n m)
	(cond
		((null l) nil)
		((= n (+ 1 m)) nil)
		(t (cons (car l) (cons (cadr l) (parcurgere_st (cddr l) (+ 1 n) (+ (cadr l) m))))) 
	)
)

(defun stanga (l)
	(parcurgere_st (cddr l) 0 0)
)

(defun parcurgere_dr (l n m)
	(cond
		((null l) nil)
		((= n (+ 1 m)) l)
		(t (parcurgere_dr (cddr l) (+ 1 n) (+ (cadr l) m)))
	)
)

(defun dreapta (l)
	(parcurgere_dr (cddr l) 0 0)
)

(defun inordine (l)
	(cond
		((null l) nil)
		(t (append (inordine (stanga l)) (cons (car l) (inordine (dreapta l))))) 
	)
)

(print (inordine '(A 2 B 0 C 2 D 0 E 0)))