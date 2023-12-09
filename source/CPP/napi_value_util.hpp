#pragma once

// 防止重复导入
#ifndef MODE_INTERNAL_INCLUDE_HMC_NAPI_VALUE_UTIL_HPP
#define MODE_INTERNAL_INCLUDE_HMC_NAPI_VALUE_UTIL_HPP

#include <windows.h>
#include <assert.h>
#include <any>
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <node_api.h>
#include <iostream>
#include <set>

#include "./hmc_string_util.hpp"

using namespace std;

// 导出一个 static 函数
#define EXPORT_NAPI_STATIC_FN(func)              \
    {                                            \
        #func, 0, func, 0, 0, 0, napi_default, 0 \
    }
// 导出一个 static 函数
#define EXPORT_NAPI_STATIC_PAIR(name, func)     \
    {                                           \
        name, 0, func, 0, 0, 0, napi_default, 0 \
    }

// 导出一个 其他文件的 函数
#define EXPORT_NAPI_REMOTE_FN(func)                                \
    {                                                              \
        #func, 0, (napi_callback) & func, 0, 0, 0, napi_default, 0 \
    }

// 导出一个 其他文件的 函数 并设置名称
#define EXPORT_NAPI_REMOTE_FNPAIR(name, func)                     \
    {                                                             \
        name, 0, (napi_callback) & func, 0, 0, 0, napi_default, 0 \
    }

typedef enum
{
    // ES6 types (corresponds to typeof)
    js_undefined = napi_undefined,
    js_null = napi_null,
    js_boolean = napi_boolean,
    js_number = napi_number,
    js_string = napi_string,
    js_symbol = napi_symbol,
    js_object = napi_object,
    js_function = napi_function,
    js_external = napi_external,
    js_bigint = napi_bigint,
    js_array = 95270,
    js_date = 95271,
    js_error = 95272,
    js_buffer = 95273,
    js_point = 95277,
    // js_array_string = 95279,
    // js_array_number = 95281,
    // js_array_boolean = 95282,
    // js_array_bigint = 95283,
    js_promise = 95285,
    js_promise_function = 95286,
    js_rect = 95288,
    js_unknown = 955666,
    // js_array_any = 95290,
} js_valuetype;

