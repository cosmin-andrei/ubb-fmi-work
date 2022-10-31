bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a db 1ah
    b dw 2c3dh
    c dd 11223344h
    x dw 14
    y dd 10011111b

; our code starts here
segment code use32 class=code
    start:
        
        mov al, [a]
        mov bx, [b]
        mov ecx, [c]
        mov dword [c],1
        mov ax, [x]
        mov ay, [y]
        mov dword [y],1
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
