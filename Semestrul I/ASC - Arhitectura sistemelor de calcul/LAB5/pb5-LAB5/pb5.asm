bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; se da un sir de quadwords
    ; se da o const k
    ; sa se adune const k la fiecare quad din sir
    
    s dq 1,2,3
    ls equ ($-s)/8
    r resq ls
    k equ 0ah
    

; our code starts here
segment code use32 class=code
    start:
        mov ecx, ls
        mov esi, 0
        repeta:
            mov eax, dword[s+esi+0]
            mov edx, dword[s+esi+4]
            add eax, k
            adc edx, 0
            mov dword[r+esi+0], eax
            mov dword[r+esi+4], edx
            add esi, 8
        loop repeta
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
