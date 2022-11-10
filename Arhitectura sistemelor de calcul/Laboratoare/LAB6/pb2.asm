bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

                          
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; se da un sir de bytes pozitivi si negativi
    ; sa se extraga intr-un sir n eleme negative
    ; sa se extraga intr un sir p elem pozitive

    s db 1,-2,-1,3,4,-6; => n=-2,-1,-6, p=1,3,4
    ls equ $-s
    n resb ls; edi
    p resb ls; ebp - extended base pointer
    
; our code starts here
segment code use32 class=code
    start:
        mov esi,0
        mov edi,0
        mov ebp,0
        mov ecx,ls
        repeta:
            mov al,byte[s+esi]
            cmp al,0
            JL negativ
            JGE pozitive
                negativ:
                    mov byte[n+edi], al
                    inc edi
                    inc esi
                    
                    jmp endif
                pozitiv:
                    mov byte[p+ebp], al
                    inc ebp
                    inc esi
                myendif:
                    inc esi
        loop repeta
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
