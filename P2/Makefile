CC := gcc
CFLAGS := -Wall -Werror
programs := \
	test_sum3.x \
	test_replaceIfHigher.x \
	test_performShiftCipher.x \
	test_strrstr.x \
	test_eachContains.x

all: $(programs)

%.x: %.c prog2.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(programs)
