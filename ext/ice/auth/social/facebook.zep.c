
#ifdef HAVE_CONFIG_H
#include "../../../ext_config.h"
#endif

#include <php.h>
#include "../../../php_ext.h"
#include "../../../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/object.h"
#include "kernel/memory.h"
#include "kernel/fcall.h"
#include "kernel/operators.h"
#include "kernel/concat.h"
#include "kernel/array.h"


/**
 * Facebook Auth social adapter.
 *
 * @package     Ice/Auth
 * @category    Adapter
 * @author      Ice Team
 * @copyright   (c) 2014-2015 Ice Team
 * @license     http://iceframework.org/license
 */
ZEPHIR_INIT_CLASS(Ice_Auth_Social_Facebook) {

	ZEPHIR_REGISTER_CLASS_EX(Ice\\Auth\\Social, Facebook, ice, auth_social_facebook, ice_auth_social_adapter_ce, ice_auth_social_facebook_method_entry, 0);

	return SUCCESS;

}

/**
 * Facebook adapter constructor.
 *
 * @param array config
 */
PHP_METHOD(Ice_Auth_Social_Facebook, __construct) {

	zval *_2;
	int ZEPHIR_LAST_CALL_STATUS;
	zephir_nts_static zephir_fcall_cache_entry *_1 = NULL;
	zval *config = NULL, *_0;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &config);

	if (!config) {
		ZEPHIR_INIT_VAR(config);
		array_init(config);
	}


	ZEPHIR_INIT_ZVAL_NREF(_0);
	ZVAL_STRING(_0, "facebook", 1);
	zephir_update_property_this(this_ptr, SL("_provider"), _0 TSRMLS_CC);
	ZEPHIR_CALL_PARENT(NULL, ice_auth_social_facebook_ce, this_ptr, "__construct", &_1, config);
	zephir_check_call_status();
	ZEPHIR_INIT_VAR(_2);
	array_init_size(_2, 8);
	add_assoc_stringl_ex(_2, SS("socialId"), SL("id"), 1);
	add_assoc_stringl_ex(_2, SS("email"), SL("email"), 1);
	add_assoc_stringl_ex(_2, SS("name"), SL("name"), 1);
	add_assoc_stringl_ex(_2, SS("sex"), SL("gender"), 1);
	add_assoc_stringl_ex(_2, SS("socialPage"), SL("link"), 1);
	add_assoc_stringl_ex(_2, SS("birthday"), SL("birthday"), 1);
	zephir_update_property_this(this_ptr, SL("_socialFieldsMap"), _2 TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

/**
 * Get url of user's avatar or null if it is not set.
 *
 * @return string|null
 */
PHP_METHOD(Ice_Auth_Social_Facebook, getImage) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *_0 = NULL, *_1 = NULL, *_2 = NULL;

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(_1);
	ZVAL_STRING(_1, "id", ZEPHIR_TEMP_PARAM_COPY);
	ZEPHIR_CALL_METHOD(&_0, this_ptr, "has", NULL, _1);
	zephir_check_temp_parameter(_1);
	zephir_check_call_status();
	if (zephir_is_true(_0)) {
		ZEPHIR_INIT_NVAR(_1);
		ZVAL_STRING(_1, "id", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_CALL_METHOD(&_2, this_ptr, "get", NULL, _1);
		zephir_check_temp_parameter(_1);
		zephir_check_call_status();
		ZEPHIR_CONCAT_SVS(return_value, "http://graph.facebook.com/", _2, "/picture?type=large");
		RETURN_MM();
	}
	RETURN_MM_NULL();

}

/**
 * Authenticate and return bool result of authentication.
 *
 * @return bool
 */
PHP_METHOD(Ice_Auth_Social_Facebook, authenticate) {

	zephir_nts_static zephir_fcall_cache_entry *_5 = NULL;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *params = NULL, *tokenInfo, *userInfo = NULL, *_GET, *_0 = NULL, *_1 = NULL, *_2 = NULL, *_3 = NULL, *_4;
	zend_bool result, _6;

	ZEPHIR_MM_GROW();

	result = 0;
	ZEPHIR_INIT_VAR(tokenInfo);
	ZVAL_NULL(tokenInfo);
	zephir_get_global(&_GET, SS("_GET") TSRMLS_CC);
	if (zephir_array_isset_string(_GET, SS("code"))) {
		ZEPHIR_INIT_VAR(params);
		array_init_size(params, 6);
		ZEPHIR_OBS_VAR(_0);
		zephir_read_property_this(&_0, this_ptr, SL("_clientId"), PH_NOISY_CC);
		zephir_array_update_string(&params, SL("client_id"), &_0, PH_COPY | PH_SEPARATE);
		ZEPHIR_OBS_NVAR(_0);
		zephir_read_property_this(&_0, this_ptr, SL("_redirectUri"), PH_NOISY_CC);
		zephir_array_update_string(&params, SL("redirect_uri"), &_0, PH_COPY | PH_SEPARATE);
		ZEPHIR_OBS_NVAR(_0);
		zephir_read_property_this(&_0, this_ptr, SL("_clientSecret"), PH_NOISY_CC);
		zephir_array_update_string(&params, SL("client_secret"), &_0, PH_COPY | PH_SEPARATE);
		ZEPHIR_OBS_NVAR(_0);
		zephir_array_fetch_string(&_0, _GET, SL("code"), PH_NOISY, "ice/auth/social/facebook.zep", 69 TSRMLS_CC);
		zephir_array_update_string(&params, SL("code"), &_0, PH_COPY | PH_SEPARATE);
		ZEPHIR_INIT_VAR(_2);
		ZVAL_LONG(_2, 0);
		ZEPHIR_INIT_VAR(_3);
		ZVAL_STRING(_3, "https://graph.facebook.com/oauth/access_token", ZEPHIR_TEMP_PARAM_COPY);
		ZEPHIR_INIT_VAR(_4);
		ZVAL_BOOL(_4, 0);
		ZEPHIR_CALL_METHOD(&_1, this_ptr, "call", NULL, _2, _3, params, _4);
		zephir_check_temp_parameter(_3);
		zephir_check_call_status();
		Z_SET_ISREF_P(tokenInfo);
		ZEPHIR_CALL_FUNCTION(NULL, "parse_str", &_5, _1, tokenInfo);
		Z_UNSET_ISREF_P(tokenInfo);
		zephir_check_call_status();
		_6 = zephir_fast_count_int(tokenInfo TSRMLS_CC) > 0;
		if (_6) {
			_6 = zephir_array_isset_string(tokenInfo, SS("access_token"));
		}
		if (_6) {
			ZEPHIR_INIT_NVAR(params);
			array_init_size(params, 2);
			ZEPHIR_OBS_NVAR(_0);
			zephir_array_fetch_string(&_0, tokenInfo, SL("access_token"), PH_NOISY, "ice/auth/social/facebook.zep", 74 TSRMLS_CC);
			zephir_array_update_string(&params, SL("access_token"), &_0, PH_COPY | PH_SEPARATE);
			ZEPHIR_INIT_NVAR(_2);
			ZVAL_LONG(_2, 0);
			ZEPHIR_INIT_NVAR(_3);
			ZVAL_STRING(_3, "https://graph.facebook.com/me", ZEPHIR_TEMP_PARAM_COPY);
			ZEPHIR_CALL_METHOD(&userInfo, this_ptr, "call", NULL, _2, _3, params);
			zephir_check_temp_parameter(_3);
			zephir_check_call_status();
			if (zephir_array_isset_string(userInfo, SS("id"))) {
				zephir_update_property_this(this_ptr, SL("_userInfo"), userInfo TSRMLS_CC);
				result = 1;
			}
		}
	}
	RETURN_MM_BOOL(result);

}

/**
 * Prepare params for authentication url.
 *
 * @return array
 */
PHP_METHOD(Ice_Auth_Social_Facebook, prepareAuthParams) {

	zval *_1 = NULL;
	zval *_0;

	ZEPHIR_MM_GROW();

	array_init_size(return_value, 3);
	add_assoc_stringl_ex(return_value, SS("auth_url"), SL("https://www.facebook.com/dialog/oauth"), 1);
	ZEPHIR_INIT_VAR(_0);
	array_init_size(_0, 6);
	ZEPHIR_OBS_VAR(_1);
	zephir_read_property_this(&_1, this_ptr, SL("_clientId"), PH_NOISY_CC);
	zephir_array_update_string(&_0, SL("client_id"), &_1, PH_COPY | PH_SEPARATE);
	ZEPHIR_OBS_NVAR(_1);
	zephir_read_property_this(&_1, this_ptr, SL("_redirectUri"), PH_NOISY_CC);
	zephir_array_update_string(&_0, SL("redirect_uri"), &_1, PH_COPY | PH_SEPARATE);
	add_assoc_stringl_ex(_0, SS("response_type"), SL("code"), 1);
	add_assoc_stringl_ex(_0, SS("scope"), SL("email,user_birthday"), 1);
	zephir_array_update_string(&return_value, SL("auth_params"), &_0, PH_COPY | PH_SEPARATE);
	RETURN_MM();

}
