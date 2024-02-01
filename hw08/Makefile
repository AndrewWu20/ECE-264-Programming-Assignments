ASG_NICKNAME=HW55
BASE_NAME=count_words
EXECUTABLE=test_(BASE_NAME)
EXECUTABLE_GCOV=test_(BASE_NAME)_gcov
SRC_C=$(BASE_NAME).c
SRC_H=$(BASE_NAME).h log_macros.h miniunit.h
SUBMIT_FILES=TEST_C log_macros.h miniunit.h Makefile
TEST_C=test_$(SRC_C)
CFLAGS=-g -std=c11 -Wall -Wshadow -Wvla -Werror -pedantic
CFLAGS_GCOV=$(CFLAGS) -fprofile-arcs -ftest-coverage
CC=gcc
SHELL=/bin/bash

test_count_words: $(SRC_C) $(TEST_C) $(SRC_H)
	$(CC) -o $(EXECUTABLE) $(SRC_C) $(TEST_C) $(CFLAGS) 

$(EXECUTABLE): EXECUTABLE
	264CC $(EXECUTABLE)

test: $(EXECUTABLE)
	./$(EXECUTABLE)

submit:
	264submit $(SUBMIT_FILES)

pretest: submit
	264test $(ASG_NICKNAME)

coverage: test
	264coverage $(EXECUTABLE_GCOV)

clean: coverage pretest submit test $(EXECUTABLE)
	264delete all



.PHONY: submit test pretest
