bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    s db 1,2,3
    ls equ $-s
    
    d resb ls

; our code starts here
segment code use32 class=code
    start:
        mov esi, s
        add esi, ls-1; pt a pozitiona esi la adresa ultimului element la adresa sirului s
        mov edi, d
        mov ecx, ls
        repeta:
            std
            lodsb
            cld
            stosb
        loop repeta
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
