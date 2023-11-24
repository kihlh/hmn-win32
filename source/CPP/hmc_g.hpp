
// 防止重复导入
#ifndef MODE_INTERNAL_INCLUDE_HMC_G_HPP
#define MODE_INTERNAL_INCLUDE_HMC_G_HPP

#include <string>
#include <windows.h>
#include <iostream>
using namespace std;

#define __HMC_CHECK_CATCH catch (char *err){};
#define __HMC_THREAD (code) std::thread([]() -> void { code }).detach();
#define __HMC_VirtualAlloc(Type, leng) (Type) VirtualAlloc((LPVOID)NULL, (DWORD)(leng), MEM_COMMIT, PAGE_READWRITE);
#define __HMC_VirtualFree(Virtua) \
    if (Virtua != NULL)           \
        VirtualFree(Virtua, 0, MEM_RELEASE);

#define _define_is_int32bit(T)         \
    (                                  \
        is_same_v<T, int64_t> ||       \
        is_same_v<T, long long> ||     \
        is_same_v<T, int32_t> ||       \
        is_same_v<T, size_t> ||        \
        is_same_v<T, unsigned long> || \
        is_same_v<T, HWND> ||          \
        is_same_v<T, long> ||          \
        is_same_v<T, long int> ||      \
        is_same_v<T, unsigned long>)

#define _define_is_int64bit(T)         \
    (                                  \
        is_same_v<T, int64_t> ||       \
        is_same_v<T, long long> ||     \
        is_same_v<T, int32_t> ||       \
        is_same_v<T, size_t> ||        \
        is_same_v<T, unsigned long> || \
        is_same_v<T, HWND> ||          \
        is_same_v<T, long> ||          \
        is_same_v<T, long int> ||      \
        is_same_v<T, unsigned long>)

// // 关闭注册表键
// #define _defined_auto_free_HKey(subHKey)            \
//     shared_ptr<void> close_key(nullptr, [&](void *) \
//                                {\
//         if (subHKey != nullptr) {\
//             ::RegCloseKey(subHKey);\
//             subHKey = nullptr;\
//         } });

// 窗口句柄
HWND __HMC_G_ConsoleHwnd = NULL;
FILE *__HMC_G_pConsoleStream;
bool __HMC_G_DEBUG = false;

// 如果导入了 hmc-console组件
#ifdef HMC_IMPORT_CONSOLE_H
#define __HMC_IN_CONSOLE_LOG_ERR_CODE_A(fn_name, error_code, error_message) hmc_console::debug(fn_name, std::string("error_code:  [ ").append(error_code).append(" ]  ").append(error_message));
#define __HMC_IN_CONSOLE_LOG_ERR_CODE_W(fn_name, error_code, error_message) std::wcout << L"[" + fn_name + L"]    " << std::wstring(L"error_code:  [ ").append(error_code).append(L" ]  ").append(error_message) << std::endl;

#define __HMC_IN_CONSOLE_LOG_ERR_A(fn_name, error_message) hmc_console::debug(fn_name, error_message);
#define __HMC_IN_CONSOLE_LOG_ERR_W(fn_name, error_message) std::wcout << L"[" + fn_name + L"]    " << error_message << std::endl;

#define __HMC_vs_Error_Code_Assert(check, LogUserName) hmc_console::debug(LogUserName, std::string("error_code:  ").append(std::to_string(check)).append("  \nPlease refer to the details:").append("https://learn.microsoft.com/zh-cn/windows/win32/debug/system-error-codes"));

