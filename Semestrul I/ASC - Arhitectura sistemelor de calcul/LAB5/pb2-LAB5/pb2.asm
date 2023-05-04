bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; se da un sir de worduri
    ; sa se salveze intr un alt sir doar bytes divizibili cu 7
    s dw 7, 14, 3
    ls equ ($-s)/2
    d resb ls*2

; our code starts here
segment code use32 class=code
    start:
        mov ecx, ls*2
        mov esi, 0
        mov edi, 0
        repeta:
            mov al, byte[s+esi]
            cbw
            mov bl, 7
            idiv bl
            cmp ah, 0; daca e 0 e div cu 7
            JE adauga
            JNE next
                adauga:
                    mov byte[d+edi], dl
                    inc edi
                next:
                    inc esi
                
                    
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
