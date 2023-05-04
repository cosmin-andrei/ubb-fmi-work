bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
                          
;Se da un sir de octeti S. Sa se determine maximul elementelor de pe pozitiile pare si minimul elementelor de pe pozitiile impare din S.
;Exemplu:
;S: 1, 4, 2, 3, 8, 4, 9, 5
;max_poz_pare: 9
;min_poz_impare: 3

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    s db 1, 4, 2, 3, 8, 4, 9, 3 ; declararea sirului initial s
	l equ ($-s) ; stabilirea lungimii sirului initial l


; our code starts here
segment code use32 class=code
    start:
        mov ecx, l; punem lungimea in ECX pentru a putea realiza bucla loop de ecx ori
        mov bl, [s+1]
        mov dl, [s+0]
        mov esi, s

        repeta:
            mov al, [esi+1]
            cmp al, bl
            jb move
            move:
                mov bl, al
                
            mov al, [esi]
            cmp al, dl
            jg move2
            move2:
                mov dl, al
          
            add esi, 2
            dec ecx
            
        loop repeta


        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
