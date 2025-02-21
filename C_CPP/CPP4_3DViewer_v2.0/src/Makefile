CXX=g++
CFLAGS=-Wall -Werror -Wextra -std=c++17

# project core
BACK_DIR=3DViewr/back
TEST_DIR=utest
BACK_SOURCES=$(wildcard $(BACK_DIR)/**/*.cpp)
TEST_SOURCES=$(wildcard $(TEST_DIR)/*.cpp)
BACK_OBJ=$(BACK_SOURCES:.cpp=.o)
TEST_OBJ=$(TEST_SOURCES:.cpp=.o)
TEST_RESULT=test

# desktop dir
BUILD_DIR=build
GUI_DIR=3DViewr/gui/Viewer
#RM_FILES=$(filter-out %.app, $(wildcard $(BUILD_DIR)/*)) $(BUILD_DIR)/.qt

OS := $(shell uname)
ifeq ($(OS),Linux)
	OPEN= xdg-open report/index.html
	CHECK_LIB = -lgtest -lm -lrt -lpthread
endif

ifeq ($(OS),Darwin)
	OPEN= open report/index.html
	CHECK_LIB = -lgtest
endif

all: clean install test

install: 
	mkdir $(BUILD_DIR)
	cd $(GUI_DIR) && qmake6 && make
	cd $(GUI_DIR) && make clean && rm -rf Makefile .qmake.stash
	open build/Viewer.app

uninstall:
	rm -rf $(BUILD_DIR)

dvi:
	open 3DViewerDoc.md

dist:
	mkdir dist
	cp -R build/Viewer.app dist/.
	cp 3DViewerDoc.md dist/.
	cd dist && tar cvzf 3d_viewer.tgz Viewer.app 3DViewerDoc.md
	cd dist && rm -R Viewer.app 3DViewerDoc.md

test: $(TEST_OBJ) 3DViewer.a
	$(CXX) $(CFLAGS) $^ -o $(TEST_RESULT) $(CHECK_LIB)
	./$(TEST_RESULT)

3DViewer.a: $(BACK_OBJ)
	ar rc $@ $^

%.o: %.cpp
	$(CXX) -c $(CFLAGS) $^ -o $@

gcov_report: $(TEST_OBJ) $(BACK_SOURCES)
	$(CXX) $(CFLAGS) --coverage $^ -o $(TEST_RESULT) $(CHECK_LIB)
	./$(TEST_RESULT)
	lcov -c -d . -o $@.info \
		--exclude "/usr/local/include/c++/13/*" \
		--exclude "/usr/local/include/c++/13/bits/*" \
		--exclude "/usr/local/include/c++/13/x86_64-apple-darwin22/bits/*" \
		--exclude "*/ObjModel/ObjModel.h" \
		--ignore-errors unused
	genhtml -o report/ $@.info
	$(OPEN)
	rm -rf *.gcno *.gcda *.info

clang:
	cp ../materials/linters/.clang-format ./
	clang-format -n 3DViewr/back/CommandPocket/*.cpp 3DViewr/back/CommandPocket/*.h
	clang-format -i 3DViewr/back/CommandPocket/*.cpp 3DViewr/back/CommandPocket/*.h
	clang-format -n 3DViewr/back/Controller/*.cpp 3DViewr/back/Controller/*.h
	clang-format -i 3DViewr/back/Controller/*.cpp 3DViewr/back/Controller/*.h
	clang-format -n 3DViewr/back/MoveStrategy/*.cpp 3DViewr/back/MoveStrategy/*.h
	clang-format -i 3DViewr/back/MoveStrategy/*.cpp 3DViewr/back/MoveStrategy/*.h
	clang-format -n 3DViewr/back/ObjModel/*.cpp 3DViewr/back/ObjModel/*.h
	clang-format -i 3DViewr/back/ObjModel/*.cpp 3DViewr/back/ObjModel/*.h
	rm -rf .clang-format

clean: uninstall
	rm -rf $(BACK_OBJ) $(TEST_OBJ) $(TEST_RESULT) 3DViewer.a report test dist