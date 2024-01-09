;; c) Sa se scrie o functie care plecand de la o lista data ca
;; argument, inverseaza numai secventele continue de atomi. Exemplu:
;; (a b c (d (e f) g h i)) ==> (c b a (d (f e) i h g))


(defun inversareL(l)
	(cond
	( (null l) l)
	( t (append (inversare (cdr l)) (list (car l))) )
))
	
(defun inversare(l)
	(cond
	( (null l) l)
	( (atom l) (append (inversare (cdr l)) (list (car l))) )
	( t (append (inversare (cdr l)) (inversareL (car l))) )
	)
)

(print (inversare '(a b c (d (e f) g h i))))