;c lista cu primele elem ale listelor cu nr impar elem pe nivel superficial

(defun nrElem (l)
	(cond
	( (null l) 0)
	( (atom (car l)) ( + 1 ( nrElem (cdr l) ) ) )
	( T (nrElem (cdr l)) )
	)
)

;(print (nrElem '(1 2 (3 (4 5) (6 7)) 8 (9 10 11))))

(defun elimAtom (l)
	(cond
	( (null l) l)
	( (atom (car l)) (elimAtom (cdr l)) )
	( T (append (car l) (elimAtom (cdr l))) )
	)
)

(print (elimAtom '(3 (4 5) (6 7) (9 10 11))))

(defun listaI (l)
  (cond
   ((null l) l)
   ((zerop (mod (nrElem (list (car l))) 2)) (listaI (elimAtom l)))
   (t (cons (car l) (listaI (elimAtom (cdr l)))))))

(defun listaIW (l)
  (listaI l))

(print (listaIW '(1 2 (3 (4 5) (6 7)) 8 (9 10 11))))

