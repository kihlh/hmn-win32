
// 防止重复导入
#ifndef MODE_INTERNAL_INCLUDE_HMC_STRING_UTIL_HPP
#define MODE_INTERNAL_INCLUDE_HMC_STRING_UTIL_HPP

#include <string>
#include <vector>
#include <windows.h>
#include <crtdbg.h> // For _ASSERTE()

#include <limits>    // For numeric_limits
#include <stdexcept> // For overflow_error

using namespace std;

class hmc_string_util
{
public:
    // ----------------------------------------------------------------
    // W2U8
    // utf 16 to utf8 encoding
    // utf16(win 标准) 转 utf8 字符(win 标准)
    // ----------------------------------------------------------------
    static string utf16_to_utf8(const wstring utf16);

    // ----------------------------------------------------------------
    // U82W
    // utf 8 to utf16 encoding
    // utf8(win 标准) 转 utf16 字符(win 标准)
    // ----------------------------------------------------------------

    static wstring utf8_to_utf16(const string utf8);

    // ----------------------------------------------------------------
    // W2A
    // utf 16 to Local CP_ACP ( Ansi [A] ) encoding
    // utf16(win 标准[W]) 转 winapi A字符
    // ----------------------------------------------------------------
    static string utf16_to_ansi(const wstring utf16);

    // ----------------------------------------------------------------
    // A2W
    // Local CP_ACP ( Ansi [A] ) to utf16 encoding
    // winapi A字符 转 utf16(win 标准[W])
    // ----------------------------------------------------------------
    static wstring ansi_to_utf16(const string ansi);

    // ----------------------------------------------------------------
    // A2U8
    // Local CP_ACP ( Ansi [A] ) to utf8 encoding
    // winapi A字符 转 utf8(win 标准[W])
    // ? 推荐w字符(utf16) 损耗更少一点 napi支持直接返回utf16
    // ----------------------------------------------------------------
    static string ansi_to_utf8(const string ansi);

    // ----------------------------------------------------------------
    // U82A
    // utf8 to Local CP_ACP ( Ansi [A] ) encoding
    // utf8 字符 转 winapi A字符
    // ? 推荐w字符(utf16) 损耗更少一点 napi支持直接返回utf16
    // ----------------------------------------------------------------
    static string utf8_to_ansi(const string utf8);
    // UFT8 字符转为GBK(中文)
    static string utf8_to_gbk(string u8str);

    // 判断此文本是否符合utf8特征
    static bool is_utf8(const string input);
    // 文本中是否有数字 并且是否是安全的 int32
    static bool is_int_str(const string Value);
    // 文本中是否有数字 并且是否是安全的 long
    static bool is_long_str(const string Value);
    // 文本中是否有数字 并且是否是安全的 long long
    static bool is_longlong_str(const string Value);

    // 拼接文本
    static wstring join(vector<wstring> &item_list);
    static wstring join(vector<wstring> &item_list, wstring splitter);
    static void join(vector<wstring> &item_list, wstring splitter, wstring outputPtr);
    static string join(vector<string> &item_list);
    static string join(vector<string> &item_list, string splitter);
    static void join(vector<string> &item_list, string splitter, string outputPtr);

    // 分割文本
    static vector<wstring> split(wstring &sourcePtr, wchar_t splitter);
    static void split(wstring &sourcePtr, wchar_t splitter, vector<wstring> &item_list);
    static vector<string> split(string &sourcePtr, char splitter);
    static void split(string &sourcePtr, char splitter, vector<string> &item_list);

    // 转义json文本
    static wstring escapeJsonString(const wstring &input);
    static string escapeJsonString(const string &input);

    // 替换单次
    static void replace(wstring &sourcePtr, const wstring from, const wstring to);
    static void replace(string &sourcePtr, string from, string to);

