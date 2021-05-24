all:

builtin/about.o:
	$(CC) -c -MMD builtin/about.c $(CFLAGS) -o build/builtin/about.c

clean:
	rm -rf test sandbox
