dnl $Id$
dnl config.m4 for extension dict_word

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

PHP_ARG_WITH(dict_word, for dict_word support,
Make sure that the comment is aligned:
[  --with-dict_word             Include dict_word support])

dnl Otherwise use enable:

dnl PHP_ARG_ENABLE(dict_word, whether to enable dict_word support,
dnl Make sure that the comment is aligned:
dnl [  --enable-dict_word           Enable dict_word support])

if test "$PHP_DICT_WORD" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-dict_word -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/dict_word.h"  # you most likely want to change this
  dnl if test -r $PHP_DICT_WORD/$SEARCH_FOR; then # path given as parameter
  dnl   DICT_WORD_DIR=$PHP_DICT_WORD
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for dict_word files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       DICT_WORD_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$DICT_WORD_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the dict_word distribution])
  dnl fi

  dnl # --with-dict_word -> add include path
  dnl PHP_ADD_INCLUDE($DICT_WORD_DIR/include)

  dnl # --with-dict_word -> check for lib and symbol presence
  dnl LIBNAME=dict_word # you may want to change this
  dnl LIBSYMBOL=dict_word # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $DICT_WORD_DIR/$PHP_LIBDIR, DICT_WORD_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_DICT_WORDLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong dict_word lib version or lib not found])
  dnl ],[
  dnl   -L$DICT_WORD_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(DICT_WORD_SHARED_LIBADD)

  PHP_NEW_EXTENSION(dict_word, dict_word.c, $ext_shared)
fi
