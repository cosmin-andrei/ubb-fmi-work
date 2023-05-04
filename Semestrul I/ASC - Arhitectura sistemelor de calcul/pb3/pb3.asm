bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions

; our data is declared here (the variables needed by our program)
segment data use32 class=data

    ; a*3 - c/b + x - y
    a dw 2
    c db 15
    b dd 4
    x dd 10
    y dq 1
    aux resd 1 ;rezerva un double pentru aux, echivalent cu aux dd 0
    
; our code starts here
segment code use32 class=code
    start:
    
        ; a*3
        
        mov ax, 3
        mul word[a]; dx:ax = a*3
        
        ; salvare dx:ax intr-o variabila
        
        mov word[aux+0], ax
        mov word[aux+2], dx
        
        ; c/b - byte/doubleword
        ; byteul trb sa fie in edx:eax
        
        movzx eax, byte[c]
        mov edx, 0
        div dword[b]
        
        ; eax = catul c/b
        ; aux - eax = doubleword - doubleword
        
        sub [aux], eax ; aux= a*3-c/b
        
        ; aux + x = doubleword + doubleword
        
        mov ebx, [aux]
        add ebx, [x]

        ; ebx=aux+x
        ; ebx-y = doubleword - dq
        ; transforma ebx in 64 biti
        
        mov ecx, 0
        
        ; transfera y in edx:eax
        mov eax, dword[y+0]
        mov edx, dword[y+4]
        
        sub ebx, eax
        sbb ecx, edx
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
