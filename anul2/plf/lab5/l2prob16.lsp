;16. Sa se decida daca un arbore de tipul (2) este echilibrat (diferenta dintre
; adancimile celor 2 subarbori nu este mai mare decat 1)

(defun nr_nivele(l nivele)
    (cond
        ((null l) nivele) ; daca lista e vida, returneaza numarul de nivele
        (t (max (nr_nivele (cadr l) (+ nivele 1)) (nr_nivele (caddr l) (+ nivele 1)))) ; altfel, returneaza maximul dintre numarul de nivele al subarborelui stang si numarul de nivele al subarborelui drept
    )
)

(defun echilibrat(l)
    (cond
        ((null l) t) ; daca lista e vida, returnam true
        ((= (abs (- (nr_nivele (cadr l) 0) (nr_nivele (caddr l) 0))) 1) t) ; daca diferenta dintre numarul de nivele al subarborelui stang si numarul de nivele al subarborelui drept este 1, returnam true
        (t nil) ; altfel, returnam false
    )
)

(print (echilibrat '(1 (2 (4 () (7)) ()) (3 (5) (6)))))
(print (echilibrat '(1 (2) (3 (4 () (5)) ()))))