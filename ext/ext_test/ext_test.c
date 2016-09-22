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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_ext_test.h"

/* If you declare any globals in php_ext_test.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(ext_test)
*/

/* True global resources - no need for thread safety here */
static int le_ext_test;




typedef struct Dict{
  char *key;
  char *content;
  struct Dict *next;
} Dict;



int open_dict(Dict **, const char *);
int search_dict(Dict *, int, char *, char *content);
void free_dict(Dict *, int size);



/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("ext_test.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_ext_test_globals, ext_test_globals)
    STD_PHP_INI_ENTRY("ext_test.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_ext_test_globals, ext_test_globals)
PHP_INI_END()
*/
/* }}} */

/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_ext_test_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(dict_aa)
{
	char *str = NULL;

	int str_len = 0;
	
	char not[40] = "Not found.";

	char *result = NULL;


	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &str, &str_len) == FAILURE) {
		return;
	}

	char content[2048];
	result = "aaaaaa";
	/*
	const char *filename = "/data/www/wwwroot/clang/dict/dict.txt";
	Dict *dict = NULL;

	int size = open_dict(&dict, filename);

	char *key = NULL;
	char content[2048];
	
	memset(key, 0, sizeof(key));
	memset(content, 0, sizeof(content));

	key = str;
	
	if (search_dict(dict, size, key, content)) {
		result = "aaaaaaaaaa";
	} else {
		result = "bbbbbbbbbbb";
	}
	

	free_dict(dict, size);
	*/
	
	RETURN_STRINGL(result, strlen(content), 0);


	/*
	char *arg = NULL;
	int arg_len, len;
	char *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	len = spprintf(&strg, 0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "ext_test", arg);
	RETURN_STRINGL(strg, len, 0);
	*/
}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and 
   unfold functions in source code. See the corresponding marks just before 
   function definition, where the functions purpose is also documented. Please 
   follow this convention for the convenience of others editing your code.
*/


/* {{{ php_ext_test_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_ext_test_init_globals(zend_ext_test_globals *ext_test_globals)
{
	ext_test_globals->global_value = 0;
	ext_test_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(ext_test)
{
	/* If you have INI entries, uncomment these lines 
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(ext_test)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(ext_test)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(ext_test)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(ext_test)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "ext_test support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

/* {{{ ext_test_functions[]
 *
 * Every user visible function must have an entry in ext_test_functions[].
 */
const zend_function_entry ext_test_functions[] = {
	PHP_FE(dict_aa,	NULL)		/* For testing, remove later. */
	PHP_FE_END	/* Must be the last line in ext_test_functions[] */
};
/* }}} */

/* {{{ ext_test_module_entry
 */
zend_module_entry ext_test_module_entry = {
	STANDARD_MODULE_HEADER,
	"ext_test",
	ext_test_functions,
	PHP_MINIT(ext_test),
	PHP_MSHUTDOWN(ext_test),
	PHP_RINIT(ext_test),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(ext_test),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(ext_test),
	PHP_EXT_TEST_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

int open_dict(Dict **dict, const char *filename)
{
	FILE *fp = fopen(filename, "r");
	if (fp == NULL) {
		return 0; 
	}
	
	*dict = (Dict *)emalloc(sizeof(Dict));
	memset(*dict, 0, sizeof(Dict));
	Dict *pD = *dict;
	
	int i = 0;
	char buf[2048];
	size_t len = 0;
	
	fseek(fp, 0L, SEEK_SET);
	while (!feof(fp)) {
		memset(buf, 0, sizeof(buf));
		fgets(buf, sizeof(buf), fp);
		len = strlen(buf);
		if (len > 0) {
			pD->key = (char *)emalloc(len);
			memset(pD->key, 0, len);
			strcpy(pD->key, &buf[1]);	
		}
		
		memset(buf, 0, sizeof(buf));
		fgets(buf, sizeof(buf), fp);
		len = strlen(buf);
		if (len > 0) {
			pD->content = (char *)emalloc(len);
			memset(pD->content, 0, len);
			strcpy(pD->content, &buf[6]);	
		}
		
		pD->next = (Dict *)emalloc(sizeof(Dict));
		memset(pD->next, 0, sizeof(Dict));
		pD = pD->next;
		i++;
	}
	fclose(fp);	
	return i;
}

int search_dict(Dict *dict, int size, char *key, char *content)
{
	Dict *pD = dict;
	while (pD) {
		if ((pD->key) && (pD->content)) {
			if (strncmp(pD->key, key, strlen(key)) == 0) {
				strcpy(content, pD->content);
				return 1;
			}	
		}
		pD = pD->next;
	}
	return 0;
}

void free_dict(Dict *dict, int size)
{
	Dict *p = dict;
	while (p) {
		if (p->key) {
			efree(p->key);
		}
		if (p->content) {
			efree(p->key);
		}
		Dict *temp = p->next;
		efree(p);
		p = temp;
	}	
}

#ifdef COMPILE_DL_EXT_TEST
ZEND_GET_MODULE(ext_test)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
