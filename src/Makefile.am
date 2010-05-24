# what flags you want to pass to the C compiler & linker
AM_CFLAGS = --pedantic -Wall -std=c99
AM_LDFLAGS =

# this lists the binaries to produce, the (non-PHONY, binary) targets in
# the previous manual Makefile

# Create test cases
check_PROGRAMS = stack_test \
				queue_test \
				htable_test \
				fenwick_test
TESTS = stack_test queue_test htable_test fenwick_test

# Stack test definition
stack_test_SOURCES = tests/stack_test.c
stack_test_LDADD = libcutils.la

# Queue test definition
queue_test_SOURCES = tests/queue_test.c
queue_test_LDADD = libcutils.la

# Hashtable test definition
htable_test_SOURCES = tests/htable_test.c
htable_test_LDADD = libcutils.la

# Fenwick tree test definition
fenwick_test_SOURCES = tests/fenwick_test.c
fenwick_test_LDADD = libcutils.la


# Create library
cutils_includedir = $(includedir)/cutils
cutils_include_HEADERS = debug.h \
						stack.h \
						queue.h \
						htable.h \
						permutations/permutations.h \
						trees/fenwick.h
lib_LTLIBRARIES = libcutils.la
libcutils_la_SOURCES =  macro.h \
						stack.c stack.h \
						queue.c queue.h \
						strhash.c strhash.h \
						htable.c htable.h \
						permutations/permutations.c permutations/permutations.h \
						trees/fenwick.c trees/fenwick.h
