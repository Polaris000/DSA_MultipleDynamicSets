run_code: utils.c list.c driver.c
	gcc -c utils.c list.c
	gcc -o run_code driver.c utils.o list.c 
	./run_code
	rm *.o
