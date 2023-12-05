; Definiti o functie care intoarce suma a doi vectori.


;sumaVect(l1: list, l2: list)
;returneaza suma a 2 liste
(defun sumaVect (l1 l2)
  (cond
    ((null l1) l2) ;daca prima lista e goala, voi returna a doua lista
    ((null l2) l1) ;daca a doua lista e goala, voi returna prima lista
    (t (cons (+ (car l1) (car l2)) (sumaVect (cdr l1) (cdr l2)))) ;adun capetele si apelez recursiv
  )
)

(print "sumaVect")
(print (sumaVect '(1 2 3) '(1 2 3)))


;appendL(l1: list, l2: list)
(defun appendL(l1 l2)
	(cond
		((null l1) l2) ;prima lista nula, returnez a doua lista
		(t (cons (car l1) (appendL(cdr l1) l2))) ;adaug primul elem la lista rezultata si apelez recursiv pt restul listei l1
	)
)

;(print "appendL")
;(print (appendL '(1 2 3) '(4 5 6)))


;Definiti o functie care obtine dintr-o lista data lista tuturor atomilor care apar, pe orice nivel, dar in aceeasi ordine. De exemplu:
; (((A B) C) (D E)) --> (A B C D E)


;elimNIL(l:list)
; elimina nil din lista mea
(defun elimNIL (l)
  (if l ;daca lista nu e goala
      (if (not (null (car l))) ;verif daca primul elem nu este nil
          (cons (car l) (elimNIL (cdr l))); adaug la rezultat si apelez recursiv restul
          (elimNIL (cdr l))) ; trec la urmatorul elem
      nil)) ;daca lista e goala, return nil

;(print "elimNIL")
;(print (elimNIL '(1 2 NIL 3 NIL 4 NIL)))


(defun listaAtom(l)
	(cond
		((null l) nil) ;lista vida - return nil
		((atom l) (list l)) ;l atom - return lista cu atom
		(t (appendL (listaAtom (car l)) ;concatenez atomii din primul elem
			(listaAtom (cdr l)))) ;concatenez atomii din restul listei
	)
)

(print "listaAtom")
(print (elimNIL (listaAtom '(((A B) C) (D E)))))

;c) Sa se scrie o functie care plecand de la o lista data ca argument, inverseaza numai secventele continue de atomi. Exemplu:
; (a b c (d (e f) g h i)) ==> (c b a (d (f e) i h g))

;inversC(l: list, r: lista rezultat)
(defun inversC (l r)
	(cond
		((null l) r) ;l-nula, return r
		
		;primul element este sublista - se inverseaza sublista si este adaugat la r
		((listp (car l)) (appendL r (appendL (list (inversC (car l) nil)) (inversC (cdr l) nil))))
		; elementul este adaugat la r
		(t (inversC (cdr l) (appendL (list (car l)) r)))
  	)
)

(print "inversare")
(print (inversC '(a b c (d (e f) g h i) j) nil))


;d) Sa se construiasca o functie care intoarce maximul atomilor numerici dintr-o lista, de la nivelul superficial.

;maxim(l: list, m)
(defun maxim (l m)
 	(cond
   	((null l) m)
	((listp (car l)) (maxim (cdr l) m))
   	((and (not m) (numberp (car l))) (maxim (cdr l) (car l)))
   	((and (> (car l) m) (numberp (car l))) (maxim (cdr l) (car l)))
   	(t (maxim (cdr l) m))
	)
)



(print "maxim")
(print (maxim '(1 2 (7 8) 5 3 (9 3) 1) nil))
						