AC_INIT([nesca4], [20240115])

echo ""
echo "RUNNING CONFIGURE NESCA4"
echo ""

AC_PREREQ([2.69])
AC_CONFIG_SRCDIR([source/nesca4.cc])
AC_CONFIG_HEADERS([config/config.h])

AC_PROG_CC
AC_PROG_CXX

LIB_CRYPTO_PATH="library/platform/linux/libcrypto.so.1.1"
LIB_DHDVR_PATH="library/platform/linux/libdhdvr.so"
LIB_DHNETSDK_PATH="library/platform/linux/libdhnetsdk.so"
LIB_HCCORE_PATH="library/platform/linux/libHCCore.so"
LIB_HCNETSDK_PATH="library/platform/linux/libhcnetsdk.so"
LIB_HPR_PATH="library/platform/linux/libhpr.so"
LIB_NCSOCK_PATH="ncsock/build/libncsock.a"
HCNETSDK_HEADER="library/HCNetSDK.h"
AVGLOBAL_HEADER="library/avglobal.h"
DHASSISTANT_HEADER="library/dhassistant.h"
DHNETSDK_HEADER="library/dhnetsdk.h"

AC_CHECK_FILE([$LIB_CRYPTO_PATH], [LIB_CRYPTO_FOUND=yes], [LIB_CRYPTO_FOUND=no])
AC_CHECK_FILE([$LIB_DHDVR_PATH], [LIB_DHDVR_FOUND=yes], [LIB_DHDVR_FOUND=no])
AC_CHECK_FILE([$LIB_DHNETSDK_PATH], [LIB_DHNETSDK_FOUND=yes], [LIB_DHNETSDK_FOUND=no])
AC_CHECK_FILE([$LIB_HCCORE_PATH], [LIB_HCCORE_FOUND=yes], [LIB_HCCORE_FOUND=no])
AC_CHECK_FILE([$LIB_HCNETSDK_PATH], [LIB_HCNETSDK_FOUND=yes], [LIB_HCNETSDK_FOUND=no])
AC_CHECK_FILE([$LIB_HPR_PATH], [LIB_HPR_FOUND=yes], [LIB_HPR_FOUND=no])
AC_CHECK_FILE([$LIB_NCSOCK_PATH], [LIB_NCSOCK_FOUND=yes], [LIB_NCSOCK_FOUND=no])

AC_CHECK_FILE([$HCNETSDK_HEADER], [HCNETSDK_HEADER_FOUND=yes], [HCNETSDK_HEADER_FOUND=no])
AC_CHECK_FILE([$AVGLOBAL_HEADER], [AVGLOBAL_HEADER_FOUND=yes], [AVGLOBAL_HEADER_FOUND=no])
AC_CHECK_FILE([$DHASSISTANT_HEADER], [DHASSISTANT_HEADER_FOUND=yes], [DHASSISTANT_HEADER_FOUND=no])
AC_CHECK_FILE([$DHNETSDK_HEADER], [DHNETSDK_HEADER_FOUND=yes], [DHNETSDK_HEADER_FOUND=no])

AC_ARG_ENABLE([hikvision], [AS_HELP_STRING([--disable-hikvision], [Disable Hikvision support])], [ENABLE_HIKVISION=$enableval], [ENABLE_HIKVISION=yes])
AC_ARG_ENABLE([dvr], [AS_HELP_STRING([--disable-dvr], [Disable DVR support])], [ENABLE_DVR=$enableval], [ENABLE_DVR=yes])

if test "$ENABLE_HIKVISION" = "yes" -a "$LIB_HCCORE_FOUND" = "yes" -a "$LIB_CRYPTO_FOUND" = "yes" -a "$LIB_HCNETSDK_FOUND" = "yes" -a "$HCNETSDK_HEADER_FOUND" = "yes" -a "$AVGLOBAL_HEADER_FOUND" = "yes"; then
    HAVE_HIKVISION=1
    AC_DEFINE([HAVE_HIKVISION], 1, [Define if all Hikvision libraries and headers are found])
    AC_SUBST([HAVE_HIKVISION])
    echo "macro (HAVE_HIKVISION) defined, and use hikvision lib"
fi

if test "$ENABLE_DVR" = "yes" -a "$LIB_HPR_FOUND" = "yes" -a "$LIB_DHDVR_FOUND" = "yes" -a "$LIB_DHNETSDK_FOUND" = "yes" -a "$DHASSISTANT_HEADER_FOUND" = "yes" -a "$DHNETSDK_HEADER_FOUND" = "yes"; then
    HAVE_DVR=1
    AC_DEFINE([HAVE_DVR], 1, [Define if all DVR libraries and headers are found])
    AC_SUBST([HAVE_DVR])
    echo "macro (HAVE_DVR) defined, and use dvr lib"
fi

if test "$LIB_NCSOCK_FOUND" = "no"; then
    echo "library (libncsock.a) not found, configuring ncsock"
    echo ""
    echo "RUNNING CONFIGURE NCSOCK/"
    echo ""
    (cd ncsock && ./configure && cd ..)
else
    echo "library (libncsock.a) found, no need to configure and make ncsock"
fi

AC_CONFIG_AUX_DIR([build])
AC_CONFIG_COMMANDS([default], [mkdir -p build])
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
