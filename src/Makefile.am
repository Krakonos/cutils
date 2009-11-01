# what flags you want to pass to the C compiler & linker
AM_CFLAGS = --pedantic -Wall -std=c99
AM_LDFLAGS =

# this lists the binaries to produce, the (non-PHONY, binary) targets in
# the previous manual Makefile

# Create test cases
check_PROGRAMS = stack_test \
				queue_test
TESTS = stack_test queue_test

# Stack test definition
stack_test_SOURCES = stack_test.c
stack_test_LDADD = libcutils.la

# Queue test definition
queue_test_SOURCES = queue_test.c
queue_test_LDADD = libcutils.la



# Create library
cutils_includedir = $(includedir)/cutils
cutils_include_HEADERS = debug.h \
						stack.h \
						queue.h
lib_LTLIBRARIES = libcutils.la
libcutils_la_SOURCES = stack.c stack.h \
						queue.c queue.h
