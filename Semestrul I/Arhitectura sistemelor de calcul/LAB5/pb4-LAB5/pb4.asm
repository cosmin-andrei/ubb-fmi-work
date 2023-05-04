bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; se da un sir de dd
    ; sa se inverseze elementele sirului
    s dd 1,2,3
    ls equ ($-s)/4
    r resd ls

; our code starts here
segment code use32 class=code
    start:
        mov esi, ls*4-4; pozitionare esi la adresa de inceput a ultimului dd din sir
        mov edi, 0 ;r
        mov ecx, ls
        
        repeta:
            mov eax, dword[s+esi]
            mov dword[r+edi], eax
            sub esi, 4
            add edi, 4
            
        loop repeta
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
