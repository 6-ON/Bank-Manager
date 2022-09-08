
CC=gcc
OBJS=main.o accounts.o bank_management.o menu.o model.o
FLAGS = -o Bank
all: Bank

main:
	$(CC) main.c -c

model:
	$(CC) libs/model.c -c

menu:
	$(CC) libs/menu.c -c

bank_management:
	$(CC) libs/bank_management.c -c

accounts:
	$(CC) libs/accounts.c -c

Bank: main bank_management menu model accounts
	$(CC) $(OBJS) $(FLAGS)


clean: Bank
	rm *.o