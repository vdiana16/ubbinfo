;12. Sa se construiasca lista nodurilor unui arbore de tipul (2) parcurs in 
;postordine
(defun stanga (l)
	(cadr l)
)

(defun dreapta (l)
	(caddr l)
)

(defun radacina (l)
	(car l)
)


(defun preordine(l)
    (cond
        ((null l) nil) ; daca lista e nula, returneaza nil
        (t (append (list (radacina l)) (preordine (stanga l)) (preordine (dreapta l)))) ; altfel, returneaza concatenarea radacinii, preordinea subarborelui stang si preordinea subarborelui drept
    )
)



(print (preordine '(1 (2 (4 () (7)) ()) (3 (5) (6)))))