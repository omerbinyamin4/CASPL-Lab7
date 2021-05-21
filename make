exec: c-libs
	gcc -g -m32 -o hexeditplus hexeditplus.o
	rm -f hexeditplus.o 
	
c-libs: hexeditplus.c
	gcc -g -m32 -c -o hexeditplus.o hexeditplus.c
	
.PHONY: clean
clean:
	rm -rf ./*.o hexeditplus