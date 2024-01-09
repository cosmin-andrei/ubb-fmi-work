;a elim el de pe poz n

(defun elim(l n i)
	(cond
	( (null l) l)
	( (= n i) (cdr l) )
	( t (cons (car l) (elim (cdr l) n (+ i 1))) )
	)
)

(defun elimP (l n)
	(elim l n 1)
)

(print (elimP '(1 2 3 4 5) 3))

;b succesor nr repr ca lista

(defun invers(l)
	(cond
	((null l) l)
	( t (append (invers (cdr l)) (list (car l))) )
))

(print (invers '(1 2 3 4 5)))

(defun succesor (l f)
  (cond
    ((and (null l) (= f 0)) l)
    ((and (null l) (= f 1)) (cons 1 nil))
    ((> (+ (car l) f) 9) (cons 0 (succesor (cdr l) f)))
    (t (cons (+ (car l) f) (succesor (cdr l) 0)))))

(defun succesorW (l)
  (cond
    ((and (= (length l) 1) (not (= (car l) 9))) (list (+ (car l) 1)))
    ((and (= (length l) 1) (= (car l) 9)) '(1 0))
    (t (invers (succesor (invers l) 1)))))

(print (succesorW '(1 9 3 5 9 9)))

(print (succesorW '(1)))
(print (succesorW '(9))) 


;c multime atomi lista neliniara

(defun cauta(l el)
	(cond
	( (null l) nil)
	( (eq (car l) el) t)
	( (listp (car l)) (or (cauta (car l) el) (cauta (cdr l) el)) )
	( t (cauta (cdr l) el) )
	)
)

(defun multime(l)
	(cond
	( (null l) nil )
	( (listp (car l)) (append (multime (car l)) (multime (cdr l))) )
	( t (append (list (car l)) (multime (cdr l))) )
	)
)

;(print (multime '(1 2 (3 (4 5) (6 7)) 8 (9 10 11))))


(defun multimeL(l)
	(cond
	( (null l) l)
	( (cauta (cdr l) (car l)) (multimeL (cdr l)) )
	( t (append (list (car l)) (multimeL (cdr l))) )
	)
)

;(print (multimeL '(1 2 1 3 2 3 1 1 4)))

(defun multimeW(l)
	(invers (multimeL ( invers( multime l ) )))
)

(print (multimeW '(1 (2 (1 3 (2 4) 3) 1) (1 4))))


