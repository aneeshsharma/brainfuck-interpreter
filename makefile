CC = gcc

all:
	${CC} brainfuck.c -o brainfuck

debug:
	${CC} brainfuck.c -o brainfuck -DDEBUG

install: all
	sudo cp brainfuck /usr/bin/brainfuck
	sudo chmod +x /usr/bin/brainfuck
	make clean
	@echo "Installation completed successfully\n"

clean:
	rm -f brainfuck