;8. a) Sa se elimine elementul de pe pozitia a n-a a unei liste liniare.
;l - lista liniara, din care se elimina elementul
;n - atom numeric, pozitia elemntului care trebuie eliminat

(defun elimina (l n)
	(cond
		((null l) nil)    							  ;Daca lista este goala, returnez nil
		((= n 1) (cdr l)) 							  ;Daca sunt la pozitia n, elimin elementul curent
		(t (cons (car l) (elimina (cdr l) (- n 1))))  ;Altfel, nu am ajuns la elementul pe care trebuie sa il elimin si continui parcurgerea listei
	)
)
(print (elimina '(1 2 3 4 5) 3))


;b) Definiti o functie care determina succesorul unui numar reprezentat cifra
;cu cifra intr-o lista. De ex: (1 9 3 5 9 9) --> (1 9 3 6 0 0)

;Inverseaza o lista
;l - lista liniara care trebuie inversata
;col - variabila colectoare, unde se adauga in ordine inversa elementele listei
(defun inversare_lista_aux (l col)
	(cond
		((null l) col)
		(t (inversare_lista_aux (cdr l) (cons (car l) col)))
	)
)
;Inverseaza o lista, initializand si colectoarea
;l - lista liniara care trebuie inversata
(defun inversare_lista (l)
	(inversare_lista_aux l nil)
)
;(print (inversare_lista '(1 2 3)))

;Aduna doua numere reprezentate sub forma de liste, dar in ordine inversa
;l1 - lista liniara
;l2 - lista liniara
;tr - atom numeric ce retine la fiecare pas transportul de la adunarea celor doua liste
(defun suma_aux (l1 l2 tr)
	(cond
		((and (null l1) (null l2)) ;Daca ambele liste sunt goale
		 (cond
	   		 ((= tr 0) nil)           ;Daca nu este transport se intoarce lista goala
			 (t (list tr))		   ;Daca este transport, se adauga la rezultat
		 )
		)
		((null l1)				   ;Daca prima lista e nula
		 (suma_aux (list 0) l2 tr)     ;Continui cu 0 in loc de prima lista	
		)
		((null l2)				   ;Daca prima lista e nula
		 (suma_aux l1 (list 0) tr)     ;Continui cu 0 in loc de a doua lista	
		)
		(t
		 (cons (mod (+ (car l1) (car l2) tr) 10)   ;cifra reziduala
			   (suma_aux (cdr l1) (cdr l2) (floor (/ (+ (car l1) (car l2) tr) 10)))			   ;transportul
		 )
		)
	)
)

;Aduna doua numere, reprezentate sub forma de liste liniare
;l1 - lista liniara
;l2 - lista liniara
(defun suma (l1 l2)
	(inversare_lista (suma_aux (inversare_lista l1) (inversare_lista l2) 0))
)
;(print (suma '(1 2 3) '(5 9 8)))

;Returneaza succesorul unui numar reprezentat sub forma unei liste liniare
;l - lista liniara care reprezinta numarul caruia i se cere succesorul
(defun succesor (l)
	(suma l '(1))
)
(print (succesor '(9 9 9)))

;c) Sa se construiasca multimea atomilor unei liste.Exemplu: (1 (2 (1 3 (2 4) 3) 1) (1 4))
; ==> (1 2 3 4)

;Verifica aparitia unui element intr-o lista liniara
;e - atom numeric, elementul cautat
;l - lista liniara in care se cauta aparitia elementului
(defun apare (e l)
	(cond
		((null l) nil)
		((equal e (car l)) t)
		(t (apare e (cdr l)))
	)
)

;Sterge duplicatele dintr-o lista, folosindu-se de o variabila colectoare pentru a se pastra ordinea
; primei aparitii
;l - lista liniara din care se sterg duplicatele
;col - variabila colectoare care pastreaza ordinea primei aparitii a fiecarui atom
(defun sterge_duplicate_aux (l col)
	(cond
		((null l) col)
		((apare (car l) col) 
		 (sterge_duplicate_aux (cdr l) col)
		)
		(t (sterge_duplicate_aux (cdr l) (append col (list (car l))))) 
	)
)
;Sterge duplicatele, initializand variabila colectoare
;l - lista liniara din care se sterg duplicatele
(defun sterge_duplicate (l)
	(sterge_duplicate_aux l nil)
)
;(print (sterge_duplicate '(1 2 3 4 2 1 4)))

;Extrage atomii dintr-o lista neliniara de la orice nivel intr-o singura lista cu un singur nivel
;l - lista neliniara
(defun extrage_atomi (l)
	(cond
		((null l) nil)
		((atom (car l))
		 (cons (car l) (extrage_atomi (cdr l)))
		)
		(t 
		 (append (extrage_atomi (car l)) (extrage_atomi (cdr l)))
		)
	)
)
;(print (extrage_atomi '(1 (2 (1 3 (2 4) 3) 1) (1 4))))

;Extrage multimea de atomi dintr-o lista cu mai multe nivele
;l - lista neliniara 
(defun multime_atomi (l)
	(sterge_duplicate (extrage_atomi l))
)
(print (multime_atomi '(1 (2 (1 3 (2 4) 3) 1) (1 4))))

;d) Sa se scrie o functie care testeaza daca o lista liniara este o multime.
;Verifica daca o lista liniara este multime
;l - lista liniara
(defun este_multime (l)
	(cond
		((null l) t)
		((apare (car l) (cdr l)) nil)
		(t
		 (este_multime (cdr l))
		)
	)
)
(print (este_multime '(1 4 2 3 4)))