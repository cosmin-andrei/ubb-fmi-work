bits 32
global start

extern exit
import exit msvcrt.dll

extern scanf
import scanf msvcrt.dll

extern scanf
import scanf msvcrt.dll

extern scanf
import scanf msvcrt.dll

extern printf
import printf msvcrt.dll

segment data use32 class=data
	 y times 4 db 0
	 c times 4 db 0
	 b times 4 db 0
	 a times 4 db 0
	 temp7 times 4 db 0
	 format db "%d", 0

segment code use32 class=code
	start:
		push dword a
		push dword format
		call [scanf]
		add ESP, 4 * 2

		push dword b
		push dword format
		call [scanf]
		add ESP, 4 * 2

		push dword c
		push dword format
		call [scanf]
		add ESP, 4 * 2

		mov EAX, 2
		mov EBX, 5
		imul EAX, EBX
		mov dword [temp7], EAX
		mov EAX, dword [a]
		add EAX, dword [b]
		add EAX, dword [c]
		add EAX, dword [temp7]
		sub EAX, 1
		mov dword [y], EAX
		push dword [y]
		push dword format
		call [printf]
		add ESP, 4 * 2

		push dword 0
		call [exit]
