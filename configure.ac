#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.63])
AC_INIT(cutils, 0.1, ladislav.laska@gmail.com)

# My stuff
AM_INIT_AUTOMAKE(cutils, 0.1)
AC_OUTPUT(Makefile src/Makefile)

# Init libtool to create .so libraries
AC_PROG_LIBTOOL

# for libtoolize
AC_CONFIG_MACRO_DIR([m4])

AM_MAINTAINER_MODE


# end of my stuff

#AC_CONFIG_SRCDIR([src/stack_test.c])
#AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC
AC_PROG_MAKE_SET

# Checks for libraries.

# Checks for header files.
#AC_CHECK_HEADERS([stdlib.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_REALLOC

# AC_CONFIG_FILES([Makefile])
AC_OUTPUT
