;; 5.
;; a) Definiti o functie care interclaseaza cu pastrarea dublurilor
;; doua liste liniare sortate.

(defun ic(l1 l2)
(cond
	( (null l1) l2 )
	( (null l2) l1 )
	( (< (car l1) (car l2)) (cons (car l1) (ic (cdr l1) l2)) )
	( t (cons (car l2) (ic l1 (cdr l2))) )
))

(print (ic '(1 2 4) '(3 5 6)))

;; b) Definiti o functie care substituie un element E prin elementele
;; unei liste L1 la toate nivelurile unei liste date L.

(defun substituire(l el el1)
(cond
	( (null l) nil )
	( (eq (car l) el) (cons el1 (substituire (cdr l) el el1)) )
	( (listp (car l)) (cons (substituire (car l) el el1) (substituire (cdr l) el el1)) )
	( t (cons (car l) (substituire (cdr l) el el1)) )
))

(print (substituire '(1 2 3 (4 5 2 3) 4 5 3) 3 0))


; c) suma a doua numere repr sub forma de lista

(defun inversare(l)
	(cond
	;( (null l) nil)
	( t (append (inversare (cdr l)) (list (car l))))) )

(print (inversare '(1 2 3 4)))

(defun sumaL (n1 n2 f)
  (cond
    ((and (null n2) (= f 0) n1) n1)
    ((and (null n1) (= f 0) n2) n2)
    ((and (null n2) (= f 1)) (cons (mod (+ 1 (car n1)) 10) (cdr n1)))
    ((and (null n1) (= f 1)) (cons (mod (+ 1 (car n2)) 10) (cdr n2)))
    ((> (+ (car n1) (car n2) f) 9)
     (append (list (mod (+ (car n1) (car n2) f) 10))
             (sumaL (cdr n1) (cdr n2) 1)))
    (t
     (append (list (mod (+ (car n1) (car n2) f) 10))
             (sumaL (cdr n1) (cdr n2) 0)))))

(print (sumaL '(1 5 4 3 2) '(1 3 4 5 9)))

(defun suma (n1 n2)
  (inversare (sumaL (inversare n1) (inversare n2) 0)))

(print (suma '(9 5 4 3 1) '(2 3 4 5 1)))









