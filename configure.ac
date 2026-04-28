#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.72])
AC_INIT([sqlite3ext_geomag], [1.0], [andrear1979@hotmail.com])
AC_CONFIG_SRCDIR([config.h.in])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE
LT_INIT([shared win32-dll])

# Checks for programs.
AC_PROG_CC
AC_PROG_CPP
AC_PROG_GREP
AC_PROG_MKDIR_P

AC_CHECK_PROG([HAVESQLITE3SHELL], [sqlite3], [sqlite3])
AM_CONDITIONAL([HAVESQLITE3SHELLFORTESTS], [test x$HAVESQLITE3SHELL = xsqlite3])

# Checks for header files.
AC_CHECK_HEADER([string.h],     [], [AC_MSG_ERROR([string.h is required.])])
AC_CHECK_HEADER([stdlib.h],	[], [AC_MSG_ERROR([stdlib.h is required.])])
AC_CHECK_HEADER([sqlite3.h],	[], [AC_MSG_ERROR([sqlite3.h is required.])])
AC_CHECK_HEADER([sqlite3ext.h], [], [AC_MSG_ERROR([sqlite3ext.h is required.])])
AC_CHECK_HEADER([geomag.h],     [], [AC_MSG_ERROR([geomag.h is required.])])

# Libraries configuration
AC_CHECK_LIB(
	[geomag-embedded], 
	[get_field_components],
	[LIBS="-Wl,-Bstatic,-lgeomag-embedded $LIBS"],
	[AC_MSG_ERROR([libgeomag-embedded static library is a mandatory requirement.])]
)

# Checks for libraries.
AC_CHECK_LIB([sqlite3], [sqlite3_value_text], [], [AC_MSG_ERROR([SQLite library is a mandatory requirement.])])

AC_CONFIG_FILES([Makefile src/Makefile])

AC_OUTPUT
