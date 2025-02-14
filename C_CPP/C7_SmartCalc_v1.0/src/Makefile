CC=gcc
CFLAGS=-Wall -Werror -Wextra

TEST_DIRS=backend/test backend/test/suites
BACK_DIRS=backend/CCalc

BACK_SOURCES=$(wildcard $(BACK_DIRS)/*.c)
BACK_OBJS=$(patsubst %.c, %.o, $(BACK_SOURCES))

TEST_SOURCES=$(wildcard $(addsuffix /*.c, $(TEST_DIRS)))
TEST_OBJS=$(patsubst %.c, %.o, $(TEST_SOURCES))
TEST_RESULT=backend/unit_test

OBJS=$(TEST_OBJS) $(BACK_OBJS)

OS := $(shell uname)
ifeq ($(OS),Linux)
	CHECK_LIB = -lcheck -lsubunit -lm -lrt -lpthread -D_GNU_SOURSE
endif

ifeq ($(OS),Darwin)
	CHECK_LIB = -lcheck
endif

all: clean test

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

install:
	@mkdir ../build
	@cd front/SmartCalc && qmake && make && make clean && rm -rf .qmake.stash Makefile
	@mv front/SmartCalc/SmartCalc.app ../build/SmartCalc.app
	@cp -R ../build/SmartCalc.app ~/Desktop
	@echo "Install complite successful"

uninstall:
	@rm -rf ../build ~/Desktop/SmartCalc.app
	@echo "Uninstall complite successful"

dvi:
	@open ../GUIDE.md

dist:
	@mkdir ../dist
	@cp ../GUIDE.md ../dist && cp -R ../build/SmartCalc.app ../dist && cp -R ../dvi ../dist
	@cd ../dist && tar cvzf SmartCalc_v1_0.tgz *
	@cd ../dist && rm -rf SmartCalc.app GUIDE.md dvi

test: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $(TEST_RESULT) $(CHECK_LIB)
	./$(TEST_RESULT)

gcov_report: $(TEST_OBJS) $(BACK_SOURCES)
	$(CC) $(CFLAGS) --coverage $^ -o $(TEST_RESULT) $(CHECK_LIB)
	./$(TEST_RESULT)
	lcov -t "$(TEST_RESULT)" -o $@.info --no-external -c -d .
	genhtml -o report/ $@.info
	open report/index.html

$(BACK_OBJS): backend/CCalc/s21_calc.h

$(TEST_OBJS): backend/test/suites/test.h

clean: 
	rm -rf $(TEST_RESULT) $(OBJS) report backend/*.gc* gcov_report* ../build ../dist ~/Desktop/SmartCalc.app
