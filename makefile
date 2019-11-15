CC = gcc

all:
	${CC} brainfuck.c -o brainfuck

install: all
	sudo cp brainfuck /usr/bin/brainfuck
	sudo chmod +x /usr/bin/brainfuck

clean:
	rm -f brainfuck