    /**
     * @brief 替换指定内容 在第N次出现的时候(仅本次)
     *
     * @param sourcePtr
     * @param from
     * @param bubble_index
     * @param to
     */
    static void replace(string &sourcePtr, string from, size_t bubble_index, string to);

    // 替换全部
    static void replaceAll(wstring &sourcePtr, const wstring from, const wstring to);
    static void replaceAll(string &sourcePtr, string from, string to);

    // 移除尾部 为xx 的指定文本
    static string trimLast(const string &input, const string &match);
    // 移除开头和尾部 为xx 的指定文本
    static string trim(const string &input, const string &match);
    // 移除开头为xx 的指定文本
    static string trimFirst(const string &input, const string &match);
    // 移除尾部 为xx 的指定文本
    static wstring hmc_string_util::trim(const wstring &input, const wstring &match);
    // 移除开头和尾部 为xx 的指定文本
    static wstring hmc_string_util::trimLast(const wstring &input, const wstring &match);
    // 移除开头为xx 的指定文本
    static wstring hmc_string_util::trimFirst(const wstring &input, const wstring &match);

    // 反特殊字符序列化
    static void unEscapeJsonString(string &sourcePtr);
    // 反特殊字符序列化
    static void unEscapeJsonString(wstring &sourcePtr);

#ifdef defined(_MFC_VER)
    CString utf8_to_cstring(const string utf8str);
    string cstring_to_utf8(CString strValue);
#endif
};

// UFT8 字符转为GBK(中文)
string hmc_string_util::utf8_to_gbk(const string u8str)
{
    string Result;
    TCHAR *pTempTstr;
    WCHAR *pTempwstr;

    int strSizeTempVar = MultiByteToWideChar(CP_UTF8, 0, u8str.c_str(), -1, NULL, 0);
    pTempwstr = new WCHAR[strSizeTempVar + 1];

    MultiByteToWideChar(CP_UTF8, 0, u8str.c_str(), -1, pTempwstr, strSizeTempVar);
    strSizeTempVar = WideCharToMultiByte(CP_ACP, 0, pTempwstr, -1, NULL, 0, NULL, NULL);

    pTempTstr = new TCHAR[strSizeTempVar + 1];

    WideCharToMultiByte(CP_ACP, 0, pTempwstr, -1, (LPSTR)pTempTstr, strSizeTempVar, NULL, NULL);
    Result = (char *)pTempTstr;
    delete[] pTempTstr;
    delete[] pTempwstr;

    return Result;
}

// 文本中是否有数字 并且是否是安全的 int32
bool hmc_string_util::is_int_str(const string Value)
{
    bool Result = false;
    if (Value.empty())
        return Result;
    try
    {
        int n = stoi(Value);
        Result = true;
    }
    catch (const exception &e)
    {
        return Result;
    }

    return Result;
}

// 文本中是否有数字 并且是否是安全的 long
bool hmc_string_util::is_long_str(const string Value)
{
    bool Result = false;
    if (Value.empty())
        return Result;
    try
    {
        long n = stol(Value);
        Result = true;
    }
    catch (const exception &e)
    {
        return Result;
    }

    return Result;
}

// 文本中是否有数字 并且是否是安全的 long long
bool hmc_string_util::is_longlong_str(const string Value)
{
    bool Result = false;
    if (Value.empty())
        return Result;
    try
    {
        long long n = stoll(Value);
        Result = true;
    }
    catch (const exception &e)
    {
        return Result;
    }

    return Result;
}

