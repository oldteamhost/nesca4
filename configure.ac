AC_INIT([nesca4], [20240926])
AC_PREREQ([2.69])

dnl configure

echo ""
echo "RUNNING CONFIGURE NESCA4"
echo ""

LIBNCSNET_PATH="libncsnet/libncsnet.a"
CFLAGS="-Wall -g"
OCFLAGS="-O3"

AC_SUBST(CFLAGS)
AC_SUBST(OCFLAGS)

AC_CONFIG_SRCDIR([nesca4.cc])
AC_CONFIG_HEADERS([config.h])
AC_PROG_CC
AC_PROG_CXX


dnl check libncsnet

AC_CHECK_FILE([$LIBNCSNET_PATH], [LIBNCSNET_FOUND=no=yes], [LIBNCSNET_FOUND=no])
if test "$LIBNCSNET_FOUND" = "no"; then
  echo "library (libncsnet.a) not found, configuring ncsnet"
  echo ""
  echo "RUNNING CONFIGURE LIBNCSNET/"
  echo ""
  (cd libncsnet && ./configure && cd ..)
else
  echo "library (libncsnet.a) found, no need to configure and make ncsnet"
fi

AC_CONFIG_FILES([Makefile])
AC_OUTPUT


