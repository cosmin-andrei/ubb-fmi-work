bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
                  
                  
;pb. 9 Se da un sir de dublucuvinte. Sa se obtina, incepand cu partea inferioara a dublucuvantului, dublucuvantul format din octetii
;superiori pari ai cuvintelor inferioare din elementele sirului de dublucuvinte. Daca nu sunt indeajuns octeti
;se va completa cu octetul FFh.

; 0 - de la stg la dr
; 1 - de la dr la stg


; our data is declared here (the variables needed by our program)
segment data use32 class=data
    s dd 12345678h, 1A2C3C4Dh, 98FCDD76h, 12783A2Bh; se va obtine d DD FF3A3C56h
    par db 2; variabila folosita pentru a testa daca numarul este par
    ls equ($-s)/4
    d resb ls
    

; our code starts here
segment code use32 class=code
    start:
        
        mov ecx, ls; punem lungimea in ecx pt a realiza bucla loop
        mov esi, s
        mov edi, d+ls-1; punem adresa lui d de la dr la stg
        jecxz sfarsit
        
        repeta:
            cld; parcurgem sirul de la stanga la dreapta
            lodsd; in eax vom avea dublucuvant
            
            mov al, ah
            mov bl, ah
            mov ah, 0
            
            div byte[par]; vedem daca al este par
            ;mov al, ah; mutam restul din ah in al
            cmp ah, 0
            jne pas
            
            adauga_in_d:
                mov al, bl
                std
                stosb 
                
            pas:
                loop repeta; daca mai sunt elemente pe parcurs(ecx>0) reia ciclul
        
        add edi, 1
        cmp edi, d; se verifica daca a ajuns la final
        je sfarsit
        mov ecx, edi
        sub ecx, d
        mov al, 0FFh
        sub edi, 1
        repeta2:
           std
           stosb
        loop repeta2
            
    sfarsit:
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