inline wstring hmc_string_util::utf8_to_utf16(const string utf8)
{
    // 源作者@ https://github.com/GiovanniDicanio/UnicodeConversions/    for MIT license 注意：与原稿对比有多处改动

    // Result of the conversion
    wstring utf16;

    // First, handle the special case of empty input string
    if (utf8.empty())
    {
        _ASSERTE(utf16.empty());
        return utf16;
    }

    // Safely fail if an invalid UTF-8 character sequence is encountered
    constexpr DWORD kFlags = MB_ERR_INVALID_CHARS;

    // Safely cast the length of the source UTF-8 string (expressed in chars)
    // from size_t (returned by string::length()) to int
    // for the MultiByteToWideChar API.
    // If the size_t value is too big to be stored into an int,
    // throw an exception to prevent conversion errors like huge size_t values
    // converted to *negative* integers.
    if (utf8.length() > static_cast<size_t>((numeric_limits<int>::max)()))
    {
        __HMC_debug(string("Utf8ToUtf16"), string("Input string too long: size_t-length doesn't fit into int."));
    }
    const int utf8Length = static_cast<int>(utf8.length());

    // Get the size of the destination UTF-16 string
    const int utf16Length = ::MultiByteToWideChar(
        CP_UTF8,     // source string is in UTF-8
        kFlags,      // conversion flags
        utf8.data(), // source UTF-8 string pointer
        utf8Length,  // length of the source UTF-8 string, in chars
        nullptr,     // unused - no conversion done in this step
        0            // request size of destination buffer, in wchar_ts
    );
    if (utf16Length == 0)
    {
        // Conversion error: capture error code and throw
        const DWORD error = ::GetLastError();
        // hmc::error

        // hmc::error
        string error_message = string(error == ERROR_NO_UNICODE_TRANSLATION ? "Invalid UTF-8 sequence found in input string." : "Cannot convert from UTF-8 to UTF-16 (WideCharToMultiByte failed).");
        __HMC_debug(string("Utf16ToUtf8"), error_message, to_string(error));
    }

    // Make room in the destination string for the converted bits
    utf16.resize(utf16Length);

    // Do the actual conversion from UTF-8 to UTF-16
    int result = ::MultiByteToWideChar(
        CP_UTF8,     // source string is in UTF-8
        kFlags,      // conversion flags
        utf8.data(), // source UTF-8 string pointer
        utf8Length,  // length of source UTF-8 string, in chars
        &utf16[0],   // pointer to destination buffer
        utf16Length  // size of destination buffer, in wchar_ts
    );
    if (result == 0)
    {
        // Conversion error: capture error code and throw
        const DWORD error = ::GetLastError();
        // hmc::error
        string error_message = string(error == ERROR_NO_UNICODE_TRANSLATION ? "Invalid UTF-8 sequence found in input string." : "Cannot convert from UTF-8 to UTF-16 (WideCharToMultiByte failed).");
        __HMC_debug(string("Utf16ToUtf8"), error_message, to_string(error));
    }

    return utf16;
}

