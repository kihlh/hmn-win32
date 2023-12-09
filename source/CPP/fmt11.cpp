#include "./fmt11.h"
// https://github.com/r-lyeh-archived/fmt11
// The Unlicense
template <unsigned trail_args, typename Map, typename... Args>
inline std::string fmt11hlp(const Map *ctx, const char *format, Args... args)
{
    std::stringstream out;
    if (format)
    {
        auto tpl = std::tuple_cat(std::tuple<Args...>{args...}, std::make_tuple(0, 0, 0, 0, 0, 0, 0, 0, 0, 0));
        char raw[64], tag[32], fmt[32];
        unsigned fix, dig, counter = 0;
        while (*format)
        {
            if (*format++ != '{')
            {
                out << format[-1];
            }
            else
            {
                auto parse = [](char raw[64], char tag[32], char fmt[32], unsigned &fix, unsigned &dig, const char *in) -> int
                {
                    int lv = 0; // parses [{] { [tag][:][fmt] } [}] expressions; returns num of bytes parsed or 0 if error
                    char *o = raw, *m = tag, *g = 0;
                    while (*in && *in == '{')
                    {
                        *o++ = *in++, ++lv;
                        if ((o - raw) >= 63)
                            return 0;
                    }
                    while (*in && lv > 0)
                    {
                        /**/ if (*in < 32)
                            return 0;
                        else if (*in < '0' && !g)
                            return 0;
                        else if (*in == '}')
                            --lv, *o++ = *in++;
                        else if (*in == ':')
                            g = fmt, *o++ = *in++;
                        else
                            *(g ? g : m)++ = *o++ = *in++;
                        if (((o - raw) >= 63) || ((m - tag) >= 31) || (g && (g - fmt) >= 31))
                            return 0;
                    }
                    *o = *m = *(g ? g : fmt) = 0;
                    if (0 != lv)
                    {
                        return 0;
                    }
                    fix = dig = 0;
                    for (char *f = fmt; *f != 0; ++f)
                    {
                        char *input = f;
                        if (*input >= '0' && *input <= '9')
                        {
                            double dbl = atof(input);
                            fix = int(dbl), dig = int(dbl * 1000 - fix * 1000);
                            while (dig && !(dig % 10))
                                dig /= 10;
                            // printf("%s <> %d %d\n", input, fix, dig );
                            break;
                        }
                    }
                    return o - raw;
                };
                int read_bytes = parse(raw, tag, fmt, fix, dig, &format[-1]);
                if (!read_bytes)
                {
                    out << format[-1];
                }
                else
                {
                    // style
                    format += read_bytes - 1;
                    for (char *f = fmt; *f; ++f)
                        switch (*f)
                        {
                        default:
                            if (f[0] >= '0' && f[0] <= '9')
                            {
                                while ((f[0] >= '0' && f[0] <= '9') || f[0] == '.')
                                    ++f;
                                --f;
                                out << std::setw(fix);
                                out << std::fixed;
                                out << std::setprecision(dig);
                            }
                            else
                            {
                                out.fill(f[0]);
                            }
                            break;
                        case '#':
                            out << std::showbase;
                            break;
                        case 'b':
                            out << std::boolalpha;
                            break;
                        case 'D':
                            out << std::dec << std::uppercase;
                            break;
                        case 'd':
                            out << std::dec;
                            break;
                        case 'O':
                            out << std::oct << std::uppercase;
                            break;
                        case 'o':
                            out << std::oct;
                            break;
                        case 'X':
                            out << std::hex << std::uppercase;
                            break;
                        case 'x':
                            out << std::hex;
                            break;
                        case 'f':
                            out << std::fixed;
                            break;
                        case '<':
                            out << std::left;
                            break;
                        case '>':
                            out << std::right;
                        }
                    // value
                    char arg = tag[0];
                    if (!arg)
                    {
                        if (counter < (sizeof...(Args) - trail_args))
                        {
                            arg = '0' + counter++;
                        }
                        else
                        {
                            arg = '\0';
                        }
                        // printf("arg %d/%d\n", int(counter), (sizeof...(Args) - trail_args));
                    }
                    switch (arg)
                    {
                    default:
                        if (ctx)
                        {
                            auto find = ctx->find(tag);
                            if (find == ctx->end())
                                out << raw;
                            else
                                out << find->second;
                        }
                        else
                        {
                            out << raw;
                        }
                        break;
                    case 0:
                        out << raw;
                        break;
                    case '0':
                        out << std::get<0>(tpl);
                        break;
                    case '1':
                        out << std::get<1>(tpl);
                        break;
                    case '2':
                        out << std::get<2>(tpl);
                        break;
                    case '3':
                        out << std::get<3>(tpl);
                        break;
                    case '4':
                        out << std::get<4>(tpl);
                        break;
                    case '5':
                        out << std::get<5>(tpl);
                        break;
                    case '6':
                        out << std::get<6>(tpl);
                        break;
                    case '7':
                        out << std::get<7>(tpl);
                        break;
                    case '8':
                        out << std::get<8>(tpl);
                        break;
                    case '9':
                        out << std::get<9>(tpl);
                    }
                }
            }
        }
    }
    return out.str();
}

