;a

(defun adauga_atom (l el i)
  (cond
    ((null l) l)
    ((= (mod i 2) 0) (cons (car l) (cons el (adauga_atom (cdr l) el (+ i 1)))))
    (t (cons (car l) (adauga_atom (cdr l) el (+ i 1))))))

;(print (adauga_atom '(1 2 3 4 5 6 7 8) 0 1))

(defun adauga (l el)
  (cond
    (t (adauga_atom l el 1))))

(print (adauga '(1 2 3 4 5 6 7 8) 0))


;b

(defun invers(l)
    (cond
        ( (null l) () )
        ( (atom (car l)) (append (invers (cdr l)) (list (car l))) )
        ( T (append (invers (cdr l)) (invers (car l))) )
    )
)

(print (invers '(((A B) C) (D E))))


;c

(defun cmmdc (a b)
  (cond
    ((= b 0) a)
    (t (cmmdc b (mod a b)))))

(defun divizorl (l)
  (cond
    ((null l) 0)
    ((numberp (car l)) (cmmdc (car l) (divizorl (cdr l))))
    (t (cmmdc (divizorl (car l)) (divizorl (cdr l))))))

(print (divizorl '(10 (2) (8) 4)))



;d

(defun aparitii (l el)
  (cond
    ((null l) 0)
    ((and (atom (car l)) (eq (car l) el))
     (+ 1 (aparitii (cdr l) el)))
    ((listp (car l))
     (+ (aparitii (car l) el) (aparitii (cdr l) el)))
    (t (aparitii (cdr l) el))))


(print (aparitii '(1 (2 3) 4 (5 (4 6) 4) 7) '4))

