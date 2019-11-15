CC = gcc

all:
	${CC} brainfuck.c -o brainfuck

install: all
	sudo cp brainfuck /usr/bin/brainfuck
	sudo chmod +x /usr/bin/brainfuck
	make clean
	@echo "Installation completed successfully\n"

clean:
	rm -f brainfuck