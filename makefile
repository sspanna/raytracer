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

# --- Profiling build ---
PROFILE_CFLAGS = -Wall -Wextra -O2 -g -MMD -MP -I.
PROFILE_LIB_OBJS = $(patsubst %.c, bin/profile/%.o, $(LIB_SRCS))

bin/profile/raytracer: bin/profile/main.o $(PROFILE_LIB_OBJS)
	$(CC) $(PROFILE_CFLAGS) -o bin/profile/raytracer bin/profile/main.o $(PROFILE_LIB_OBJS)

bin/profile/%.o: %.c | bin/profile
	$(CC) $(PROFILE_CFLAGS) -c $< -o $@

bin/profile:
	mkdir -p bin/profile

perf: bin/profile/raytracer
	perf record -g -o perf.data ./bin/profile/raytracer > /tmp/profile.ppm
	perf report -i perf.data

callgrind: bin/profile/raytracer
	valgrind --tool=callgrind --callgrind-out-file=bin/profile/callgrind.out ./bin/profile/raytracer > /tmp/profile.ppm
	callgrind_annotate bin/profile/callgrind.out | less

image.ppm: bin/raytracer
	./bin/raytracer > image.ppm

print: bin/raytracer
	./bin/raytracer

.PHONY: run clean test

run: image.ppm
	open image.ppm

profile: bin/profile/raytracer

# --- Debug build ---
DEBUG_CFLAGS = -Wall -Wextra -O0 -g3 -MMD -MP -I.
DEBUG_LIB_OBJS = $(patsubst %.c, bin/debug/%.o, $(LIB_SRCS))

bin/debug/raytracer: bin/debug/main.o $(DEBUG_LIB_OBJS)
	$(CC) $(DEBUG_CFLAGS) -o bin/debug/raytracer bin/debug/main.o $(DEBUG_LIB_OBJS) $(LDFLAGS)

bin/debug/%.o: %.c | bin/debug
	$(CC) $(DEBUG_CFLAGS) -c $< -o $@

bin/debug:
	mkdir -p bin/debug

debug: bin/debug/raytracer

gdb: bin/debug/raytracer
	gdb ./bin/debug/raytracer
TEST_SRCS = $(wildcard tests/*.c)
TEST_BINS = $(patsubst tests/%.c, bin/%, $(TEST_SRCS))

bin/%: tests/%.c $(LIB_OBJS) | bin 
	$(CC) $(CFLAGS) -o $@ $< $(LIB_OBJS) $(LDFLAGS)

-include $(wildcard bin/*.d)
-include $(wildcard bin/profile/*.d)
-include $(wildcard bin/debug/*.d)

test: $(TEST_BINS) 
	@for t in $(TEST_BINS); do \
		echo "Running $$t..."; \
		./$$t || exit 1; \
	done

clean:
	rm -rf bin image.ppm
