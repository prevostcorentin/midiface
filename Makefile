PREPROCESSOR=-DDEBUG
CC=gcc

%.exe: sources/%.c
	$(CC) -g $< -o $@ $(PREPROCESSOR)

clean:
	del *.exe
