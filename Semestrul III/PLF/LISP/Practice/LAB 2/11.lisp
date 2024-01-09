(defun nodesLevel (l depth n)
	(cond
	( (null l) l)
	( (= depth n)
		(list (car l)) )
	( t (append (nodesLevel (cadr l) (+ 1 depth) n) (nodesLevel (caddr l) (+ 1 depth) n)) )
	)
)

(print (nodesLevel '(A (B) (C (D) (E))) 0 1))

(defun depth (l)
  (cond
    ((null l) 0)
    (t (max (+ 1 (depth (cadr l))) (+ 1 (depth (caddr l)))))
  )
)

(print (depth '(A (B) (C (D) (E)))))


(defun nivelMaxim (l lvl maxim)
  (cond
    ((null l) maxim)
    ((= lvl (depth l)) maxim)
    ((< maxim (length (nodesLevel l 0 lvl))) (nivelMaxim l (+ 1 lvl) (length (nodesLevel l 0 lvl))))
    (t (nivelMaxim l (+ 1 lvl) maxim))
  )
)

(print (nivelMaxim '(A (B) (C (D) (E))) 0 0))

(defun f(l)
	(cons (nodesLevel l 0 (nivelMaxim l 0 0)) (nivelMaxim l 0 0))
)


(print (f '(A (B) (C (D) (E)))))
