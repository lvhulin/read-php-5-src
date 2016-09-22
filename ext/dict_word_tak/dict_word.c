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
#include "php_dict_word.h"

/* If you declare any globals in php_dict_word.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(dict_word)
*/

/* True global resources - no need for thread safety here */
static int le_dict_word;

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("dict_word.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_dict_word_globals, dict_word_globals)
    STD_PHP_INI_ENTRY("dict_word.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_dict_word_globals, dict_word_globals)
PHP_INI_END()
*/
/* }}} */

/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_dict_word_compiled(string arg)
   Return a string to confirm that the module is compiled in */


PHP_FUNCTION(dict_init)
{
	
	char *str = NULL;

	int str_len = 0;
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &str, &str_len) == FAILURE) {
		return;
	}

	char *filename = str;

	Dict *dict = NULL;


	if (open_dict(&dict, filename) == 0){
		RETURN_NULL();
	}

	/* 返回资源类型 */
	ZEND_REGISTER_RESOURCE(return_value, dict, le_dict_word);
}


PHP_FUNCTION(dict_search)
{
	Dict *dict = NULL;

	zval *dict_resource = NULL;

	int keyword_len = 0;
	
	char not_found[40] = "Not found.";

	char *keyword = NULL;

	int size = 0;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rs", 
				&dict_resource, &keyword, &keyword_len) == FAILURE) {
		RETURN_FALSE;
	}

    if (keyword_len > KEYWORD_MAX_LEN || keyword_len < 1) {
        php_error_docref(NULL TSRMLS_CC, E_WARNING, "keyword should has [1, %d] bytes", KEYWORD_MAX_LEN);
        RETURN_FALSE;
    }

    /* 检查资源是否合法 */
	ZEND_FETCH_RESOURCE(dict, Dict *, &dict_resource, -1, PHP_DICT_WORD_RES_NAME, le_dict_word);


	char content[2048];

	memset(content, 0, sizeof(content));


	if (search_dict(dict, keyword, content) == 0) {
		strcpy(content, not_found);
	}
	
	RETURN_STRINGL(content, strlen(content), 0);

}


PHP_FUNCTION(dict_close)
{
	FILE *fp;
	zval *file_resource;
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r",&file_resource) == FAILURE ) {
		RETURN_NULL();
	}

	ZEND_FETCH_RESOURCE(fp, FILE*, &file_resource, -1, PHP_DICT_WORD_RES_NAME, le_dict_word);

	/* Force the resource into self-destruct mode */
	zend_hash_index_del(&EG(regular_list),Z_RESVAL_P(file_resource));
	RETURN_TRUE;
}




/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and 
   unfold functions in source code. See the corresponding marks just before 
   function definition, where the functions purpose is also documented. Please 
   follow this convention for the convenience of others editing your code.
*/


/* {{{ php_dict_word_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_dict_word_init_globals(zend_dict_word_globals *dict_word_globals)
{
	dict_word_globals->global_value = 0;
	dict_word_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(dict_word_open_one)
{
	/* If you have INI entries, uncomment these lines 
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(dict_word_stop_two)
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
PHP_RINIT_FUNCTION(dict_word_open_two)
{
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(dict_word_stop_one)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(dict_word)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "dict_word support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

/* {{{ dict_word_functions[]
 *
 * Every user visible function must have an entry in dict_word_functions[].
 */
const zend_function_entry dict_word_functions[] = {
	PHP_FE(dict_init,	NULL)		/* For testing, remove later. */
	PHP_FE(dict_search,	NULL)
	PHP_FE(dict_close,	NULL)
	PHP_FE_END	/* Must be the last line in dict_word_functions[] */
};
/* }}} */

/* {{{ dict_word_module_entry
 */
zend_module_entry dict_word_module_entry = {
	STANDARD_MODULE_HEADER,
	"dict_word",
	dict_word_functions,
	PHP_MINIT(dict_word_open_one),
	PHP_MSHUTDOWN(dict_word_stop_two),
	PHP_RINIT(dict_word_open_two),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(dict_word_stop_one),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(dict_word),
	PHP_DICT_WORD_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_DICT_WORD
ZEND_GET_MODULE(dict_word)
#endif


static int open_dict(Dict **dict, char *filename)
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

static int search_dict(Dict *dict, char *key, char *content)
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

void free_dict(Dict *dict)
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

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
