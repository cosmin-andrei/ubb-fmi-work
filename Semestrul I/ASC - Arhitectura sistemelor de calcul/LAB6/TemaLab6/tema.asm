bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

;Se da octetul A. Sa se obtina numarul intreg n reprezentat de bitii 2-4 ai lui A. Sa se obtina apoi in B ;octetul rezultat prin rotirea spre dreapta a lui A cu n pozitii. Sa se obtina dublucuvantul C:
;bitii 8-15 ai lui C sunt 0 - c+2
;bitii 16-23 ai lui C coincid cu bitii lui B
;bitii 24-31 ai lui C coincid cu bitii lui A
;bitii 0-7 ai lui C sunt 1 - c+3

;00FF0300

             
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a db 100001110b
    b db 0
    c dd 0
    n db 0

; our code starts here
segment code use32 class=code
    start:

        mov al, [a]
        shr al, 2; shift right
        AND al, 00000111b; izolare biti din A
        mov [n], al
        mov cl, [n]
        mov al, [a]
        ror al, cl; rotim n pozitii spre dreapta
        
        mov [b], al
        mov byte[c+3], 11111111b
        mov bl, [b]
        mov al,[a]
   
        or byte[c+1], bl ; punem bitii din b in rezultat
        or byte[c], al; punem bitii din a in rezultat
        
        
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
