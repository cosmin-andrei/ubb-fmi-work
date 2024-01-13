;invers(l: list)
; lista de input

(defun invers(l)
	(cond
	( (null l) nil)
	( t (append (invers (cdr l)) (list (car l))) )
	)
)

;(print (invers '(A B C D E F)))


;inversL(l: list)
; lista de input
(defun inversL(l)
	(cond
	( (null l) nil)
	( (atom (car l)) (append (inversL (cdr l)) (list (car l))) )
	( t (cons (inversL (car l)) (inversL (cdr l))) )
	)
)

(print (inversL '(A B C D E F)))
(print (inversL '(A B C (D (E F) G H I))))

