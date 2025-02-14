CC=gcc
CFLAGS=-Wall -Wextra -Werror -std=c11

TEST_SOURCES=$(wildcard **/*.c **/**/*.c **/**/**/*.c) # list of all the C source files in the project
SOURCES=$(filter-out test/%, $(TEST_SOURCES)) # need to add another files in progress
TEST_RESULT=test/test
OBJECTS=$(SOURCES:.c=.o)
TEST_OBJECTS=$(TEST_SOURCES:.c=.o)
RESULT=s21_matrix.a

OS := $(shell uname)
ifeq ($(OS),Linux)
	CHECK_LIB = -lcheck -lsubunit -lm -lrt -lpthread -D_GNU_SOURSE
endif

ifeq ($(OS),Darwin)
	CHECK_LIB = -lcheck
endif

all: $(RESULT)

test: $(RESULT) $(TEST_OBJECTS)
	# clear
	$(CC) $(CFLAGS) $^ -o $(TEST_RESULT) $(CHECK_LIB)
	./$(TEST_RESULT)

$(RESULT): $(OBJECTS)
	ar rc $(RESULT) $(OBJECTS)

.c.o:
	$(CC) -c $(CFLAGS) $< -o $@

gcov_report: $(TEST_SOURCES) $(SOURCES)
	$(CC) $(CFLAGS) --coverage $^ $(CHECK_LIB) -o $@
	chmod +x *
	./$@
	lcov -t "$@" -o $@.info --no-external -c -d .
	genhtml -o report/ $@.info
	open report/index.html

clang:
	clang-format -style=Google -n $(SOURCES) $(TEST_SOURCES)

clean:
	rm -rf $(RESULT) $(OBJECTS) $(TEST_OBJECTS) $(TEST_RESULT) gcov_report* *.gc* report/ *.o