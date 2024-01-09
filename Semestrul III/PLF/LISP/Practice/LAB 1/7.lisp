; substituire prima aparitie a unui el dintr o lista data

(defun subst(l e i f)
	(cond
	( (null l) l)
	( (and (eq (car l) e) (= f 0))
		(append (list i) (subst (cdr l) e i 1)) )
	( (listp (car l))
		(append (list (subst (car l) e i f)) (subst (cdr l) e i f)) )
	( t (append (list (car l)) (subst (cdr l) e i f)) )
	)
)

(print (subst '(1 2 3 (4 5 6) 7 4 8) 4 0 0))


; c) Sa se inlocuiasca fiecare sublista a unei liste cu ultimul
;; ei element. Prin sublista se intelege element de pe primul nivel,
;; care este lista.
;; Exemplu: (a (b c) (d (e (f)))) ==>
;; (a c (e (f))) ==> (a c (f)) ==> (a c f)
;; (a (b c) (d ((e) f))) ==> (a c ((e) f)) ==> (a c f)

(defun extragere(l)
	(cond
        ( (atom l) l )
        ( (= (length l) 1) (extragere (car l)) )
        ( (> (length l) 1) (extragere (cdr l)) )
    	)
)

(defun inloc(l)
	(cond
	( (null l) l )
	( (listp (car l)) ( append ( list (extragere (car l)) )  (inloc (cdr l))) )
	( t (append (list (car l)) (inloc (cdr l))) )
	)
)

(print (inloc '(a (b c) (d ((e) f)))))