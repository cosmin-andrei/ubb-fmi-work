bison -d analizator.y
flex analizator.l
gcc analizator.tab.c lex.yy.c

.\a.exe program1.cpp  #pentru generare asm

asamblare 			nasm -fobj asmCode.asm
linkeditare 		alink -oPE -subsys console -entry start asmCode.obj
depanare  			ollydbg asmCode.exe