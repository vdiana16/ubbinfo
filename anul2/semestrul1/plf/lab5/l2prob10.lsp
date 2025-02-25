;10. Se da un arbore de tipul (2). Sa se precizeze nivelul pe care apare un nod x in arbore. Nivelul radacii se considera a fi 0.

; As an example, the tree
;   A
;  / \
; B   C
;    / \
;   D   E
; is represented as follows:
; (A (B) (C (D) (E))) (2)

(defun stanga (l)
	(cadr l)
)

(defun dreapta (l)
	(caddr l)
)

(defun radacina (l)
	(car l)
)

(defun nivel_el (l el n)
	(cond 
		((null l) nil)
		((equal (radacina l) el) n)
		(t (or (nivel_el (stanga l) el (+ 1 n)) (nivel_el (dreapta l) el (+ 1 n)))) 
	)
)

(print (nivel_el '(A (B) (C (D) (E))) 'E '0))