inline string hmc_string_util::utf16_to_utf8(const wstring utf16)
{
    // 源作者@ https://github.com/GiovanniDicanio/UnicodeConversions/    for MIT license 注意：与原稿对比有多处改动
    // Result of the conversion
    string utf8;

    // First, handle the special case of empty input string
    if (utf16.empty())
    {
        _ASSERTE(utf8.empty());
        return utf8;
    }

    // Safely fail if an invalid UTF-16 character sequence is encountered
    constexpr DWORD kFlags = WC_ERR_INVALID_CHARS;

    // Safely cast the length of the source UTF-16 string (expressed in wchar_ts)
    // from size_t (returned by wstring::length()) to int
    // for the WideCharToMultiByte API.
    // If the size_t value is too big to be stored into an int,
    // throw an exception to prevent conversion errors like huge size_t values
    // converted to *negative* integers.
    if (utf16.length() > static_cast<size_t>((numeric_limits<int>::max)()))
    {
        __HMC_debug(string("Utf16ToUtf8"), string("Input string too long: size_t-length doesn't fit into int."));
    }
    const int utf16Length = static_cast<int>(utf16.length());

    // Get the length, in chars, of the resulting UTF-8 string
    const int utf8Length = ::WideCharToMultiByte(
        CP_UTF8,         // convert to UTF-8
        kFlags,          // conversion flags
        utf16.data(),    // source UTF-16 string
        utf16Length,     // length of source UTF-16 string, in wchar_ts
        nullptr,         // unused - no conversion required in this step
        0,               // request size of destination buffer, in chars
        nullptr, nullptr // unused
    );
    if (utf8Length == 0)
    {
        // Conversion error: capture error code and throw
        const DWORD error = ::GetLastError();
        // hmc::error
        string error_message = string(error == ERROR_NO_UNICODE_TRANSLATION ? "Invalid UTF-16 sequence found in input string." : "Cannot convert from UTF-16 to UTF-8 (WideCharToMultiByte failed).");
        __HMC_debug(string("Utf16ToUtf8"), error_message, to_string(error));
    }

    // Make room in the destination string for the converted bits
    utf8.resize(utf8Length);

    // Do the actual conversion from UTF-16 to UTF-8
    int result = ::WideCharToMultiByte(
        CP_UTF8,         // convert to UTF-8
        kFlags,          // conversion flags
        utf16.data(),    // source UTF-16 string
        utf16Length,     // length of source UTF-16 string, in wchar_ts
        &utf8[0],        // pointer to destination buffer
        utf8Length,      // size of destination buffer, in chars
        nullptr, nullptr // unused
    );
    if (result == 0)
    {
        // Conversion error: capture error code and throw
        const DWORD error = ::GetLastError();
        // hmc::error
        string error_message = string(error == ERROR_NO_UNICODE_TRANSLATION ? "Invalid UTF-16 sequence found in input string." : "Cannot convert from UTF-16 to UTF-8 (WideCharToMultiByte failed).");
        __HMC_debug(string("Utf16ToUtf8"), error_message, to_string(error));
    }

    return utf8;
}

inline string hmc_string_util::utf16_to_ansi(const wstring utf16)
{

    string ansi;

    if (utf16.empty())
    {
        _ASSERTE(ansi.empty());
        return ansi;
    }

    constexpr DWORD kFlags = WC_ERR_INVALID_CHARS;

    if (utf16.length() > static_cast<size_t>((numeric_limits<int>::max)()))
    {
        __HMC_debug(string("Utf16ToAnsi"), string("Input string too long: size_t-length doesn't fit into int."));
        return ansi;
    }

    const int utf16Length = static_cast<int>(utf16.length());

    const int ansiLength = ::WideCharToMultiByte(
        CP_ACP,
        kFlags,
        utf16.data(),
        utf16Length,
        nullptr,
        0,
        nullptr, nullptr);
    if (ansiLength == 0)
    {
        const DWORD error = ::GetLastError();
        // hmc::error
        string error_message = string(error == ERROR_NO_UNICODE_TRANSLATION ? "Invalid UTF-16 sequence found in input string." : "Cannot convert from UTF-16 to CP_ACP (WideCharToMultiByte failed).");
        __HMC_debug(string("Utf16ToAnsi"), error_message, to_string(error));
    }

    ansi.resize(ansiLength);

    int result = ::WideCharToMultiByte(
        CP_ACP,
        kFlags,
        utf16.data(),
        utf16Length,
        &ansi[0],
        ansiLength,
        nullptr, nullptr);
    if (result == 0)
    {
        const DWORD error = ::GetLastError();
        // hmc::error
        string error_message = string(error == ERROR_NO_UNICODE_TRANSLATION ? "Invalid UTF-16 sequence found in input string." : "Cannot convert from UTF-16 to CP_ACP (WideCharToMultiByte failed).");
        __HMC_debug(string("Utf16ToAnsi"), error_message, to_string(error));
    }

    return ansi;
}

