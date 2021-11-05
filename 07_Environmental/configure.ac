#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.71])
AC_INIT([rhasher], [1.0], [egor.sklyarov.ru@gmail.com])
AC_CONFIG_SRCDIR([rhasher.c])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC
AM_INIT_AUTOMAKE

# Checks for libraries.
AC_CHECK_LIB([librhash], [rhash_library_init], [
	AC_MSG_ERROR([Unable to find librhash])
])

# Checks for header files.
AC_CHECK_HEADER([rhash.h], [], [
	AC_MSG_ERROR([Unable to find rhash.h])
])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
