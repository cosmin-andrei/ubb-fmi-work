bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit, fopen, fprintf, fclose
import exit msvcrt.dll  
import fopen msvcrt.dll  
import fprintf msvcrt.dll
import fclose msvcrt.dll
import getchar msvcrt.dll
extern scanf,printf,gets, getchar
import scanf msvcrt.dll
import printf msvcrt.dll
import gets msvcrt.dll

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ;Se da un nume de fisier (definit in segmentul de date). Sa se creeze un fisier cu numele dat, apoi sa se citeasca de la tastatura cuvinte pana cand se citeste de la tastatura caracterul '$'. Sa se scrie in fisier doar cuvintele care contin cel putin o cifra.
    
    formatcitire dd '%s', 0
    nume_fisier db "cuvinte.txt", 0  ; numele fisierului care va fi creat
    mod_acces db "a", 0 ; modul de deschidere a fisierului - 
    ; a - pentru adaugare. daca fiserul nu exista, se va crea      
    text db "", 0 ; textul care va fi adaugat in fisier
                                    
    descriptor_fis dd -1 ; variabila in care vom salva descriptorul fisierului - necesar pentru a putea face referire la fisier
    inceput db 'Introduceti cuvinte. Cand va opriti introduceti $:', 0
    cifre db '0123456789'
    lc equ $-cifre
    copie dw 0
    numere dw 0

; our code starts here
segment code use32 class=code
    start:
        ; apelam fopen pentru a crea fisierul
        ; functia va returna in EAX descriptorul fisierului sau 0 in caz de eroare
        ; eax = fopen(nume_fisier, mod_acces)
        push dword mod_acces     
        push dword nume_fisier
        call [fopen]
        add esp, 4*2                ; eliberam parametrii de pe stiva

        mov [descriptor_fis], eax   ; salvam valoarea returnata de fopen in variabila descriptor_fis
        
        ; verificam daca functia fopen a creat cu succes fisierul (daca EAX != 0)
        cmp eax, 0
        je final
        
        ; adaugam/scriem textul in fisierul deschis folosind functia fprintf
        ; fprintf(descriptor_fis, text)
        ; mesaj pt citire sir
        push dword inceput
        call [printf]
        add esp, 4*1
        
        citeste:
            push dword cuvant
            push dword formatcitire
            call [fread]
            add esp,4*2
            cmp [cuvant], '$'
            JE LoopCuv
            JNE Insert
                Insert:
                    mov ax, offset numere ; adresa vectorului de numere
                    mov dx, 
                    mov [ax], dx ; salveaza cuvantul in vector
                    add ax, 2; trece la urmatoarea pozitie din vector
                    mov numere, ax
                             
        
        LoopCuv:
            mov cl, 
            

            
            ;verificam daca contine o cifra
            
            mov si, 0
            mov di, 0
            mov word 
            mov al, byte[text+esi]
            mov [copie], ecx
            mov ebp, 0
            mov ecx, lc
            repetacifre:
                mov bl, byte[cifre+ebp]
                cmp al, bl
                je adauga
                jne next
                    adauga:
                        push dword text
                        push dword [descriptor_fis]
                        call [fprintf]
                        add esp, 4*2
                    next:
                        inc ebp
            loop repetacifre
            
            mov ecx,[copie]
            add esi, 1
                   
        loop repeta  
    
        Sfarsit:
            call [fclose]
            add esp, 4
        
        
      final:
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
