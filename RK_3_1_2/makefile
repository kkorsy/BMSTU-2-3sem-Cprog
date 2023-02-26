CC := gcc
CFLAGS := -Wall -Werror -Wextra -Wpedantic -g

app.exe: main.o find.o matrix_read.o
	$(CC) -o $@ $^
	
main.o: main.c *.h
	$(CC) $(CFLAGS) -c $<

find.o: find.c find.h errors.h
	$(CC) $(CFLAGS) -c $<

matrix_read.o: matrix_read.c matrix_read.h errors.h
	$(CC) $(CFLAGS) -c $<

clean:
	rm *.txt *.o *.exe
