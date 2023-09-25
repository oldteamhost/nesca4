AC_INIT([nesca4],[20230925],[oldteam])
AM_INIT_AUTOMAKE
AC_CONFIG_SRCDIR([nesca4.cc])

AC_PROG_CXX
AC_PROG_CC

AC_CHECK_LIB([pthread], [pthread_create])
AC_CHECK_LIB([hcnetsdk], [some_function_from_hcnetsdk_library])
AC_ARG_VAR([LD_LIBRARY_PATH], [additional library search path])

if test "x$LD_LIBRARY_PATH" != "x"; then
  AC_MSG_NOTICE([Using LD_LIBRARY_PATH: $LD_LIBRARY_PATH])
  AC_SUBST([LD_LIBRARY_PATH])
fi

AC_CONFIG_FILES([Makefile])
AC_OUTPUT

