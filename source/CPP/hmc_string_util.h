#pragma once

// 防止重复导入
#ifndef MODE_INTERNAL_INCLUDE_HMC_STRING_UTIL_HPP
#define MODE_INTERNAL_INCLUDE_HMC_STRING_UTIL_HPP

#include <string>
#include <vector>
#include <windows.h>
#include <crtdbg.h> // For _ASSERTE()
#include <iomanip>
#include <map>
#include <sstream>
#include <tuple>
#include <limits>    // For numeric_limits
#include <stdexcept> // For overflow_error

using namespace std;

namespace hmc_string_util
{
    // ----------------------------------------------------------------
    // W2U8
    // utf 16 to utf8 encoding
    // utf16(win 标准) 转 utf8 字符(win 标准)
    // ----------------------------------------------------------------
    extern string utf16_to_utf8(const wstring utf16);

    // ----------------------------------------------------------------
    // U82W
    // utf 8 to utf16 encoding
    // utf8(win 标准) 转 utf16 字符(win 标准)
    // ----------------------------------------------------------------

    extern wstring utf8_to_utf16(const string utf8);

    // ----------------------------------------------------------------
    // W2A
    // utf 16 to Local CP_ACP ( Ansi [A] ) encoding
    // utf16(win 标准[W]) 转 winapi A字符
    // ----------------------------------------------------------------
    extern string utf16_to_ansi(const wstring utf16);

    // ----------------------------------------------------------------
    // A2W
    // Local CP_ACP ( Ansi [A] ) to utf16 encoding
    // winapi A字符 转 utf16(win 标准[W])
    // ----------------------------------------------------------------
    extern wstring ansi_to_utf16(const string ansi);

    // ----------------------------------------------------------------
    // A2U8
    // Local CP_ACP ( Ansi [A] ) to utf8 encoding
    // winapi A字符 转 utf8(win 标准[W])
    // ? 推荐w字符(utf16) 损耗更少一点 napi支持直接返回utf16
    // ----------------------------------------------------------------
    extern string ansi_to_utf8(const string ansi);

    // ----------------------------------------------------------------
    // U82A
    // utf8 to Local CP_ACP ( Ansi [A] ) encoding
    // utf8 字符 转 winapi A字符
    // ? 推荐w字符(utf16) 损耗更少一点 napi支持直接返回utf16
    // ----------------------------------------------------------------
    extern string utf8_to_ansi(const string utf8);
    // UFT8 字符转为GBK(中文)
    extern string utf8_to_gbk(string u8str);

    // 判断此文本是否符合utf8特征
    extern bool is_utf8(const string input);
    // 文本中是否有数字 并且是否是安全的 int32
    extern bool is_int_str(const string Value);
    // 文本中是否有数字 并且是否是安全的 long
    extern bool is_long_str(const string Value);
    // 文本中是否有数字 并且是否是安全的 long long
    extern bool is_longlong_str(const string Value);

    // 拼接文本
    extern wstring join(vector<wstring> &item_list);
    extern wstring join(vector<wstring> &item_list, wstring splitter);
    extern void join(vector<wstring> &item_list, wstring splitter, wstring outputPtr);
    extern string join(vector<string> &item_list);
    extern string join(vector<string> &item_list, string splitter);
    extern void join(vector<string> &item_list, string splitter, string outputPtr);

    /**
     * @brief 仅拼接文本
     *
     * @tparam Arguments
     * @param input
     * @param firstInput
     * @param data_list
     * @return string
     */
    template <typename... Arguments>
    extern string string_join(const string &input, const string &firstInput, vector<Arguments...> data_list);
    /**
     * @brief 仅拼接文本
     *
     * @tparam Arguments
     * @param input
     * @param firstInput
     * @param data_list
     * @return wstring
     */
    template <typename... Arguments>
    extern wstring string_join(const wstring &input, const wstring &firstInput, vector<Arguments...> data_list);

    // 分割文本
    extern vector<wstring> split(wstring &sourcePtr, wchar_t splitter);
    extern void split(wstring &sourcePtr, wchar_t splitter, vector<wstring> &item_list);
    extern vector<string> split(string &sourcePtr, char splitter);
    extern void split(string &sourcePtr, char splitter, vector<string> &item_list);

    // 转义json文本
    extern wstring escapeJsonString(const wstring &input);
    extern string escapeJsonString(const string &input);

    // 替换单次
    extern void replace(wstring &sourcePtr, const wstring from, const wstring to);
    extern void replace(string &sourcePtr, string from, string to);

    /**
     * @brief 替换指定内容 在第N次出现的时候(仅本次)
     *
     * @param sourcePtr
     * @param from
     * @param bubble_index
     * @param to
     */
    extern void replace(string &sourcePtr, string from, size_t bubble_index, string to);

    // 替换全部
    extern void replaceAll(wstring &sourcePtr, const wstring from, const wstring to);
    extern void replaceAll(string &sourcePtr, string from, string to);

    // 移除尾部 为xx 的指定文本
    extern string trimLast(const string &input, const string &match);
    // 移除开头和尾部 为xx 的指定文本
    extern string trim(const string &input, const string &match);
    // 移除开头为xx 的指定文本
    extern string trimFirst(const string &input, const string &match);
    // 移除尾部 为xx 的指定文本
    extern wstring trim(const wstring &input, const wstring &match);
    // 移除开头和尾部 为xx 的指定文本
    extern wstring trimLast(const wstring &input, const wstring &match);
    // 移除开头为xx 的指定文本
    extern wstring trimFirst(const wstring &input, const wstring &match);

    // 移除尾部 为xx 的指定文本
    extern string trimLastAll(const string &input, const string &match);
    // 移除开头和尾部 为xx 的指定文本
    extern string trimAll(const string &input, const string &match);
    // 移除开头为xx 的指定文本
    extern string trimFirstAll(const string &input, const string &match);
    // 移除尾部 为xx 的指定文本
    extern wstring trimAll(const wstring &input, const wstring &match);
    // 移除开头和尾部 为xx 的指定文本
    extern wstring trimLastAll(const wstring &input, const wstring &match);
    // 移除开头为xx 的指定文本
    extern wstring trimFirstAll(const wstring &input, const wstring &match);

    // 反特殊字符序列化
    extern void unEscapeJsonString(string &sourcePtr);
    // 反特殊字符序列化
    extern void unEscapeJsonString(wstring &sourcePtr);

    template <unsigned trail_args, typename Map, typename... Args>
    extern std::string fmt11hlp(const Map *ctx, const char *format, Args... args);
    extern std::string fmt11(const char *format);
    template <typename... Args>
    extern std::string fmt11(const char *format, Args... args);
    template<typename Map>
    extern std::string fmt11map(const Map &ctx, const char *format);
    template <typename Map, typename... Args>
    extern std::string fmt11map(const Map &ctx, const char *format, Args... args);

    // c数组转json
    extern string vec2json(vector<string> item_list);
    extern wstring vec2json(vector<wstring> item_list);
    extern string vec2json();
    template <typename Arg1, typename... Args>
    extern string vec2json(Arg1 arg_1, Args... args);

    template <typename Map>
    extern string vec2json(vector<Map>);

    extern string vec2json(vector<DWORD> item_list);

};

#endif // MODE_INTERNAL_INCLUDE_HMC_STRING_UTIL_HPP