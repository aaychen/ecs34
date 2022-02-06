CC := gcc
CFLAGS := -Wall -Werror
programs := \
	add_three.x \
	get_three.x \
	grow_prod.x \
	snack_machine.x

all: $(programs)

%.x: %.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(programs)
