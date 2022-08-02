CC = gcc
CFLAGS = -Wall -ansi -pedantic -Werror
OBJ = main.o module.o linkedList.o
EXEC = calculator

$(EXEC) : $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

main.o : main.c module.h
	$(CC) -c main.c $(CFLAGS)

module.o : module.c module.h linkedList.h
	$(CC) -c module.c $(CFLAGS)

linkedList.o : linkedList.c linkedList.h
	$(CC) -c linkedList.c $(CFLAGS)

clean :
	rm -f $(EXEC) $(OBJ)