AC_INIT([nesca4], [20240115])
AC_PREREQ([2.69])
AC_CONFIG_SRCDIR([source/nesca4.cc])
AC_PROG_CXX
AC_PROG_CC

LIB_CRYPTO_PATH="library/platform/linux/libcrypto.so.1.1"
LIB_DHDVR_PATH="library/platform/linux/libdhdvr.so"
LIB_DHNETSDK_PATH="library/platform/linux/libdhnetsdk.so"
LIB_HCCORE_PATH="library/platform/linux/libHCCore.so"
LIB_HCNETSDK_PATH="library/platform/linux/libhcnetsdk.so"
LIB_HPR_PATH="library/platform/linux/libhpr.so"

AC_CHECK_FILE([$LIB_CRYPTO_PATH], [LIB_CRYPTO_FOUND=yes], [LIB_CRYPTO_FOUND=no])
AC_CHECK_FILE([$LIB_DHDVR_PATH], [LIB_DHDVR_FOUND=yes], [LIB_DHDVR_FOUND=no])
AC_CHECK_FILE([$LIB_DHNETSDK_PATH], [LIB_DHNETSDK_FOUND=yes], [LIB_DHNETSDK_FOUND=no])
AC_CHECK_FILE([$LIB_HCCORE_PATH], [LIB_HCCORE_FOUND=yes], [LIB_HCCORE_FOUND=no])
AC_CHECK_FILE([$LIB_HCNETSDK_PATH], [LIB_HCNETSDK_FOUND=yes], [LIB_HCNETSDK_FOUND=no])
AC_CHECK_FILE([$LIB_HPR_PATH], [LIB_HPR_FOUND=yes], [LIB_HPR_FOUND=no])

AC_CONFIG_AUX_DIR([build])
AC_CONFIG_COMMANDS([default], [mkdir -p build])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
