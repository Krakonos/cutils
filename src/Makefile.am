# what flags you want to pass to the C compiler & linker
AM_CFLAGS = --pedantic -Wall -std=c99
AM_LDFLAGS =

# this lists the binaries to produce, the (non-PHONY, binary) targets in
# the previous manual Makefile

# Create test cases
check_PROGRAMS = stack_test
stack_test_SOURCES = stack_test.c stack_test.h

TESTS = stack_test

stack_test_LDADD = libcutils.la

# Create library
cutils_includedir = $(includedir)/cutils
cutils_include_HEADERS = debug.h stack.h
lib_LTLIBRARIES = libcutils.la
libcutils_la_SOURCES = stack.c stack.h
