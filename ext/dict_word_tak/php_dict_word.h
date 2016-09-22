/*
  +----------------------------------------------------------------------+
  | PHP Version 5                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2016 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifndef PHP_DICT_WORD_H
#define PHP_DICT_WORD_H

extern zend_module_entry dict_word_module_entry;
#define phpext_dict_word_ptr &dict_word_module_entry

#define PHP_DICT_WORD_VERSION "0.1.0" /* Replace with version number for your extension */

#ifdef PHP_WIN32
#	define PHP_DICT_WORD_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_DICT_WORD_API __attribute__ ((visibility("default")))
#else
#	define PHP_DICT_WORD_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

/* 
  	Declare any global variables you may need between the BEGIN
	and END macros here:     

ZEND_BEGIN_MODULE_GLOBALS(dict_word)
	long  global_value;
	char *global_string;
ZEND_END_MODULE_GLOBALS(dict_word)
*/

/* In every utility function you add that needs to use variables 
   in php_dict_word_globals, call TSRMLS_FETCH(); after declaring other 
   variables used by that function, or better yet, pass in TSRMLS_CC
   after the last function argument and declare your utility function
   with TSRMLS_DC after the last declared argument.  Always refer to
   the globals in your function as DICT_WORD_G(variable).  You are 
   encouraged to rename these macros something shorter, see
   examples in any other php module directory.
*/

#ifdef ZTS
#define DICT_WORD_G(v) TSRMG(dict_word_globals_id, zend_dict_word_globals *, v)
#else
#define DICT_WORD_G(v) (dict_word_globals.v)
#endif


#define KEYWORD_MAX_LEN 255
#define PHP_DICT_WORD_RES_NAME "dict word"

   
typedef struct _dict{
  char *key;
  char *content;
  struct Dict *next;
} Dict;



static int open_dict(Dict **, char *);
static int search_dict(Dict *, char *, char *content);
void free_dict(Dict *);

#endif	/* PHP_DICT_WORD_H */


/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