inline wstring hmc_string_util::ansi_to_utf16(const string ansi)
{

    wstring utf16;

    if (ansi.empty())
    {
        _ASSERTE(utf16.empty());
        return utf16;
    }

    constexpr DWORD kFlags = MB_ERR_INVALID_CHARS;

    if (ansi.length() > static_cast<size_t>((numeric_limits<int>::max)()))
    {
        __HMC_debug(string("AnsiToUtf16"), string("Input string too long: size_t-length doesn't fit into int."));
    }
    const int utf8Length = static_cast<int>(ansi.length());

    const int utf16Length = ::MultiByteToWideChar(
        CP_ACP,
        kFlags,
        ansi.data(),
        utf8Length,
        nullptr,
        0);
    if (utf16Length == 0)
    {
        const DWORD error = ::GetLastError();
        // hmc::error
        string error_message = string(error == ERROR_NO_UNICODE_TRANSLATION ? "Invalid ansi sequence found in input string." : "Cannot convert from ansi to UTF-16 (WideCharToMultiByte failed).");
        __HMC_debug(string("AnsiToUtf16"), error_message, to_string(error));
    }

    utf16.resize(utf16Length);

    int result = ::MultiByteToWideChar(
        CP_ACP,
        kFlags,
        ansi.data(),
        utf8Length,
        &utf16[0],
        utf16Length);
    if (result == 0)
    {
        const DWORD error = ::GetLastError();
        // hmc::error
        string error_message = string(error == ERROR_NO_UNICODE_TRANSLATION ? "Invalid ansi sequence found in input string." : "Cannot convert from ansi to UTF-16 (WideCharToMultiByte failed).");
        __HMC_debug(string("AnsiToUtf16"), error_message, to_string(error));
    }

    return utf16;
}

inline string hmc_string_util::ansi_to_utf8(const string ansi)
{
    wstring to_utf16 = ansi_to_utf16(ansi);
    return utf16_to_utf8(to_utf16);
}

inline string hmc_string_util::utf8_to_ansi(const string utf8)
{
    wstring to_utf16 = utf8_to_utf16(utf8);
    return utf16_to_ansi(to_utf16);
}

inline bool hmc_string_util::is_utf8(const string input)
{
    for (string::const_iterator str = input.begin(), eos = input.end(); str != eos; ++str)
    {
        unsigned char cuChar = static_cast<unsigned char>(*str);
        size_t len = sizeof(cuChar);
        if (cuChar == '\b' || cuChar == '\n' || cuChar == '\r' || cuChar == '\f' || cuChar == '\t')
        {
            // 转义符
        }
        // 超出utf8的大小了
        else if (static_cast<unsigned char>(cuChar) >= 0xF8)
            return false;

        else if (static_cast<unsigned char>(cuChar) >= 0xF0)
        {
            if (len < 4)
                return false;
            for (int i = 1; i <= 3; i++)
            {
                if ((*(unsigned char *)(cuChar + i) & 0xC0) != 0x80)
                    return false;
            }
            return true;
        }
        else if (static_cast<unsigned char>(cuChar) >= 0xE0)
        {
            if (len < 3)
                return false;
            for (int i = 1; i <= 2; i++)
            {
                if ((*(unsigned char *)(cuChar + i) & 0xC0) != 0x80)
                    return false;
            }
            return true;
        }
        else if (static_cast<unsigned char>(cuChar) >= 0xC0)
        {

            if (len < 2)
                return false;
            if ((*(unsigned char *)(cuChar + 1) & 0xC0) != 0x80)
                return false;
            return true;
        }
        else if (static_cast<unsigned char>(cuChar) >= 0x80)
            return false;
        else
            return true;
    }
    return true;
}

/**
 * @brief 全部替换
 *
 * @param sourcePtr
 * @param from
 * @param to
 */
