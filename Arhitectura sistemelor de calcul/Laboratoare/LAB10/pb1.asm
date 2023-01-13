bits 32 ; assembling for the 32 bits architecture

; declare the EntryPoint (a label defining the very first instruction of the program)
global start        

; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions             
extern scanf,printf,gets, getchar
import scanf msvcrt.dll
import printf msvcrt.dll
import gets msvcrt.dll
import getchar msvcrt.dll 

; our data is declared here (the variables needed by our program)
segment data use32 class=data
    ; Se citesc de la tastatura numere (in baza 10) pana cand se introduce cifra 0. Determinaţi şi afişaţi cel mai mic număr dintre cele citite.
    x dd 0
    formatcitire db '%d', 0
    mesajafisare db 'Cel mai mic numar este %d', 0
    inceput db 'Introduceti nr. Cand va opriti introduceti 0: ', 0
    minim dd 80000000h
    

; our code starts here
segment code use32 class=code
    start:
        ;mesaj pt citire sir
        push dword inceput
        call [printf]
        add esp, 4*1
        
        repeta:
            ;citire o val pentru x
            push dword x
            push dword formatcitire
            call [scanf]
            add esp, 4*2
            mov eax, [x]
                        
            ; verificam daca s-a introdus 0 de la tastatura
            cmp eax, 0 
            JE finalsiafisare
            JNE compara
            
            ;obtinem minimul
            compara:
                cmp eax, [minim]
                jb move
                jmp repeta
                move:
                    mov [minim], eax
                    jmp repeta
            
            finalsiafisare:
                push dword [minim]
                push dword mesajafisare
                call [printf]
                add esp, 4*2

        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program
