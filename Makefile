CC := clang
CFLAGS := -std=c11 -pedantic-errors -Wall -Iinclude src/*.c

examples-advanced:
	$(CC) $(CFLAGS) examples/advanced.c -o examples-advanced

examples-simple:
	$(CC) $(CFLAGS) examples/simple.c -o examples-simple

clean:
	rm -f examples-simple examples-advanced
	find -name '*.o' -delete

.PHONY: clean
