CC=gcc
CFLAGS=-Wall -Werror -Wextra -std=c++17
MAIN_PROJECT=$(wildcard **/*.cc **/**/*.cc **/*.tpp **/*.h) # list of all the C source files in the project
SOURCES=$(filter-out %.tpp %.h, $(MAIN_PROJECT))
TEST_SOURCES=$(filter-out %.tpp %.h, $(MAIN_PROJECT))
CONTAINER=$(filter containers_tests/test.cc containers_tests/multiset%, $(MAIN_PROJECT))
HEADERS_AND_TPP=$(filter %.tpp %.h, $(MAIN_PROJECT))
MAIN=
TEST_RESULT=test
OBJECTS=$(SOURCES:.cc=.o)
TEST_OBJECTS=$(TEST_SOURCES:.cc=.o)
RESULT=
CURRENT_BRANCH=$(shell git rev-parse --abbrev-ref HEAD)

OS := $(shell uname)
ifeq ($(OS),Linux)
	OPEN= xdg-open report/index.html
	CHECK_LIB = -lgtest -lsubunit -lm -lrt -lpthread -lstdc++
endif

ifeq ($(OS),Darwin)
	OPEN= open report/index.html
	CHECK_LIB = -lgtest -lstdc++
endif

all: test

test: $(TEST_OBJECTS)
	$(CC) $(CFLAGS) $^ -o $(TEST_RESULT) $(CHECK_LIB)
	./$(TEST_RESULT)

$(RESULT): $(OBJECTS)
	ar rc $(RESULT) $(OBJECTS)

%.o: %.cc $(HEADERS_AND_TPP)
	$(CC) -c $(CFLAGS) $< -o $@

gcov_report: $(TEST_SOURCES)
	$(CC) $(CFLAGS) --coverage $^ $(CHECK_LIB) -o $@
	chmod +x *
	./$@ 
	lcov -t  "$@" --ignore-errors mismatch --ignore-errors inconsistent -o $@.info --no-external -c -d .
	genhtml -o report/ $@.info
	$(OPEN)

# you should use it on ubuntu
valgrind: test
	CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --read-var-info=yes ./$(TEST_RESULT)

clang:
	clang-format -style=Google -n $(MAIN_PROJECT)

apclang:
	clang-format -style=Google -i $(MAIN_PROJECT)

git: clean
	git add .
	git commit
	git push origin $(CURRENT_BRANCH)

clean:
	rm -rf $(RESULT) $(OBJECTS) $(TEST_OBJECTS) $(TEST_RESULT) gcov_report* *.gc* report/ *.o $(MAIN)