CC := gcc
CFLAGS := -Wall -Werror -Wextra -Wpedantic

app.exe: node.o list.o main.o
	$(CC) $^ -o $@

main.o: main.c
	$(CC) $(CFLAGS) -c $<

list.o: list.c
	$(CC) $(CFLAGS) -c $<

node.o: node.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.exe *.o *.txt