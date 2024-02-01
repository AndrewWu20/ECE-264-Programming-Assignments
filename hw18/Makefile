ASG_NICKNAME=HW18
BASE_NAME=huffman
EXECUTABLE=test_$(BASE_NAME)
EXECUTABLE_GCOV=test_$(BASE_NAME)_gcov
SRC_C=$(BASE_NAME).c priority_queue.c frequencies.c
SRC_H=$(BASE_NAME).h priority_queue.h frequencies.h miniunit.h log_macros.h
SUBMIT_FILES=$(SRC_C) $(TEST_C) $(SRC_H) Makefile
TEST_C=test_$(BASE_NAME).c
CFLAGS=-g -std=c11 -Wall -Wshadow -Wvla -Werror -pedantic
CFLAGS_GCOV=$(CFLAGS) -fprofile-arcs -ftest-coverage
CC=gcc
SHELL=/bin/bash

$(EXECUTABLE): $(SRC_C) $(TEST_C) $(SRC_H)
	$(CC) -o $(EXECUTABLE) $(SRC_C) $(TEST_C) $(CFLAGS) 

test: $(EXECUTABLE)
	./$(EXECUTABLE)

submit: $(SUBMIT_FILES)
	264submit $(ASG_NICKNAME) $(SUBMIT_FILES) test.txt recurring.txt huffman_test.txt

pretest: submit
	264test $(ASG_NICKNAME)

coverage: $(SRC_C) $(TEST_C) $(SRC_H)
	$(CC) -o $(EXECUTABLE_GCOV) $(SRC_C) $(TEST_C) $(CFLAGS_GCOV) $(CFLAGS)
	./$(EXECUTABLE_GCOV)
	gcov -f $(SRC_C)

clean: 
	rm -f $(EXECUTABLE) $(EXECUTABLE_GCOV) *.c.gcov *.gcda *.gcno



.PHONY: submit test pretest coverage clean
