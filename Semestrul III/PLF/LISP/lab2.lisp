; Se da un arbore de tipul (1). Sa se precizeze nivelul pe care apare un nod
; x in arbore. Nivelul radacii se considera a fi 0. 

;isNod(l: list, e: atom)
;verifica daca e se afla in l
(defun isNod (l e)
    (cond 
        ((null l) nil)
        ((eq (car l) e) t)
        (t (isNod (cddr l) e ))
    )
)

;runStang(l: list, nivel: integer, n: integer)
;l - arbore
;nivel - nivel curent
;n - adancime nod curent
; parcurg subarborele stang si construiesc o lista noua a acestui subarbore

(defun runStang(l nivel n)
  (cond
    ((null l) nil)
    ((= nivel (+ 1 n)) nil)
    ;adaug primul si al doilea element la lista curenta
    (t (cons (car l) (cons (cadr l) (runStang (cddr l) (+ 1 nivel) (+ (cadr l) n)))))
  )
)


;runDrept(l: list, nivel: integer, n: integer)
;l - arbore
;nivel - nivel curent
;n - adancime nod curent
; parcurg subarborele drept si construiesc o lista noua a acestui subarbore

(defun runDrept(l nivel n)
  (cond
    ((null l) nil)
    ((= nivel (+ 1 n)) l) ;nivel = adancime+1
    (t (runDrept (cddr l) (+ 1 nivel) (+ (cadr l) n)))
  )
)

;functie apel pt parcurgere
(defun stang(l)
  (runStang (cddr l) 0 0)
)

;functie apel pt parcurgere
(defun drept(l)
  (runDrept (cddr l) 0 0)
)

;nivel(l: list, e: atom)
;parcurge arborele recursiv pentru a gasi nivelul nodului e
(defun nivel(l e)
  (cond
    ((null l) nil) ;conditie arbore nul
    ((eq (car l) e) 0)
    ((isNod(stang l) e ) (+ 1 (nivel (stang l) e))) ;daca se gaseste in subarborele stang
    (t (+ 1 (nivel (drept l) e)))
  )
)

(print (nivel '(a 2 b 1 d 1 e 1 f 2 g 0 h 2 j 0 k 0 c 2 l 2 n 0 q 2 p 0 r 0 m 0) 'r))