inline void hmc_string_util::replaceAll(string &sourcePtr, string from, string to)
{
    size_t start_pos = 0;
    while ((start_pos = sourcePtr.find(from, start_pos)) != string::npos)
    {
        sourcePtr.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
}

inline void hmc_string_util::replaceAll(wstring &sourcePtr, const wstring from, const wstring to)
{
    size_t start_pos = 0;
    while ((start_pos = sourcePtr.find(from, start_pos)) != string::npos)
    {
        sourcePtr.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
}

/**
 * @brief 替换一次
 *
 * @param sourcePtr
 * @param from
 * @param to
 */
inline void hmc_string_util::replace(string &sourcePtr, string from, string to)
{
    size_t start_pos = 0;
    while ((start_pos = sourcePtr.find(from, start_pos)) != string::npos)
    {
        sourcePtr.replace(start_pos, from.length(), to);
        start_pos += to.length();
        return;
    }
}

inline void hmc_string_util::replace(wstring &sourcePtr, const wstring from, const wstring to)
{
    size_t start_pos = 0;
    while ((start_pos = sourcePtr.find(from, start_pos)) != string::npos)
    {
        sourcePtr.replace(start_pos, from.length(), to);
        return;
    }
}

/**
 * @brief 替换指定内容 仅在第N次出现的时候执行替换
 *
 * @param sourcePtr
 * @param from
 * @param bubble_index
 * @param to
 */
inline void hmc_string_util::replace(string &sourcePtr, string from, size_t bubble_index, string to)
{
    size_t start_pos = 0;
    size_t index = 0;
    while ((start_pos = sourcePtr.find(from, start_pos)) != string::npos)
    {
        if (index == bubble_index)
        {
            sourcePtr.replace(start_pos, from.length(), to);
            return;
        }
        index++;
    }
}

inline string hmc_string_util::escapeJsonString(const string &input)
{
    string output;
    for (char ch : input)
    {
        switch (ch)
        {
        case '\"':
            output.append("\\\"");
            break;
        case '\\':
            output.append("\\\\");
            break;
        case '\b':
            output.append("\\b");
            break;
        case '\f':
            output.append("\\f");
            break;
        case '\n':
            output.append("\\n");
            break;
        case '\r':
            output.append("\\r");
            break;
        case '\t':
            output.append("\\t");
            break;
        default:
            output.push_back(ch);
            break;
        }
    }
    return output;
}

inline wstring hmc_string_util::escapeJsonString(const wstring &input)
{
    wstring output;
    for (wchar_t ch : input)
    {
        switch (ch)
        {
        case L'\"':
            output.append(L"\\\"");
            break;
        case L'\\':
            output.append(L"\\\\");
            break;
        case L'\b':
            output.append(L"\\b");
            break;
        case L'\f':
            output.append(L"\\f");
            break;
        case L'\n':
            output.append(L"\\n");
            break;
        case L'\r':
            output.append(L"\\r");
            break;
        case L'\t':
            output.append(L"\\t");
            break;
        default:
            output.push_back(ch);
            break;
        }
    }
    return output;
}

/**
 * @brief 切割文本
 *
 * @param sourcePtr
 * @param splitter
 * @param item_list
 */
void hmc_string_util::split(string &sourcePtr, char splitter, vector<string> &item_list)
{

    item_list.clear();
    if (sourcePtr.empty())
    {
        return;
    }
    string item;
    item.reserve(sourcePtr.length());

    for (auto data : sourcePtr)
    {
        if (data == splitter)
        {
            if (!item.empty())
            {

                item_list.push_back(item);
            }
            item.clear();
        }
        else
        {
            item.push_back(data);
        }
    }

    // 最后一个元素如果是空文本则不导入
    if (!item.empty())
        item_list.push_back(move(item));
}

vector<string> hmc_string_util::split(string &sourcePtr, char splitter)
{
    if (sourcePtr.empty())
    {
        return vector<string>();
    }
    vector<string> item_list;
    split(sourcePtr, splitter, item_list);
    return item_list;
}

/**
 * @brief 切割文本
 *
 * @param sourcePtr
 * @param splitter
 * @param item_list
 */
void hmc_string_util::split(wstring &sourcePtr, wchar_t splitter, vector<wstring> &item_list)
{

    item_list.clear();
    if (sourcePtr.empty())
    {
        return;
    }

    wstring item;
    item.reserve(sourcePtr.length());

    for (auto data : sourcePtr)
    {
        if (data == splitter)
        {
            if (!item.empty())
            {

                item_list.push_back(item);
            }
            item.clear();
        }
        else
        {
            item.push_back(data);
        }
    }

    // 最后一个元素如果是空文本则不导入
    if (!item.empty())
        item_list.push_back(move(item));
}

vector<wstring> hmc_string_util::split(wstring &sourcePtr, wchar_t splitter)
{
    if (sourcePtr.empty())
    {
        return vector<wstring>();
    }
    vector<wstring> item_list;
    split(sourcePtr, splitter, item_list);
    return item_list;
}

void hmc_string_util::join(vector<string> &item_list, string splitter, string outputPtr)
{
    for (size_t i = 0; i < item_list.size(); i++)
    {
        auto item = item_list[i];
        outputPtr.append(item);
        if (item_list.size() - 1 != i)
        {
            outputPtr.append(splitter);
        }
    }
}

string hmc_string_util::join(vector<string> &item_list, string splitter)
{
    string result = string();
    for (size_t i = 0; i < item_list.size(); i++)
    {
        auto item = item_list[i];
        result.append(item);
        if (item_list.size() - 1 != i)
        {
            result.append(splitter);
        }
    }

    return result;
}
string hmc_string_util::join(vector<string> &item_list)
{
    return join(item_list, string(""));
}

void hmc_string_util::join(vector<wstring> &item_list, wstring splitter, wstring outputPtr)
{
    for (size_t i = 0; i < item_list.size(); i++)
    {
        auto item = item_list[i];
        outputPtr.append(item);
        if (item_list.size() - 1 != i)
        {
            outputPtr.append(splitter);
        }
    }
}
wstring hmc_string_util::join(vector<wstring> &item_list, wstring splitter)
{
    wstring result = wstring();
    for (size_t i = 0; i < item_list.size(); i++)
    {
        auto item = item_list[i];
        result.append(item);
        if (item_list.size() - 1 != i)
        {
            result.append(splitter);
        }
    }

    return result;
}
wstring hmc_string_util::join(vector<wstring> &item_list)
{
    return join(item_list, wstring(L""));
}

string hmc_string_util::trim(const string &input, const string &match)
{
    string temp_trim_str = trimLast(input, match);
    return trimFirst(temp_trim_str, match);
}

string hmc_string_util::trimFirst(const string &input, const string &match)
{
    auto start_pos = input.find_first_not_of(match);
    return (start_pos == string::npos) ? "" : input.substr(start_pos);
}

string hmc_string_util::trimLast(const string &input, const string &match)
{
    auto end_pos = input.find_last_not_of(match);
    return (end_pos == string::npos) ? "" : input.substr(0, end_pos + 1);
}

wstring hmc_string_util::trim(const wstring &input, const wstring &match)
{
    wstring temp_trim_str = trimLast(input, match);
    return trimFirst(temp_trim_str, match);
}

wstring hmc_string_util::trimFirst(const wstring &input, const wstring &match)
{
    auto start_pos = input.find_first_not_of(match);
    return (start_pos == string::npos) ? L"" : input.substr(start_pos);
}

wstring hmc_string_util::trimLast(const wstring &input, const wstring &match)
{
    auto end_pos = input.find_last_not_of(match);
    return (end_pos == string::npos) ? L"" : input.substr(0, end_pos + 1);
}

void hmc_string_util::unEscapeJsonString(string &sourcePtr)
{
    replaceAll(sourcePtr, "\\a", "\a");
    replaceAll(sourcePtr, "\\b", "\b");
    replaceAll(sourcePtr, "\\f", "\f");
    replaceAll(sourcePtr, "\\n", "\n");
    replaceAll(sourcePtr, "\\r", "\r");
    replaceAll(sourcePtr, "\\t", "\t");
    replaceAll(sourcePtr, "\\v", "\v");
    replaceAll(sourcePtr, "\\\"", "\"");
    replaceAll(sourcePtr, "\\?", "\?");
    replaceAll(sourcePtr, "\\\\", "\\");
}

void hmc_string_util::unEscapeJsonString(wstring &sourcePtr)
{
    replaceAll(sourcePtr, L"\\a", L"\a");
    replaceAll(sourcePtr, L"\\b", L"\b");
    replaceAll(sourcePtr, L"\\f", L"\f");
    replaceAll(sourcePtr, L"\\n", L"\n");
    replaceAll(sourcePtr, L"\\r", L"\r");
    replaceAll(sourcePtr, L"\\t", L"\t");
    replaceAll(sourcePtr, L"\\v", L"\v");
    replaceAll(sourcePtr, L"\\\"", L"\"");
    replaceAll(sourcePtr, L"\\?", L"\?");
    replaceAll(sourcePtr, L"\\\\", L"\\");
}

// _MFC_VER
#ifdef defined(_MFC_VER)

#ifdef defined(_MFC_VER)

string hmc_string_util::cstring_to_utf8(CString strValue)
{
    wstring wbuffer;
#ifdef _UNICODE
    // 如果是Unicode编码，直接获取Unicode字符串
    wbuffer.assign(strValue.GetString(), strValue.GetLength());
#else
    /*
     * 转换ANSI编码到Unicode编码
     * 获取转换后长度
     */
    int length = MultiByteToWideChar(CP_ACP, MB_ERR_INVALID_CHARS, (LPCTSTR)strValue, -1, NULL, 0);
    wbuffer.resize(length);
    /* 转换 */
    MultiByteToWideChar(CP_ACP, 0, (LPCTSTR)strValue, -1, (LPWSTR)(wbuffer.data()), wbuffer.length());
#endif //_UNICODE

    /* 获取转换后长度 */
    int utf8Length = WideCharToMultiByte(CP_UTF8, 0, wbuffer.data(), wbuffer.size(), NULL, 0, NULL, NULL);
    /* 获取转换后内容 */
    string utf8Buffer;
    utf8Buffer.resize(utf8Length);

    WideCharToMultiByte(CP_UTF8, 0, wbuffer.data(), -1, (LPSTR)(utf8Buffer.data()), utf8Length, NULL, NULL);
    return (utf8Buffer);
}

#endif //_MFC_VER

#ifdef defined(_MFC_VER)

CString hmc_string_util::utf8_to_cstring(string utf8str)
{
    // 计算所需空间的大小
    int nLen = MultiByteToWideChar(CP_UTF8, NULL,
                                   utf8str.data(), utf8str.size(), NULL, 0);

    // 转换为Unicode
    wstring wbuffer;
    wbuffer.resize(nLen);
    MultiByteToWideChar(CP_UTF8, NULL, utf8str.data(), utf8str.size(),
                        (LPWSTR)(wbuffer.data()), wbuffer.length());

#ifdef UNICODE
    // 如果是Unicode编码，直接返回Unicode字符串
    return (CString(wbuffer.data(), wbuffer.length()));
#else
    /*
     * 转换为ANSI编码
     * 得到转换后长度
     */
    nLen = WideCharToMultiByte(CP_ACP, 0,
                               wbuffer.data(), wbuffer.length(), NULL, 0, NULL, NULL);

    string ansistr;
    ansistr.resize(nLen);

    // 把Unicode字符串转成ANSI编码字符串
    WideCharToMultiByte(CP_ACP, 0, (LPWSTR)(wbuffer.data()), wbuffer.length(),
                        (LPSTR)(ansistr.data()), ansistr.size(), NULL, NULL);
    return (CString(ansistr.data(), ansistr.length()));
#endif // UNICODE
}

#endif //_MFC_VER

#endif //_MFC_VER

#endif // MODE_INTERNAL_INCLUDE_HMC_STRING_UTIL_HPP