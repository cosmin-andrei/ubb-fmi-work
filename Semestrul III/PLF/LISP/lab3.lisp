;Sa se construiasca o functie care intoarce maximul atomilor numerici dintr-o lista, de la orice nivel.

(defun maxim (l)
  (cond 
        ((atom l) (cond ((numberp l) l)
			(t 0)))
        (t (apply #' max (mapcar #' maxim l)))
  )
)

(print (maxim '(1 a (3 5) (b (6 7) 8) 1)))
