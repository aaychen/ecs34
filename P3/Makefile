CC := gcc
CFLAGS := -Wall -Werror
programs := \
	test_parseForHighest.x \
	test_getAllHigherThan.x \
	test_strtok_c.x \
	test_student.x

all: $(programs)

%.x: %.c prog3.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(programs)
