;6.
;a) Sa se scrie de doua ori elementul de pe pozitia a n-a a unei liste liniare. De exemplu, pentru (10 20 30 40 50) si n=3 se va produce (10 20 30 30 40 50).
(defun dublare (l n)
	(cond 
		((null l) nil)
		((equal n 1) (append (list (car l) (car l)) (dublare (cdr l) (- n 1))))
		(t (cons (car l) (dublare (cdr l) (- n 1))))
	)
)
(print (dublare '(10 20 30 40 50) '3))

;b) Sa se scrie o functie care realizeaza o lista de asociere cu cele doua liste pe care le primeste. De ex: (A B C) (X Y Z) --> ((A.X) (B.Y) (C.Z)).
(defun asociere (l1 l2)
	(cond
		((and (null l1) (null l2)) nil)
		((null l1) (cons nil (car l2)))
		((null l2) (cons (car l1) nil))
		(t (append (list (cons (car l1) (car l2))) (asociere (cdr l1) (cdr l2))))
	)
)
(print (asociere '(A B C) '(X Y Z)))

;c) Sa se determine numarul tuturor sublistelor unei liste date, pe orice nivel. Prin sublista se intelege fie lista insasi, fie un element de pe  orice nivel, care este lista. 
;Exemplu: (1 2 (3 (4 5) (6 7)) 8 (9 10)) => 5 (lista insasi, (3 ...), (4 5), (6 7), (9 10)).
(defun nr_subliste (l)
	(cond
		((atom l) 0)
		(t (+ 1 (apply '+ (mapcar 'nr_subliste l))))
	)
)

(print (nr_subliste '(1 2 (3 (4 5) (6 7)) 8 (9 10))))

;d) Sa se construiasca o functie care intoarce numarul atomilor dintr-o lista, de la nivel superficial.
(defun nr_atomi (l)
	(cond
		((null l) 0)
		((atom (car l)) (+ 1 (nr_atomi (cdr l))))
		(t (nr_atomi (cdr l)))
	)
)
(print (nr_atomi '(1 2 (3 (4 5) (6 7)) 8 (9 10))))