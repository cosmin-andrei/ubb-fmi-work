bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        
extern exit, fopen, fclose, scanf, fprintf, fread     
import exit msvcrt.dll
import fopen msvcrt.dll  
import fclose msvcrt.dll
import fprintf msvcrt.dll
import scanf msvcrt.dll
import fread msvcrt.dll


;Se da un nume de fisier (definit in segmentul de date). Sa se creeze un fisier cu numele dat, apoi sa se citeasca de la tastatura cuvinte pana cand se citeste de la tastatura caracterul '$'. Sa se scrie in fisier doar cuvintele care contin cel putin o cifra.

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    nume_fisier db "date.txt", 0; numele fisierului care va fi creat
    mod_acces db "%s", 0; s- string: pt scriere
    descriptor_fis dd -1;variabila in care vom salva descriptorul fisierului - necesar pentru a putea face referire la fisier
    formatcitire dd '%s', 0
    
    sir times 10 dw 0
    cuvant dw "", 0
    spatiu db " "
    cifre db '0123456789'
    lc equ $-cifre
    copie times 10 dw 0

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
        mov esi, sir ; initializam pointerul de sir la inceputul sirului
        
        citeste:
            push dword cuvant
            push dword formatcitire
            call [fread]
            add esp, 4*2

            cmp dword [cuvant], '$'
            JE modifesi
            
            mov eax, [cuvant]
            mov [sir+esi], eax
            add esi, 1
        jmp citeste
           
        modifesi:
            mov esi, 0
            jmp ParcurgereSir
            
        ParcurgereSir:
            mov al, byte[sir+esi]
            mov [copie], ecx
            mov ebp, 0
            mov ecx, lc
            
            repetacifre:
                mov bl, byte[cifre+ebp]
                cmp al, bl
                je adauga
                jne next
                
                adauga:
                    push dword [sir+esi]
                    push dword [descriptor_fis]
                    call [fprintf]
                    add esp, 4*2
                
                next:
                    inc ebp
                    
            loop repetacifre
            
            mov ecx, [copie]
            add esi, 1
            
        loop ParcurgereSir
        
        final:
        call [fclose]
        add esp, 4
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
