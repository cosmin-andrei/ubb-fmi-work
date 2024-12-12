Proiectul consta in implementarea protocolului FTP (Fle Transfer Protocol) intr-o aplicatie client-server, respectand standardul in vigoare: https://datatracker.ietf.org/doc/html/rfc959

Vor fi formate echipa de cate doi studenti:
- un student implementeaza partea de client
- celalalt student implementeaza parea de server

Aplicatia va fi implementata in limbajul C/C++.<br/>
Studentii vor trimite codul sursa cadrelor didactic pe canalele de comunicare disponibile mail/teams.
<br/>Codul sursa va fi analizat de catre cadrele didactice si apoi va fi realizat demo la laborator.
<br/>Termen de predate online: saptamana 10.
<br/>Termen pentru demo: saptamana 12.
<br/>Nu sunt permise folosirea altor librarii care nu sunt standard C/C++ sau care deja implementeaza total sau partial protocolul FTP.

Aplicatia (atat client, cat si server) trebuie implementata astfel incat, cel putin urmatoarele functionalitati sa fie functionale pe partea de client:
- conectare / logare
- deconectare / delogare
- listare fisiere
- urcare fisiere
- descarcare fisiere, inclusiv binary (transfer mode)
- passive

Pentru ca se cere implementarea standardului, partea de client va trebui sa se conecteze la orice alt server FTP care implementeaza standardul, iar partea de server va trebui sa accepte orice alt client FTP care implementeaza standardul.

<br/>Accentul in evaluarea implementarii se va pune pe urmatoarele aspecte:
- validarea parametrilor
- validarea input-ului, sanitizare, etc
- evaluarea rezultatelor apelurilor de functii
- utilizarea api-urilor safe/unsafe
- utilizarea api-urilor bounded unde este cazul
- gestionarea corecta a bufferelor
- aspectul estetic al codului
- NU se evalueaza in mod direct eficienta implementarii.