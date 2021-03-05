all:
	$(CC) -Wall -pedantic -g3 -gdwarf \
		-I ./ -I builtin \
		yosh.c builtin/help.c builtin/about.c builtin/exit.c\
		sandbox.c \
		-o sandbox

clean:
	rm -rf test
