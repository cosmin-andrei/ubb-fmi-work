;un arbore echilibrat

(defun depth(l)
	(cond
	( (null l) 0 )
	( t (max (+ 1 (depth (cadr l))) (+ 1 (depth (caddr l)))) )
	)
)

;(print (depth '(A (B) (C (D) (E)))))

(defun echilibrat (l)
  (cond	
    ((null l) nil)
    ((= (length l) 1) nil)
    ((= 0 (+ 1 (- (depth (cadr l)) (depth (caddr l))))) t)
    ((= 1 (- (depth (cadr l)) (depth (caddr l)))) t)
    ((= 0 (- (depth (cadr l)) (depth (caddr l)))) t)
    (t nil)
  )
)

(print (echilibrat '(A (B (F (G (I)))) (C (D) (E)))))
