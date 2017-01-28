version = gcc
CFLAGS = -g -std=gnu99 -Wall -Wextra -lpthread
jackpot: main.o display.o threads.o spinner.o controller.o
	$(version) $^ -o $@ $(CFLAGS)
main.o : main.c
	$(version) -c main.c $(CFLAGS)

%.o: %.c %.h
	$(version) $(CFLAGS) $< -c
clean:
	rm -rf *.o jackpot
