CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11
LDFLAGS = -lcheck -lpthread -lm -I /usr/local/include -L/usr/local/lib
CHECK:=$(shell pkg-config --cflags --libs check)
FS = -fsanitize=address -g

SOURCE = $(wildcard s21_*.c)
OBJECTS = $(patsubst %.c,%.o, ${SOURCE})

TARGET = s21_smart_calc.a
EXECUTABLE = s21_calculator

UNAME_S = $(shell uname)
DIR = smart_calc
TEST_SRC = unit_test/s21_smart_calc_test.c
ARCHIVE_DIR = s21_calc
COV_DIR = coverage

OPEN_CMD = open

ifeq ($(UNAME_S), Darwin)
	ADD_LIB = -lcheck $(shell pkg-config --cflags --libs check)
endif
ifeq ($(UNAME_S), Linux)
	ADD_LIB = -lcheck -lsubunit -pthread -lrt -lm
	OPEN_CMD = open_xdg
endif


# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

all: s21_smart_calc.a test gcov_report

s21_smart_calc.a: clean
	@$(CC) $(CFLAGS) -c $(LDFLAGS) $(SOURCE)
	@ar rc $(TARGET) $(OBJECTS)
	@ranlib $(TARGET)

test: clean $(TARGET)
	$(CC) $(CFLAGS) $(LDFLAGS) --coverage $(TEST_SRC) $(TARGET) -o $@ $(CHECK)
	./test


gcov_report: $(TARGET)
	$(CC) $(CFLAGS) $(LDFLAGS) --coverage $(SOURCE) $(TEST_SRC) $(TARGET) -o test $(CHECK)
	./test
	@lcov -t "smart-calc" -o tests.info -c -d .
	@genhtml -o $(COV_DIR) tests.info
	$(OPEN_CMD) $(COV_DIR)/index.html

install: 
	cd $(DIR) && cmake .
	cd $(DIR) && make
	mv $(DIR)/$(EXECUTABLE) ~/Desktop

uninstall:
	cd $(DIR) && rm -rf CMakeFiles $(EXECUTABLE)_autogen
	cd $(DIR) && rm -rf .cmake .qtc_clangd Testing
	cd $(DIR) && rm -f CMakeCache.txt CMakeCache.txt.prev *.cmake *.user
	rm ~/Desktop/$(EXECUTABLE)


dvi: dvi_clean
	makeinfo manual.texi --html
	open ./manual/index.html

dvi_clean:
	rm -rf manual

dist: install
	mkdir -p ./$(ARCHIVE_DIR)
	cp ~/Desktop/$(EXECUTABLE) ./$(ARCHIVE_DIR)
	tar -czf ~/Desktop/$(EXECUTABLE).tar.gz ./$(ARCHIVE_DIR)
	rm -rf $(ARCHIVE_DIR)


style:
	clang-format -style=Google -i *.c *.h
	clang-format -style=Google -i */*.cpp */*.h

valgrind: test
	CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./test

clean:
	@rm -f *.a *.o *.txt *.gch
	@rm -f *.gcno *.gcda *.info
	@rm -f $(EXECUTABLE) test *.out
	@rm -f ~/Desktop/differentiate_payments_table.txt
	@rm -rf $(ARCHIVE_DIR) *.dSYM
	@rm -rf $(COV_DIR) build*
