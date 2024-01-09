;b) (A B C) (X Y Z) => ( (A.X) (B.Y) (C.Z))

(defun asoc(l1 l2)
	(cond
	( (or (null l1) (null l2)) nil)
	( t (append (list (cons (car l1) (car l2))) (asoc (cdr l1) (cdr l2))) )
	)
)

(print (asoc '(A B C) '(X Y Z)))

;c) nr subliste

(defun nr_subliste (l)
  (cond
    ((null l) 0)
    ((listp (car l))
     (+ (nr_subliste (car l)) (nr_subliste (cdr l)) 1))
    (t (nr_subliste (cdr l)))))


(defun subl(l)
	(nr_subliste (list l))
)

(print (subl '(1 2 (3 (4 5) (6 7)) 8 (9 10))))