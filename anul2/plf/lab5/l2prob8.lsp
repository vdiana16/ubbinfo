;8. Sa se construiasca lista nodurilor unui arbore de tipul (2) parcurs in inordine.

; As an example, the tree
;   A
;  / \
; B   C
;    / \
;   D   E
; is represented as follows:
;(A (B) (C (D) (E))) (2)

(defun radacina (l)
	(cond 
		((atom l) l)
		(t (car l))
	)
)

(defun stanga (l)
	(cond
		((and (listp l) (> (length l) 1)) (cadr l))
		(t nil)
	)
)

(defun dreapta (l)
	(cond
		((and (listp l) (> (length l) 2)) (caddr l))
		(t nil)
	)
)

(defun inordine (l)
	(cond
		((null l) nil)
		((atom l) (list l))
		(t (append (inordine (stanga l)) (list (radacina l)) (inordine (dreapta l))))
	)
)

(print (inordine '(A (B) (C (D) (E)))))