namespace hmc_napi_get_value
{
    /**
     * @brief 数字转int
     *
     * @param env
     * @param nodeValue
     * @return int
     */
    extern int number_int(napi_env env, napi_value nodeValue, int defaultValue = 0);
    /**
     * @brief 数字转int64
     *
     * @param env
     * @param nodeValue
     * @return int64_t
     */
    extern int64_t number_int64(napi_env env, napi_value nodeValue, int64_t defaultValue = 0);
    /**
     * @brief 数字转64位浮点
     *
     * @param env
     * @param nodeValue
     * @return double
     */
    extern double number_double(napi_env env, napi_value nodeValue, int defaultValue = 0.0);
    /**
     * @brief bigint转long
     *
     * @param env
     * @param nodeValue
     * @return long long
     */
    extern long long bigint_longlong(napi_env env, napi_value nodeValue, long long defaultValue = 0);
    /**
     * @brief 获取buff
     *
     * @param env
     * @param nodeValue
     * @param buffer
     */
    template <typename T>
    extern void buffer_vector(napi_env env, napi_value nodeValue, vector<T> &buffer);
    /**
     * @brief 获取为布尔值
     *
     * @param env
     * @param nodeValue
     * @return true
     * @return false
     */
    extern bool boolean_bool(napi_env env, napi_value nodeValue, bool defaultValue = false);
    /**
     * @brief 获取为utf8标准的文本
     *
     * @param env
     * @param nodeValue
     * @return string
     */
    extern string string_utf8(napi_env env, napi_value nodeValue, string defaultValue = string(""));
    /**
     * @brief 获取为utf8标准的文本
     *
     * @param env
     * @param nodeValue
     * @return string
     */
    extern wstring string_utf16(napi_env env, napi_value nodeValue, wstring defaultValue = wstring(L""));
    /**
     * @brief 获取为窄(A)文本
     *
     * @param env
     * @param nodeValue
     * @return string
     */
    extern string string_ansi(napi_env env, napi_value nodeValue, string defaultValue = string(""));
    /**
     * @brief 获取为宽(W)文本
     *
     * @param env
     * @param nodeValue
     * @return wstring
     */
    extern wstring string_wide(napi_env env, napi_value nodeValue, wstring defaultValue = wstring(L""));
    /**
     * @brief 获取文本数组
     *
     * @param env
     * @param nodeValue
     * @return vector<string>
     */
    extern vector<string> array_string_utf8(napi_env env, napi_value nodeValue);
    /**
     * @brief 获取文本数组
     *
     * @param env
     * @param nodeValue
     * @return vector<string>
     */
    extern vector<wstring> array_string_utf16(napi_env env, napi_value nodeValue);
    /**
     * @brief 获取数字数组
     *
     * @param env
     * @param nodeValue
     * @return vector<int>
     */
    extern vector<int> array_int(napi_env env, napi_value nodeValue);
    /**
     * @brief 获取数字数组
     *
     * @param env
     * @param nodeValue
     * @return vector<int>
     */
    extern vector<int64_t> array_int64(napi_env env, napi_value nodeValue);
    /**
     * @brief 获取数字数组
     *
     * @param env
     * @param nodeValue
     * @return vector<int>
     */
    extern vector<double> array_double(napi_env env, napi_value nodeValue);
    /**
     * @brief 将文本的显示状态转为CPP的显示状态代码
     *
     * @param env
     * @param nodeValue
     * @return UINT
     */
    extern UINT showType_UINT(napi_env env, napi_value nodeValue);
    /**
     * @brief 转 DWORD
     *
     * @param env
     * @param nodeValue
     * @return DWORD
     */
    extern DWORD number_DWORD(napi_env env, napi_value nodeValue, int defaultValue = 0);
    /**
     * @brief 转窗口句柄
     *
     * @param env
     * @param nodeValue
     * @return HWND
     */
    extern HWND number_HWND(napi_env env, napi_value nodeValue, HWND defaultValue = NULL);
    /**
     * @brief 获取buff内容
     *
     * @param env
     * @param nodeValue
     * @return vector<unsigned char>
     */
    extern vector<unsigned char> buffer_vector(napi_env env, napi_value nodeValue);
    /**
     * @brief 传入缓冲是utf16的文本
     *
     * @param env
     * @param nodeValue
     * @return wstring
     */
    extern wstring buffer_utf16_strW(napi_env env, napi_value nodeValue);
    /**
     * @brief 传入缓冲是ansi的文本（winapi转换过得）
     *
     * @param env
     * @param nodeValue
     * @return string
     */
    extern string buffer_ansi_strA(napi_env env, napi_value nodeValue);
    /**
     * @brief 传入缓冲是utf8的文本
     *
     * @param env
     * @param nodeValue
     * @return string
     */
    extern string buffer_utf8_strU8(napi_env env, napi_value nodeValue);
    /**
     * @brief 缓冲区转为c标准接口的文本 Buffer.from('文本', 'utf16le')
     * @param env
     * @param nodeValue
     * @return const wchar_t* c标准接口的  const char *
     */
    extern const wchar_t *buffer_utf16_clpStrW(napi_env env, napi_value nodeValue);
    /**
     * @brief 缓冲区转为c标准接口的文本 Buffer.from('文本', 'utf16le')
     * @param env
     * @param nodeValue
     * @return const char* c标准接口的  const char *
     */
    extern const char *buffer_utf8_clpStrU8(napi_env env, napi_value nodeValue);
    /**
     * @brief 缓冲区转为c标准接口的文本 Buffer.from('文本', 'utf16le')
     * @param env
     * @param nodeValue
     * @return const char* c标准接口的  const char *
     */
    extern const char *buffer_ansi_clpStrA(napi_env env, napi_value nodeValue);
    /**
     * @brief 获取一个对象并将其转换为 POINT
     *
     * @param env
     * @param objectValue
     * @return POINT
     */
    extern POINT point(napi_env env, napi_value objectValue);
    /**
     * @brief 使用键获取napi_value 的值
     *
     * @param env
     * @param objectValue
     * @param key
     * @return napi_value
     */
    extern napi_value get_object_value(napi_env env, napi_value objectValue, string key);
    /**
     * @brief 使用键取值为int
     *
     * @param env
     * @param objectValue
     * @param key
     * @param defaultValue
     * @return int
     */
    extern int get_object_value_int(napi_env env, napi_value objectValue, string key, int defaultValue = 0);
    /**
     * @brief 使用键取值为int64
     *
     * @param env
     * @param objectValue
     * @param key
     * @param defaultValue
     * @return int64_t
     */
    extern int64_t get_object_value_int64(napi_env env, napi_value objectValue, string key, int64_t defaultValue = 0);
    /**
     * @brief 使用键取值为double
     *
     * @param env
     * @param objectValue
     * @param key
     * @param defaultValue
     * @return double
     */
    extern double get_object_value_double(napi_env env, napi_value objectValue, string key, double defaultValue = 0);
    /**
     * @brief 使用键取值为bool
     *
     * @param env
     * @param objectValue
     * @param key
     * @param defaultValue
     * @return true
     * @return false
     */
    extern bool get_object_value_bool(napi_env env, napi_value objectValue, string key, bool defaultValue = false);
    /**
     * @brief 使用键取值为 utf16
     *
     * @param env
     * @param objectValue
     * @param key
     * @param defaultValue
     * @return wstring
     */
    extern wstring get_object_value_utf16(napi_env env, napi_value objectValue, string key, wstring defaultValue = wstring(L""));
    /**
     * @brief 使用键取值为utf8
     *
     * @param env
     * @param objectValue
     * @param key
     * @param defaultValue
     * @return string
     */
    extern string get_object_value_utf8(napi_env env, napi_value objectValue, string key, string defaultValue = string(""));
    /**
     * @brief 使用键取值为ansi
     *
     * @param env
     * @param objectValue
     * @param key
     * @param defaultValue
     * @return string
     */
    extern string get_object_value_ansi(napi_env env, napi_value objectValue, string key, string defaultValue = string(""));
    /**
     * @brief 使用键取值为 RECT
     *
     * @param env
     * @param objectValue
     * @return RECT
     */
    extern RECT rect(napi_env env, napi_value objectValue);
}

