CXX=g++
CFLAGS=-Wall -Werror -Wextra -std=c++17
# project core
BACKEND=brick_game
TEST=utest
BACK_SOURCES=$(wildcard $(BACKEND)/**/*.cc)
TEST_SOURCES=$(wildcard $(TEST)/*.cc)
BACK_OBJ=$(BACK_SOURCES:.cc=.o)
TEST_OBJ=$(TEST_SOURCES:.cc=.o)
TEST_RESULT=test
# desktop dir
BUILD_DIR=../build
SOURCE_DIR=gui/desktop/BrickGame_v2/.
RM_FILES=$(filter-out %.app, $(wildcard $(BUILD_DIR)/*)) $(BUILD_DIR)/.qt



OS := $(shell uname)
ifeq ($(OS),Linux)
	OPEN= xdg-open report/index.html
	CHECK_LIB = -lgtest -lm -lrt -lpthread
endif

ifeq ($(OS),Darwin)
	OPEN= open report/index.html
	CHECK_LIB = -lgtest
endif

all: clean test install

install:
	mkdir $(BUILD_DIR)
	cmake -B $(BUILD_DIR) $(SOURCE_DIR)
	cd $(BUILD_DIR) && make
	make rm-build
	open $(BUILD_DIR)/BrickGame_v2.app 

rm-build:
	rm -rf $(RM_FILES)

uninstall:
	rm -rf $(BUILD_DIR)

dvi:
	open ../dvi/readme.md

dist:
	@mkdir ../dist
	@cp -R ../build/BrickGame_v2.app ../dist && cp -R ../dvi ../dist
	@cd ../dist && tar cvzf BrickGame_v2.tgz *
	@cd ../dist && rm -rf BrickGame_v2.app dvi

test: $(TEST_OBJ) brickgame.a
	$(CXX) $(CFLAGS) $^ -o $(TEST_RESULT) $(CHECK_LIB)
	./$(TEST_RESULT)

gcov_report: $(TEST_OBJ) $(BACK_SOURCES)
	$(CXX) $(CFLAGS) --coverage $^ -o $(TEST_RESULT) $(CHECK_LIB)
	./$(TEST_RESULT)
	lcov -c -d . -o $@.info
	genhtml -o report/ $@.info
	open report/index.html
	rm -rf *.gcno *.gcda *.info

terminal: brickgame.a
	@cd gui/terminal && make

brickgame.a: $(BACK_OBJ)
	ar rc $@ $^

%.o: %.cc
	$(CXX) -c $(CFLAGS) $^ -o $@

clean: uninstall
	rm -rf $(BACK_OBJ) brickgame.a $(TEST_OBJ) Snake.txt Tetris.txt test
	rm -rf ../dist *.gcno *.gcda *.info report
	@cd gui/terminal && make clean