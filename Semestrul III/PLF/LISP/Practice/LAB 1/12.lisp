; b max de la orice nivel

(defun maxim(l)
	(cond
	( (null l) 0 )
	( (numberp (car l)) (max (car l) (maxim (cdr l))) )
	( (listp (car l)) (max (maxim (car l)) (maxim (cdr l))) )
	( t (maxim (cdr l)) )
	)
)

(print (maxim '(1 2 (4 2))))

;c lista permutarilor unei liste date
;  ????


;d nr elem par/impar pe primul nivel, fara numarare

(defun par (l f)
  (cond
   ((and (null l) (= f 0)) t)
   ((and (null l) (= f 1)) nil)
   ((and (atom (car l)) (= f 0)) (par (cdr l) 1))
   ((and (atom (car l)) (= f 1)) (par (cdr l) 0))
   (t (par (cdr l) f))))

(defun parW (l)
  (par l 0))

(print (parW '(1 2 (a b c) 3 4)))
