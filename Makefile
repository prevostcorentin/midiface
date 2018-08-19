CC=gcc
CC_FLAGS=-Wall
DEFINES=-DDEBUG
LIB_OBJS=$(subst sources/, obj/, $(patsubst %.c, %.o, $(wildcard sources/*.c)))
EXAMPLES_OBJS=$(subst sources/, obj/, $(patsubst %.c, %.o, $(wildcard examples/sources/*.c)))

static-lib: lib obj lib/midilib.a

lib:
	mkdir lib

obj:
	mkdir obj

lib/midilib.a: $(LIB_OBJS)
	ar rvs -o $@ $<

obj/%.o: sources/%.c
	$(CC) -c $(CC_FLAGS) $(DEFINES) -g $< -o $@ -I.

debug:
	echo $(LIB_OBJS)

clean:
	del *.exe
	rmdir obj
