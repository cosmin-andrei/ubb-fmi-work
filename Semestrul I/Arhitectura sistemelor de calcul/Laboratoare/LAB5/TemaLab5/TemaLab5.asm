bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data

    ;cerinta
    ;x-(a*a+b)/(a+c/a); a,c-byte; b-doubleword; x-qword
    a db 10
    c db 3
    b dd 5
    x dq 6
    
; our code starts here
segment code use32 class=code
    start:
        
        MOV al,[a]
        IMUL byte[a]; ax=a*a
        CWDE ; convertire double word extended
        ADD eax,[b]; eax=a*a+b
        
        push eax
        
        MOV al, [c]
        CBW
        IDIV byte[a]; al:=c/a
        ADD ax,[a]; ax:=c/a+a
        
        pop dx
        pop ax
        idiv bx; ax:=(a*a+b)/(a+c/a)
        
        CWDE ; convert to double extended
        CDQ ; convert to quad word
        
        mov ebx, dword[x+4]; high
        mov ecx, dword[x]; low
        
        sub ecx, eax ; scaderea din partea low 
        sbb ebx, edx ; scaderea din partea high
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
