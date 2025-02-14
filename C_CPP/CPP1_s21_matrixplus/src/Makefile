CC=g++
FLAGS=-Wall -Werror -Wextra -std=c++17
TEST_SOURCE=$(wildcard **/*.cc)
SOURCE=s21_matrix_oop.cc
TEST_RESULT=test/unit_test
OBJECTS=$(SOURCE:.cc=.o)
RESULT=s21_matrix_oop.a

all: clean test

test: $(TEST_SOURCE) $(RESULT)
	$(CC) $(FLAGS) $^ -o $(TEST_RESULT) -lgtest
	./$(TEST_RESULT)

$(RESULT): $(OBJECTS)
	ar rc $(RESULT) $(OBJECTS)

.cc.o:
	$(CC) -c $< -o $@

clean:
	rm -rf $(RESULT) $(OBJECTS) $(TEST_RESULT)