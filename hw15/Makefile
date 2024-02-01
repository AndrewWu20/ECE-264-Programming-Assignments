ASG_NICKNAME=HW15
BASE_NAME=json
EXECUTABLE=test_$(BASE_NAME)
EXECUTABLE_GCOV=test_$(BASE_NAME)_gcov
SRC_C=$(BASE_NAME).c
SRC_H=$(BASE_NAME).h log_macros.h miniunit.h
SUBMIT_FILES=$(SRC_C) $(TEST_C) $(SRC_H) log_macros.h miniunit.h Makefile
TEST_C=test_$(SRC_C)
CFLAGS=-g -std=c11 -Wall -Wshadow -Wvla -Werror -pedantic
CFLAGS_GCOV=$(CFLAGS) -fprofile-arcs -ftest-coverage
CC=gcc
SHELL=/bin/bash

$(EXECUTABLE): $(SRC_C) $(TEST_C) $(SRC_H)
	$(CC) -o $(EXECUTABLE) $(SRC_C) $(TEST_C) $(CFLAGS) 

test: $(EXECUTABLE)
	./$(EXECUTABLE)

submit: $(SUBMIT_FILES)
	264submit $(ASG_NICKNAME) $(SUBMIT_FILES)

pretest: submit
	264test $(ASG_NICKNAME)

coverage: test
	$(CC) -o $(EXECUTABLE_GCOV) $(SRC_C) $(TEST_C) $(CFLAGS_GCOV)
	./$(EXECUTABLE_GCOV)
	gcov -f $(SRC_C)

clean: 
	rm -f $(EXECUTABLE) $(EXECUTABLE_GCOV) *.c.gcov *.gcda *.gcno



.PHONY: submit test pretest coverage clean