namespace hmc_napi_type
{

    /**
     * @brief 获取napi数据的类型文本
     *
     * @param valuetype
     * @return string
     */
    extern string typeName(js_valuetype valuetype);
    /**
     * @brief 获取napi数据的类型文本
     *
     * @param valuetype
     * @return string
     */
    extern string typeName(napi_valuetype valuetype);
    /**
     * @brief 获取napi类型变量名称（人话）
     *
     * @param env
     * @param valuetype
     * @return string
     */
    extern string typeName(napi_env env, napi_value valuetype);

    /**
     * @brief 获取node类型的枚举值
     *
     * @param env
     * @param valuetype
     * @return string
     */
    extern js_valuetype getType(napi_env env, napi_value valuetype);

    /**
     * @brief 对比两个变量类型是否相等
     *
     * @param valuetype
     * @param valuetype2
     * @return BOOL
     */
    extern bool diff(napi_valuetype valuetype, napi_valuetype valuetype2);
    /**
     * @brief 判断值与多种类型是否一致
     *
     * @param valuetype
     * @param valuetype2
     * @param first
     * @param args
     * @return true
     * @return false
     */
    template <typename... Args>
    extern bool diff(napi_valuetype valuetype, const napi_valuetype &first, const Args &...args);
    /**
     * @brief 判断值与多种类型是否一致
     *
     * @tparam Args
     * @param env
     * @param nodeValue
     * @param first
     * @param args
     * @return int
     */
    template <typename... Args>
    extern bool diff(napi_env env, napi_value nodeValue, const napi_valuetype &first, const Args &...args);

