Parcari

Pentru a-si gestiona locurile de parcare, o firma a proiectat us sistem client-server.
Serverul gestioneaza o lista de locuri de parcare, fiecare loc avand urmatoarele proprietati
  id - numar intreg,
  number - sir de caractere,
  takenBy - sir de caractere indicand utilizatorul care a ocupat locul
Dezvoltati o aplicatie client mobila dupa cum urmeaza.

1. La prima lansare in executie a aplicatiei, un prim ecran permite utilizatorului sa-si
introduca numele (username) si sa declanseze un buton 'Next' pentru a naviga la al doilea ecran.
La relansarea in executie, daca utilizatorul a declansat butonul 'Next' la lansarile
anterioare, automat aplicatia va naviga catre al doilea ecran [1p].

2. In contextul celui de-al doilea ecran, aplicatia descarca locurile de parcare via GET /space,
prezentand un indicator de progress pe durata descarcarii.
Daca apelul GET esueaza, aplicatia va notifica utilizatorul si va prezenta locuri de parcare
daca acestea au fost descarcate anterior de aplicatie in sesiunile anterioare de lucru [1p].

3. Daca apelul GET de la punctul (3) esueaza, un buton 'Retry' va permite utilizatorului sa reia
operatia de descarcare a locurilor [1p].

4. O lista prezinta locurile de parcare. Locurile libere sunt marcate cu verde iar cele ocupate
de utilizatorul curent cu galben [1p].

5. Utilizatorul poate cauta locuri de parcare dupa numarul lor [1p].

6. Cand utilizatorul face click pe un element din lista, daca el reprezinta [1p]:
(a) un loc liber, elementul va fi expandat si un buton 'Take' va fi prezentat.
(b) un loc ocupat de utilizatorul curent (takenBy = username), elementul va fi expandat si un buton
'Release' va fi prezentat.

7. Cand utilizatorul declanseaza butoanele 'Take' & 'Release', aplicatia actualizeaza locul via
PUT /space/:id, incluzand in corpul cererii status cu valorile 'taken', respectiv 'free',
si takenBy cu valoarea username, respectiv ''. Un indicator de progress este prezentat de element
in timpul operatiei PUT [1p].

8. Daca operatia PUT e efectuata cu succes, lista va fi actualizata corespunzator.
Daca operatia PUT esueaza, o notificare va fi afisata iar utilizatorul va putea
relua operatia esuata declansand un buton 'Retry' [1p].

9. Serverul emite notificari prin ws pe localhost:3000. Notificarile indica faptul un
loc de parcare a fost actualizat. Daca conexiunea prin web socket esueaza, aplicatia
va reincerca sa se conecteze [1p].
