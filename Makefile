CC=gcc
CC_FLAGS=-Wall
DEFINES=-DDEBUG

#.SILENT:


windows: static-lib lib/libmidi.dll examples


static-lib: $(patsubst sources/%.c, obj/%.o, $(wildcard sources/*.c)) lib/libmidi.a

obj/%.o: sources/%.c
	$(CC) -c $(CC_FLAGS) -g $< -o $@ -I.

lib/libmidi.a:
	ar rvs -o $@ $(wildcard obj/*.o)

lib/libmidi.dll:
	$(CC) -DWINDOWS -shared -o lib/libmidi.dll $(wildcard obj/*.o) -Wl,--out-implib,lib/libmidi.a


examples: $(patsubst examples/sources/%.c, examples/bin/%.exe, $(wildcard examples/sources/*.c))

examples/bin/%.exe: examples/sources/%.c
	$(CC) $(CC_FLAGS) -g $< $(wildcard obj/*.o) -o $@ -I. -Llib -lmidi



clean:
	del obj\*.o
	del lib\*.a
	del examples\bin\*.exe
