; 2.
; a) Definiti o functie care selecteaza al n-lea element
; al unei liste, sau NIL, daca nu exista.

(defun cauta (l n i)
  (cond
    ((= n i) (car l))
    (t (cauta (cdr l) n (+ i 1)))))

(print (cauta '(A 1 2 3) 5 1))

;; b) Sa se construiasca o functie care verifica daca un atom
;; e membru al unei liste nu neaparat liniara.

(defun membru(l el)
	(cond
	((null l) nil)
	( (eq (car l) el) T )
	( (atom (car l)) (membru (cdr l) el) )
	( t (or (membru (cdr l) el) (membru (car l) el)) )
	)
)

(print (membru '(A (B C) D E) 'C))

;; c) Sa se construiasca lista tuturor sublistelor unei liste.
;; Prin sublista se intelege fie lista insasi, fie un element
;; de pe orice nivel, care este lista. Exemplu: (1 2 (3 (4 5) (6 7)) 8 (9 10)) =>
;; ( (1 2 (3 (4 5) (6 7)) 8 (9 10)) (3 (4 5) (6 7)) (4 5) (6 7) (9 10) ).

(defun lista (l)
  (cond
    ((null l) nil)
    ((listp (car l)) (append (list (car l)) (lista (car l)) (lista (cdr l))))
    (t (lista (cdr l)))))

(defun listal (l)
  (lista (list l)))

(print (listal '(1 2 (3 (4 5) (6 7)) 8 (9 10))))

;; d) Sa se scrie o functie care transforma o lista liniara intr-o multime.


(defun elim (l)
  (cond
    ((null l) nil)
    ((membru (cdr l) (car l))
     (elim (cdr l)))
    (t (append (list (car l)) (elim (cdr l))))))

(print (elim '(1 2 3 4 5 6 1 2 3 4)))



