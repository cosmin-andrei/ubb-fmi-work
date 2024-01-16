;(load "D:/ubb-fmi-work/Semestrul III/PLF/LISP/Colocviu/sub8.lisp")

(defun inaltime(l e niv)
	(cond
	( (and (atom (car l)) (eq l e)) niv)
	( (listp (car l)) (or (inaltime (car l) e niv) (inaltime (cdr l) e (- niv 1)) ) )
	( t (inaltime (cdr l) e (- niv 1)) )
	)
)

(defun det_lg(l)
	(cond
	( (atom l) 1)
	( t (apply #'+ (mapcar #' det_lg l)) )
	)
)

(print (det_lg '(c (d (e)) (f))))