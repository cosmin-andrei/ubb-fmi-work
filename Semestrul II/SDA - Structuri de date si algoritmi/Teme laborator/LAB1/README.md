Să se implementeze în C++ un anumit container de date (TAD) folosind o anumită
reprezentare (indicată) și un vector dinamic ca structură de date. Se va folosi implementare
proprie pentru vectorul dinamic.


6. TAD Colecție – memorată sub forma unui vector de frecvențe.
Spre exemplu, colecția [5, 10, -1, 2, 3, 10, 5, 5, -5] va fi reprezentată sub forma vectorului
V=[1, 0, 0, 0, 1,0, 0, 1, 1, 0, 3, 0, 0, 0, 0, 2] construit astfel: (1) intervalul de valori [-5, 10] se
translatează în intervalul [0, 16]; (2) pe poziția 0 în V avem frecvența elementului -5 (minim);
pe poziția 1 avem frecvența elementului -4, …, pe poziția 15 avem frecvența elementului 10
(maxim).
