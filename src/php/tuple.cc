/*
  +----------------------------------------------------------------------+
  | Phpy                                                                 |
  +----------------------------------------------------------------------+
  | This source file is subject to version 2.0 of the Apache license,    |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.apache.org/licenses/LICENSE-2.0.html                      |
  | If you did not receive a copy of the Apache2.0 license and are unable|
  | to obtain it through the world-wide-web, please send a note to       |
  | license@swoole.com so we can mail you a copy immediately.            |
  +----------------------------------------------------------------------+
  | Author: Tianfeng Han  <rango@swoole.com>                             |
  | Copyright: 上海识沃网络科技有限公司                                       |
  +----------------------------------------------------------------------+
 */

#include "phpy.h"

#include "zend_interfaces.h"

BEGIN_EXTERN_C()
#include "stubs/phpy_tuple_arginfo.h"
END_EXTERN_C()

zend_class_entry *PyTuple_ce;

using phpy::php::arg_1;

int php_class_tuple_init(INIT_FUNC_ARGS) {
    zend_class_entry ce;
    INIT_CLASS_ENTRY(ce, "PyTuple", class_PyTuple_methods);
    PyTuple_ce = zend_register_internal_class_ex(&ce, phpy_sequence_get_ce());
    PyTuple_ce->ce_flags |= ZEND_ACC_FINAL | ZEND_ACC_NO_DYNAMIC_PROPERTIES | ZEND_ACC_NOT_SERIALIZABLE;
    return SUCCESS;
}

namespace phpy {
namespace php {
void new_tuple(zval *zv, PyObject *list) {
    new_object(zv, list, PyTuple_ce);
}
}  // namespace php
}  // namespace phpy

static ssize_t get_key(INTERNAL_FUNCTION_PARAMETERS) {
    ssize_t k;

    ZEND_PARSE_PARAMETERS_START(1, 1)
    Z_PARAM_LONG(k)
    ZEND_PARSE_PARAMETERS_END_EX(return 0);

    return k;
}

ZEND_METHOD(PyTuple, __construct) {
    auto pyobj = arg_1(INTERNAL_FUNCTION_PARAM_PASSTHRU, phpy_object_get_ce());
    phpy_object_ctor(ZEND_THIS, PySequence_Tuple(pyobj));
}

ZEND_METHOD(PyTuple, offsetGet) {
    auto pk = get_key(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    auto object = phpy_object_get_handle(ZEND_THIS);
    if (PyTuple_Size(object) <= pk) {
        zend_throw_error(NULL, "PyTuple: index[%ld] out of range", pk);
        return;
    }
    auto value = PyTuple_GetItem(object, pk);
    if (value != NULL) {
        py2php(value, return_value);
    }
}

ZEND_METHOD(PyTuple, offsetSet) {
    zend_throw_error(NULL, "PyTuple: does not support offsetSet");
}

ZEND_METHOD(PyTuple, offsetUnset) {
    zend_throw_error(NULL, "PyTuple: does not support offsetUnset");
}

ZEND_METHOD(PyTuple, offsetExists) {
    auto pk = get_key(INTERNAL_FUNCTION_PARAM_PASSTHRU);
    auto object = phpy_object_get_handle(ZEND_THIS);
    RETVAL_BOOL(PyTuple_Size(object) > pk);
}
