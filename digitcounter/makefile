exec: c-libs
	gcc -g -m32 -fno-pie -o digit_counter digit_counter.o
	rm -f digit_c.o 
	
c-libs: digit_counter.c
	gcc -g -m32 -fno-pie -c -o digit_counter.o digit_counter.c
	
.PHONY: clean
clean:
	rm -rf ./*.o digit_counter