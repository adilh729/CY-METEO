all : exec

main.o : main.c ABR.h ABL.h TAB.h 
	gcc -c $< -o $@

ABR.o : ABR.c ABR.h
	gcc -c $< -o $@
	
AVL.o : ABL.c ABL.h	
	gcc -c $< -o $@

TAB.h : TAB.c TAB.h
	gcc -c $< -o $@
	
	
	
exec : maion.o ABR.o
	gcc main.o ABR.o AVL.o TAB.o exec
