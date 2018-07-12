CC := clang
CWARNINGS := -Wall -Wextra -Wpedantic -Wunused -Wformat=2 -Winit-self \
	-Wmissing-include-dirs -Wstrict-overflow=4 -Wfloat-equal -Wwrite-strings \
	-Wconversion -Wundef -Wtrigraphs -Wunused-parameter -Wunknown-pragmas \
	-Wcast-align -Wswitch-enum -Waggregate-return -Wmissing-noreturn \
	-Wmissing-format-attribute -Wpacked -Wredundant-decls -Wunreachable-code \
	-Winline -Winvalid-pch -Wdisabled-optimization -Wbad-function-cast \
	-Wunused-function -Werror=implicit-function-declaration
CFLAGS := -std=c11 -pedantic-errors $(CWARNINGS) -Iinclude src/*.c

examples-advanced:
	$(CC) $(CFLAGS) examples/advanced.c -o examples-advanced

examples-simple:
	$(CC) $(CFLAGS) examples/simple.c -o examples-simple

clean:
	rm -f examples-simple examples-advanced
	find -name '*.o' -delete

.PHONY: clean
