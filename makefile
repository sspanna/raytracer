CC = cc
CFLAGS = -Wall -Wextra -MMD -MP -I.
LDFLAGS = -lm

LIB_SRCS = $(filter-out main.c, $(wildcard *.c))
LIB_OBJS = $(patsubst %.c, bin/%.o, $(LIB_SRCS))

bin/raytracer: bin/main.o $(LIB_OBJS) 
	$(CC) $(CFLAGS) -o bin/raytracer bin/main.o $(LIB_OBJS) $(LDFLAGS)

bin/%.o: %.c | bin
	$(CC) $(CFLAGS) -c $< -o $@

bin:
	mkdir -p bin

image.ppm: bin/raytracer
	./bin/raytracer > image.ppm

print: bin/raytracer
	./bin/raytracer

.PHONY: run clean test

run: image.ppm
	open image.ppm

TEST_SRCS = $(wildcard tests/*.c)
TEST_BINS = $(patsubst tests/%.c, bin/%, $(TEST_SRCS))

bin/%: tests/%.c $(LIB_OBJS) | bin 
	$(CC) $(CFLAGS) -o $@ $< $(LIB_OBJS) $(LDFLAGS)

-include $(wildcard bin/*.d)

test: $(TEST_BINS) 
	@for t in $(TEST_BINS); do \
		echo "Running $$t..."; \
		./$$t || exit 1; \
	done

clean:
	rm -rf bin image.ppm