    /**
     * @brief 判断值与类型是否一致
     *
     * @param env
     * @param jsValue
     * @param valuetype
     * @return true
     * @return false
     */
    extern bool diff(napi_env env, napi_value jsValue, napi_valuetype valuetype);
    /**
     * @brief 判断两个值的类型是否一致
     *
     * @param env
     * @param jsValue
     * @param jsValue2
     * @return true
     * @return false
     */
    extern bool diff(napi_env env, napi_value jsValue, napi_value jsValue2);
    /**
     * @brief 判断传入的值数量是否符合当前的要求
     *
     * @param env
     * @param nodeValue
     * @param argLength
     * @param index
     * @return true
     * @return false
     */
    extern bool argsSize(napi_env env, size_t argLength, int minLength, int maxLength);
    /**
     * @brief 判断传入的值数量是否符合当前的要求
     *
     * @param env
     * @param nodeValue
     * @param argLength
     * @param index
     * @return true
     * @return false
     */
    extern bool argsSize(napi_env env, size_t argLength, int minLength);
    /**
     * @brief 是buff
     *
     * @param env
     * @param value
     * @return true
     * @return false
     */
    extern bool isBuffer(napi_env env, napi_value value);
    /**
     * @brief 是文本
     *
     * @param env
     * @param value
     * @return true
     * @return false
     */
    extern bool isString(napi_env env, napi_value value);
    /**
     * @brief 是数字
     *
     * @param env
     * @param value
     * @return true
     * @return false
     */
    extern bool isNumber(napi_env env, napi_value value);
    /**
     * @brief 是布尔
     *
     * @param env
     * @param value
     * @return true
     * @return false
     */
    extern bool isBoolean(napi_env env, napi_value value);
    /**
     * @brief 是 Bigint
     *
     * @param env
     * @param value
     * @return true
     * @return false
     */
    extern bool isBigint(napi_env env, napi_value value);
    /**
     * @brief 是函数
     *
     * @param env
     * @param value
     * @return true
     * @return false
     */
    extern bool isFunction(napi_env env, napi_value value);
    /**
     * @brief 是对象
     *
     * @param env
     * @param value
     * @return true
     * @return false
     */
    extern bool isObject(napi_env env, napi_value value);
    /**
     * @brief 是 Undefined
     *
     * @param env
     * @param value
     * @return true
     * @return false
     */
    extern bool isUndefined(napi_env env, napi_value value);
    /**
     * @brief 是null
     *
     * @param env
     * @param value
     * @return true
     * @return false
     */
    extern bool isNull(napi_env env, napi_value value);
    /**
     * @brief 在 JavaScript 中显示为普通对象
     *
     * @param env
     * @param value
     * @return true
     * @return false
     */
    extern bool isExternal(napi_env env, napi_value value);
    /**
     * @brief 判断是否是 obj 并且包含了 此key
     *
     * @param env
     * @param objectValue
     * @param key
     * @return true
     * @return false
     */
    extern bool isObjectkeyExists(napi_env env, napi_value objectValue, string key);
    /**
     * @brief 是数组
     *
     * @param env
     * @param value
     * @return true
     * @return false
     */
    extern bool isArray(napi_env env, napi_value value);
    /**
     * @brief 是Date
     *
     * @param env
     * @param value
     * @return true
     * @return false
     */
    extern bool isDate(napi_env env, napi_value value);
    /**
     * @brief 是 Error
     *
     * @param env
     * @param value
     * @return true
     * @return false
     */
    extern bool isError(napi_env env, napi_value value);
    /**
     * @brief 是 C Point
     *
     * @param env
     * @param value
     * @return true
     * @return false
     */
    bool isPoint(napi_env env, napi_value value);
    /**
     * @brief 是 Promise
     *
     * @param env
     * @param value
     * @return true
     * @return false
     */
    bool isPromise(napi_env env, napi_value value);
    /**
     * @brief 是 C Rect
     *
     * @param env
     * @param value
     * @return true
     * @return false
     */
    bool isRect(napi_env env, napi_value value);
}

namespace hmc_napi_create_value
{

    // 创建一个布尔型
    napi_value Boolean(napi_env env, bool value = false);
    // 创建一个布尔型
    napi_value Boolean(napi_env env, int value = 0);

    // 返回一个 string utf8 string
    napi_value String(napi_env env, string value);

    // 返回一个 string utf8 string
    napi_value StringA(napi_env env, string value);
    // 返回一个 string utf16 string
    napi_value String(napi_env env, wstring value);
    napi_value String(napi_env env, wchar_t *value);
    napi_value String(napi_env env, char *value);
    napi_value String(napi_env env);

    /**
     * @brief 返回一个 number到js
     *
     * @param number
     * @return napi_value
     */
    napi_value Number(napi_env env, int number = 0);
    /**
     * @brief 返回一个 number到js
     *
     * @param number
     * @return napi_value
     */
    napi_value Number(napi_env env, int64_t number = 0);
    /**
     * @brief 返回一个 number到js
     *
     * @param number
     * @return napi_value
     */
    napi_value Number(napi_env env, double number = 0.0);
    /**
     * @brief 返回一个 number到js
     *
     * @param number
     * @return napi_value
     */
    napi_value Number(napi_env env, HWND number);
    napi_value Number(napi_env env, unsigned long number);
    /**
     * @brief 返回一个 number到js
     *
     * @param bigint
     * @return napi_value
     */
    napi_value Bigint(napi_env env, long bigint = 0);
    /**
     * @brief 返回一个 number到js
     *
     * @param bigint
     * @return napi_value
     */
    napi_value Bigint(napi_env env, long long bigint = 0);
    /**
     * @brief 返回一个 Buffer到js(返回的是空值 napi 不支持)
     *
     * @param env
     * @param data
     * @param size
     * @return napi_value
     */
    napi_value Buffer(napi_env env, vector<unsigned char> &buffer);
    napi_value Buffer(napi_env env, void *data, size_t size);