inline std::string fmt11(const char *format)
{
    return fmt11hlp<1, std::map<std::string, std::string>>(nullptr, format, 0);
}

template <typename... Args>
inline std::string fmt11(const char *format, Args... args)
{
    return fmt11hlp<0, std::map<std::string, std::string>>(nullptr, format, args...);
}

template <typename Map>
extern inline std::string fmt11map(const Map &ctx, const char *format)
{
    return fmt11hlp<1>(&ctx, format, 0);
}

template <typename Map, typename... Args>
inline std::string fmt11map(const Map &ctx, const char *format, Args... args)
{
    return fmt11hlp<0>(&ctx, format, args...);
}




// wstring

// https://github.com/r-lyeh-archived/fmt11
// The Unlicense
template <unsigned trail_args, typename Map, typename... Args>
inline std::wstring fmt11hlp(const Map *ctx, const wchar_t *format, Args... args)
{
    std::wstringstream out;
    if (format)
    {
        auto tpl = std::tuple_cat(std::tuple<Args...>{args...}, std::make_tuple(0, 0, 0, 0, 0, 0, 0, 0, 0, 0));
        wchar_t raw[64], tag[32], fmt[32];
        unsigned fix, dig, counter = 0;
        while (*format)
        {
            if (*format++ != L'{')
            {
                out << format[-1];
            }
            else
            {
                auto parse = [](wchar_t raw[64], wchar_t tag[32], wchar_t fmt[32], unsigned &fix, unsigned &dig, const wchar_t *in) -> int
                {
                    int lv = 0; // parses [{] { [tag][:][fmt] } [}] expressions; returns num of bytes parsed or 0 if error
                    wchar_t *o = raw, *m = tag, *g = 0;
                    while (*in && *in == L'{')
                    {
                        *o++ = *in++, ++lv;
                        if ((o - raw) >= 63)
                            return 0;
                    }
                    while (*in && lv > 0)
                    {
                        /**/ if (*in < 32)
                            return 0;
                        else if (*in < L'0' && !g)
                            return 0;
                        else if (*in == L'}')
                            --lv, *o++ = *in++;
                        else if (*in == L':')
                            g = fmt, *o++ = *in++;
                        else
                            *(g ? g : m)++ = *o++ = *in++;
                        if (((o - raw) >= 63) || ((m - tag) >= 31) || (g && (g - fmt) >= 31))
                            return 0;
                    }
                    *o = *m = *(g ? g : fmt) = 0;
                    if (0 != lv)
                    {
                        return 0;
                    }
                    fix = dig = 0;
                    for (wchar_t *f = fmt; *f != 0; ++f)
                    {
                        wchar_t *input = f;
                        if (*input >= L'0' && *input <= L'9')
                        {
                            double dbl = _wtoi(input);
                            fix = int(dbl), dig = int(dbl * 1000 - fix * 1000);
                            while (dig && !(dig % 10))
                                dig /= 10;
                            // printf("%s <> %d %d\n", input, fix, dig );
                            break;
                        }
                    }
                    return o - raw;
                };
                int read_bytes = parse(raw, tag, fmt, fix, dig, &format[-1]);
                if (!read_bytes)
                {
                    out << format[-1];
                }
                else
                {
                    // style
                    format += read_bytes - 1;
                    for (wchar_t *f = fmt; *f; ++f)
                        switch (*f)
                        {
                        default:
                            if (f[0] >= L'0' && f[0] <= L'9')
                            {
                                while ((f[0] >= L'0' && f[0] <= L'9') || f[0] == L'.')
                                    ++f;
                                --f;
                                out << std::setw(fix);
                                out << std::fixed;
                                out << std::setprecision(dig);
                            }
                            else
                            {
                                out.fill(f[0]);
                            }
                            break;
                        case L'#':
                            out << std::showbase;
                            break;
                        case L'b':
                            out << std::boolalpha;
                            break;
                        case L'D':
                            out << std::dec << std::uppercase;
                            break;
                        case L'd':
                            out << std::dec;
                            break;
                        case L'O':
                            out << std::oct << std::uppercase;
                            break;
                        case L'o':
                            out << std::oct;
                            break;
                        case L'X':
                            out << std::hex << std::uppercase;
                            break;
                        case L'x':
                            out << std::hex;
                            break;
                        case L'f':
                            out << std::fixed;
                            break;
                        case L'<':
                            out << std::left;
                            break;
                        case L'>':
                            out << std::right;
                        }
                    // value
                    wchar_t arg = tag[0];
                    if (!arg)
                    {
                        if (counter < (sizeof...(Args) - trail_args))
                        {
                            arg = L'0' + counter++;
                        }
                        else
                        {
                            arg = L'\0';
                        }
                        // printf("arg %d/%d\n", int(counter), (sizeof...(Args) - trail_args));
                    }
                    switch (arg)
                    {
                    default:
                        if (ctx)
                        {
                            auto find = ctx->find(tag);
                            if (find == ctx->end())
                                out << raw;
                            else
                                out << find->second;
                        }
                        else
                        {
                            out << raw;
                        }
                        break;
                    case 0:
                        out << raw;
                        break;
                    case L'0':
                        out << std::get<0>(tpl);
                        break;
                    case L'1':
                        out << std::get<1>(tpl);
                        break;
                    case L'2':
                        out << std::get<2>(tpl);
                        break;
                    case L'3':
                        out << std::get<3>(tpl);
                        break;
                    case L'4':
                        out << std::get<4>(tpl);
                        break;
                    case L'5':
                        out << std::get<5>(tpl);
                        break;
                    case L'6':
                        out << std::get<6>(tpl);
                        break;
                    case L'7':
                        out << std::get<7>(tpl);
                        break;
                    case L'8':
                        out << std::get<8>(tpl);
                        break;
                    case L'9':
                        out << std::get<9>(tpl);
                    }
                }
            }
        }
    }
    return out.str();
}

inline std::wstring fmt11(const wchar_t *format)
{
    return fmt11hlp<1, std::map<std::wstring, std::wstring>>(nullptr, format, 0);
}

template <typename... Args>
inline std::wstring fmt11(const wchar_t *format, Args... args)
{
    return fmt11hlp<0, std::map<std::wstring, std::wstring>>(nullptr, format, args...);
}

template <typename Map>
extern inline std::wstring fmt11map(const Map &ctx, const wchar_t *format)
{
    return fmt11hlp<1>(&ctx, format, 0);
}

template <typename Map, typename... Args>
inline std::wstring fmt11map(const Map &ctx, const wchar_t *format, Args... args)
{
    return fmt11hlp<0>(&ctx, format, args...);
}