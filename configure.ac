#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.63])
AC_INIT(cutils, 0.1, ladislav.laska@gmail.com)
AC_CONFIG_HEADERS([config.h])
AC_DEFINE([_XOPEN_SOURCE], [500], [Enable POSIX.1, 2, XPG4 and UNIX 98 extension.])

# My stuff
AM_INIT_AUTOMAKE(cutils, 0.1)
AC_OUTPUT(Makefile src/Makefile)

# Init libtool to create .so libraries
AC_PROG_LIBTOOL

# for libtoolize
AC_CONFIG_MACRO_DIR([m4])

AM_MAINTAINER_MODE

# --enable-debug feature
############################
AC_ARG_ENABLE(debug, 
	[
		AS_HELP_STRING([--enable-debug], 
		[enable debug mode (default=disabled)])
	],
	[enable_debug=yes], [enable_debug=no])

AS_IF([test "$enable_debug" == "yes"],
	[
		AC_DEFINE([DEBUG], [1], [Enable debugging features])
	])

# end of my stuff

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
