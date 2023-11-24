// windows.h 会默认把<winsock.h> 放进来 但是 winsock.h 会和 winsock2.h 冲突导致无法使用ipv6
#define _WINSOCKAPI_

#include <string>
#include <vector>
#include <windows.h>
#include <assert.h>
#include <Shlobj.h>
#include <iostream>
#include <node_api.h>

#include "./include/json.hpp"
using json = nlohmann::json;
#include "./sock_lib/sock.hpp"

#include "./hmc_g.hpp"
#include "./hmc_string_util.hpp"
#include "./napi_value_util.hpp"

using namespace std;

#define $napi_get_cb_info(argsLen, args, fnName)                                                                           \
    if (napi_get_cb_info(env, info, &argsLen, args, NULL, NULL) != napi_ok)                                                \
    {                                                                                                                      \
        hmc_console::error("main", string("napi fn -> [").append(fnName).append("]").append(" $napi_get_cb_info error ")); \
        return NULL;                                                                                                       \
    }

// 导出一个其他cpp中的模块
#define DECLARE_NAPI_METHODRM(name, func)                         \
    {                                                             \
        name, 0, (napi_callback) & func, 0, 0, 0, napi_default, 0 \
    }

// 导出一个模块
#define DECLARE_NAPI_METHOD(name, func)         \
    {                                           \
        name, 0, func, 0, 0, 0, napi_default, 0 \
    }

// 导出一个文本内容
#define DECLARE_NAPI_VALUE(name, value)                                                    \
    {                                                                                      \
        name, 0, 0, 0, 0, hmc_napi_util::create_value::String(env, value), napi_default, 0 \
    }
