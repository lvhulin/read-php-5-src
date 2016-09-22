dnl $Id$
dnl config.m4 for extension ext_test

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

 PHP_ARG_WITH(ext_test, for ext_test support,
 Make sure that the comment is aligned:
 [  --with-ext_test             Include ext_test support])

dnl Otherwise use enable:

dnl PHP_ARG_ENABLE(ext_test, whether to enable ext_test support,
dnl Make sure that the comment is aligned:
dnl [  --enable-ext_test           Enable ext_test support])

if test "$PHP_EXT_TEST" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-ext_test -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/ext_test.h"  # you most likely want to change this
  dnl if test -r $PHP_EXT_TEST/$SEARCH_FOR; then # path given as parameter
  dnl   EXT_TEST_DIR=$PHP_EXT_TEST
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for ext_test files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       EXT_TEST_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$EXT_TEST_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the ext_test distribution])
  dnl fi

  dnl # --with-ext_test -> add include path
  dnl PHP_ADD_INCLUDE($EXT_TEST_DIR/include)

  dnl # --with-ext_test -> check for lib and symbol presence
  dnl LIBNAME=ext_test # you may want to change this
  dnl LIBSYMBOL=ext_test # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $EXT_TEST_DIR/$PHP_LIBDIR, EXT_TEST_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_EXT_TESTLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong ext_test lib version or lib not found])
  dnl ],[
  dnl   -L$EXT_TEST_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(EXT_TEST_SHARED_LIBADD)

  PHP_NEW_EXTENSION(ext_test, ext_test.c, $ext_shared)
fi