#else
#define __HMC_IN_CONSOLE_LOG_ERR_CODE_A(fn_name, error_code, error_message) std::cout << "[" + fn_name + "]    " << std::string("error_code:  [ ").append(error_code).append(" ]  ").append(error_message) << std::endl;
#define __HMC_IN_CONSOLE_LOG_ERR_CODE_W(fn_name, error_code, error_message) std::wcout << L"[" + fn_name + L"]    " << std::wstring(L"error_code:  [ ").append(error_code).append(L" ]  ").append(error_message) << std::endl;
#define __HMC_vs_Error_Code_Assert(check, LogUserName) std::cout << "---------->   [ERROR]    [" << LogUserName << "]    " << std::string("error_code:  ").append(std::to_string(check)).append("  \nPlease refer to the details:").append("https://learn.microsoft.com/zh-cn/windows/win32/debug/system-error-codes") << std::endl;
#define __HMC_IN_CONSOLE_LOG_ERR_A(fn_name, error_message) std::cout << "[" + fn_name + "]    " << error_message << std::endl;
#define __HMC_IN_CONSOLE_LOG_ERR_W(fn_name, error_message) std::wcout << L"[" + fn_name + L"]    " << error_message << std::endl;

#endif // 头文件保护结束

/**
 * @brief 判断winapi错误
 *
 * @param check
 * @param LogUserName
 * @return true
 * @return false
 */
bool __HMC_vsErrorCodeAssert(DWORD check, std::string LogUserName = "HMC_CHECK")
{
    bool result = false;

    if (check == ERROR_SUCCESS)
    {
        result = true;
    }
    else
    {
        if (__HMC_G_DEBUG)
        {
            __HMC_vs_Error_Code_Assert(check, LogUserName);
        }
    }

    return result;
}

// 由于 template <typename NUMER> 不能识别 "" 和 L"" 只能string("") 所以使用类型重定向

// 打印debug内容
void __HMC_debug(string fn_name, string error_message)
{
    if (!__HMC_G_DEBUG)
    {
        return;
    }
    __HMC_IN_CONSOLE_LOG_ERR_A(fn_name, error_message);
}

void __HMC_debug(wstring fn_name, wstring error_message)
{
    if (!__HMC_G_DEBUG)
    {
        return;
    }
    __HMC_IN_CONSOLE_LOG_ERR_W(fn_name, error_message);
}

void __HMC_debug(wstring fn_name, wstring error_message, wstring error_code)
{
    if (!__HMC_G_DEBUG)
    {
        return;
    }
    __HMC_IN_CONSOLE_LOG_ERR_CODE_W(fn_name, error_code, error_message);
}

void __HMC_debug(string fn_name, string error_message, string error_code)
{
    if (!__HMC_G_DEBUG)
    {
        return;
    }
    __HMC_IN_CONSOLE_LOG_ERR_CODE_A(fn_name, error_code, error_message);
}

template <typename NUMER>
void __HMC_debug(wstring fn_name, wstring error_message, NUMER error_code)
{
    if (!__HMC_G_DEBUG)
    {
        return;
    }

    static_assert(
        (_define_is_int32bit(NUMER) || _define_is_int64bit(NUMER)),
        "[ assert_ok , assert_ok , error_code ] Unsupported type preset escape (不支持的类型预设转义)");

    wstring _error_code = to_wstring(error_code);
    __HMC_IN_CONSOLE_LOG_ERR_CODE_W(fn_name, _error_code, error_message);
}

#ifdef SRC_NODE_API_H_ // 判断napi.h是否导入

// 显示debug窗口(黑框框)
napi_value fn_hmc_debug(napi_env env, napi_callback_info info)
{
    if (::AllocConsole())
    {
        ::freopen_s(&__HMC_G_pConsoleStream, "CONOUT$", "w", stdout);
        __HMC_G_DEBUG = true;
        __HMC_G_ConsoleHwnd = ::GetConsoleWindow();
        std::cout << "[ HMC-DEUG ] Current debug mode has been enabled. Please note that debug mode will increase performance overhead, and the window can only be closed by calling hmc.hmc_debug_end() first. Otherwise, it may cause the process to crash." << std::endl;
    }

    return NULL;
}

// 释放debug窗口(黑框框)
napi_value fn_hmc_debug_end(napi_env env, napi_callback_info info)
{
    __HMC_G_DEBUG = false;
    ::FreeConsole();
    ::CloseWindow(__HMC_G_ConsoleHwnd);
    return NULL;
}

#endif // SRC_NODE_API_H_

#endif // MODE_INTERNAL_INCLUDE_HMC_G_HPP