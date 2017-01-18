flags = -std=gnu99 -g -Wall -Wextra
jackpot: main.o display.o threads.o spinner.o
	gcc $^ -o jackpot -lrt -lpthread

main.o: main.c
	gcc $(flags) -c $<

display.o: display.c display.h
	gcc $(flags) -c $<

spinner.o: spinner.c spinner.h
	gcc $(flags) -c $<

threads.o: threads.c threads.h
	gcc $(flags) -c $<
