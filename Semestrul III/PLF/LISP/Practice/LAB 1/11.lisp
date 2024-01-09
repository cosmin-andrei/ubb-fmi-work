;a cmmmc


(defun cmmdc(a b)
	(cond
	( (= a b) a )
	( (> a b) (cmmmc (- a b) b) )
	( t (cmmmc a (- b a)) )
	)
)

(defun cmmmc(a b)
	(/ (* a b) (cmmdc a b))
)



(defun multipluL(l)
	(cond
	( (null l) l)
	( t (cmmmc (car l) (cadr l)) )
	;(multipluL (cdr l))) )
	)
)

(print (multipluL '(2 8 4)))

;n -nr, p -putere, m-puterea maxima
;(defun factori(n p m)
;	(cond
;	( (= 1 n) m


;b verif munte

(defun munte(l f)
	(cond
	((null l) nil)
	((= (length l) 1) t)
	((= (length l) 2) t)
	( (and (> (car l) (cadr l)) (= f 0))
		(munte (cdr l) 1) ) 
	( (and (< (car l) (cadr l)) (= f 1)) nil)
	( (and (> (car l) (cadr l)) (= f 1))
		(munte (cdr l) 1) ) 
	( (and (< (car l) (cadr l)) (= f 1)) nil)
	( t (munte (cdr l) 0) )
	)
)

(defun munteW (l)
	(munte l 0)
)

(print (munteW '(10 18 29 17 11 10)))


;d produs atomilor

(defun produs(l)
	(cond
	( (null l) 1 )
	( (numberp (car l)) (* (car l) (produs (cdr l))) )
	( (listp (car l)) (* (produs (car l)) (produs (cdr l))) )
	( t (produs (cdr l)) )
	)
)

(print (produs '(1 2 (3 4))))