    /**
     * @brief 返回一个 null
     *
     * @param env
     * @param data
     * @param size
     * @return napi_value
     */
    napi_value Null(napi_env env);
    /**
     * @brief RECT (位置信息转为Object)
     *
     * @param env
     * @param rect
     * @return napi_value
     */
    napi_value Rect(napi_env env, RECT rect);
    napi_value Point(napi_env env, POINT point);

    /**
     * @brief 返回一个 undefined
     *
     * @param env
     * @param data
     * @param size
     * @return napi_value
     */
    napi_value Undefined(napi_env env);
    /**
     * @brief 自识别类型
     *
     * @param env
     * @param anyValue
     * @return napi_value
     */
    napi_value New(napi_env env, any anyValue);

    napi_value New(napi_env env);

    namespace Array
    {
        /**
         * @brief 支持多种类型的数组
         *
         * @param env
         * @param wstringVector
         * @return napi_value
         */
        napi_value New(napi_env env, vector<napi_value> wstringVector);
        napi_value New(napi_env env, vector<any> wstringVector);
        /**
         * @brief 创建一个全是文本的数组
         *
         * @param env
         * @param stringVector
         * @return napi_value
         */
        napi_value String(napi_env env, vector<string> stringVector);
        napi_value String(napi_env env, vector<wstring> wstringVector);
        /**
         * @brief 创建一个全是数字的数组
         *
         * @param env
         * @param intVector
         * @return napi_value
         */
        napi_value Number(napi_env env, vector<int> intVector);

        /**
         * @brief 创建一个全是数字的数组
         *
         * @param env
         * @param intVector
         * @return napi_value
         */
        napi_value Bigint(napi_env env, vector<int> intVector);
        /**
         * @brief 创建一个全是数字的数组
         *
         * @param env
         * @param intVector
         * @return napi_value
         */
        napi_value Boolean(napi_env env, vector<bool> boolVector);
    }

    namespace Object
    {
        /**
         * @brief 创建一个全是文本的 键值对对象
         *
         * @param env
         * @param mapObject
         * @return napi_value
         */
        napi_value Object(napi_env env, map<string, string> mapObject);
        /**
         * @brief 创建一个全是文本的 键值对对象
         *
         * @param env
         * @param mapObject
         * @return napi_value
         */
        napi_value Object(napi_env env, map<wstring, wstring> mapObject);

        /**
         * @brief 创建一个全是int的 键值对对象
         *
         * @param env
         * @param mapObject
         * @return napi_value
         */
        napi_value Object(napi_env env, map<string, int> mapObject);
        /**
         * @brief 创建一个全是napi_value的 键值对对象
         *
         * @param env
         * @param mapObject
         * @return napi_value
         */
        napi_value Object(napi_env env, map<string, napi_value> mapObject);
        /**
         * @brief 创建一个任意js支持的类型
         *
         * @param env
         * @param mapObject
         * @return napi_value
         */
        napi_value Object(napi_env env, map<string, any> mapObject);
    }

}

