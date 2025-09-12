CFLAGS=-std=c17 -Wall -Wextra -Wpedantic -Wconversion -Wvla -Warith-conversion -Wno-builtin-declaration-mismatch -Wno-dangling-else
CPPFLAGS=
LDLIBS=
.PHONY: all clear clean
all: compile_flags.txt lsode

lsode: lsode.c makefile
	$(CC) $(CPPFLAGS) $(CFLAGS) $< -o $@ $(LDLIBS)

compile_flags.txt: makefile
	printf '%s\n' $(CFLAGS) $(CPPFLAGS) > ./compile_flags.txt

clear: clean
clean:
	$(RM) lsode