class hmcNodeValue
{
private:
    std::vector<napi_value> args;
    napi_env env;

public:
    hmcNodeValue(napi_env env, napi_callback_info info);
    ~hmcNodeValue();
    /**
     * @brief 获取数量
     *
     * @return size_t
     */
    size_t size();
    /**
     * @brief 获取指定索引为 int
     *
     * @param index
     * @param defaultValue
     * @return int
     */
    int getInt(size_t index, int defaultValue = 0);
    /**
     * @brief 获取指定索引为 int 64
     *
     * @param index
     * @param defaultValue
     * @return int64_t
     */
    int64_t getInt64(size_t index, int64_t defaultValue = 0);
    /**
     * @brief 获取指定索引为 String Ansi
     *
     * @param index
     * @param defaultValue
     * @return string
     */
    string getStringAnsi(size_t index, string defaultValue = string(""));
    /**
     * @brief 获取指定索引为  String Wide
     *
     * @param index
     * @param defaultValue
     * @return wstring
     */
    wstring getStringWide(size_t index, wstring defaultValue = wstring(L""));
    /**
     * @brief 获取指定索引为  String Utf8
     *
     * @param index
     * @param defaultValue
     * @return string
     */
    string getStringUtf8(size_t index, string defaultValue = string(""));
    /**
     * @brief 获取指定索引为 布尔
     *
     * @param index
     * @param defaultValue
     * @return true
     * @return false
     */
    bool getBool(size_t index, bool defaultValue = false);
    /**
     * @brief 获取指定索引为  Buffer
     *
     * @param index
     * @param defaultValue
     * @return vector<unsigned char>
     */
    vector<unsigned char> getBuffer(size_t index, vector<unsigned char> defaultValue = {});
    /**
     * @brief 获取指定索引为  Double
     *
     * @param index
     * @param defaultValue
     * @return double
     */
    double getDouble(size_t index, double defaultValue = 0.0);
    /**
     * @brief 获取指定索引为 DWORD
     *
     * @param index
     * @param defaultValue
     * @return DWORD
     */
    DWORD getDword(size_t index, DWORD defaultValue = 0);
    /**
     * @brief 获取指定索引为 HWND
     *
     * @param index
     * @param defaultValue
     * @return HWND
     */
    HWND getHwnd(size_t index, HWND defaultValue = NULL);
    /**
     * @brief 获取指定索引为 String 数组
     *
     * @param index
     * @param defaultValue
     * @return vector<string>
     */
    vector<string> getArrayString(size_t index, vector<string> defaultValue = {});
    /**
     * @brief 获取指定索引为 int 数组
     *
     * @param index
     * @param defaultValue
     * @return vector<int>
     */
    vector<int> getArrayInt(size_t index, vector<int> defaultValue = {});
    /**
     * @brief 获取指定索引为 utf16 数组
     *
     * @param index
     * @param defaultValue
     * @return vector<wstring>
     */
    vector<wstring> getArrayWstring(size_t index, vector<wstring> defaultValue = {});
    /**
     * @brief 判断值是否存在
     *
     * @param index
     * @return true
     * @return false
     */
    bool exists(size_t index);
    /**
     * @brief 判断值长度是否符合
     *
     * @param min_length 最少有多少个
     * @param max_length 最多有多少个
     * @return true
     * @return false
     */
    bool argsSize(size_t min_length, size_t max_length, bool throw_error = false);
    /**
     * @brief 判断当前传入的值是否是期待值
     *
     * @param eq_type
     * @return true
     * @return false
     */
    bool eq(size_t index, js_valuetype type, bool throw_error = false);
    /**
     * @brief 判断当前传入的值是否是期待值
     *
     * @param eq_type
     * @return true
     * @return false
     */
    bool eq(vector<std::tuple<size_t, js_valuetype>> eq_type, bool throw_error = false);

    /**
     * @brief 判断当前传入的值是否是期待值
     *
     * @param eq_type
     * @return true
     * @return false
     */
    bool eq(size_t index, napi_valuetype type, bool throw_error = false);
    /**
     * @brief 判断当前传入的值是否是期待值
     *
     * @param eq_type
     * @return true
     * @return false
     */
    bool eq(vector<std::tuple<size_t, napi_valuetype>> eq_type, bool throw_error = false);
    /**
     * @brief 判断当前传入的值是否是期待值
     *
     * @param eq_type
     * @return true
     * @return false
     */
    bool eq(size_t index,vector<js_valuetype> type_list = {}, bool throw_error = false);
    /**
     * @brief 判断当前传入的值是否是期待值
     *
     * @param eq_type
     * @return true
     * @return false
     */
    bool eq(size_t index, vector<napi_valuetype> type_list = {}, bool throw_error = false);
    /**
     * @brief 获取类型列表
     * 
     * @return vector<js_valuetype> 
     */
    vector<js_valuetype> getType();
    /**
     * @brief 获取指定索引的 类型
     *
     * @param index
     * @return js_valuetype
     */
    js_valuetype getType(size_t index);
};

// namespace hmcPromise{
//     size_t __$hmcPromise_PromiseSessionID;
//     std::set<size_t> __$hmcPromise_PromiseTaskEndStatusList;
//     std::map<size_t, Promise> __$hmcPromise_PromiseTaskList;

//     class Promise
//     {
//     private:
    
//     public:
//         Promise(){
            
//         }
//         ~Promise();
//         napi_value format(size_t PromiseID)
//         {
//             return NULL;
//         }
//         any data(){
            
//         }
//     };


// }


#endif // MODE_INTERNAL_INCLUDE_HMC_NAPI_VALUE_UTIL_HPP