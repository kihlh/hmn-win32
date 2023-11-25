#ifndef FMT11_VERSION
#define FMT11_VERSION "1.0.2" /* (2016/06/01): Parse valid identifiers only \
#define FMT11_VERSION "1.0.1" // (2016/05/31): Extra boundary checks        \
#define FMT11_VERSION "1.0.0" // (2016/05/29): Initial version */

// https://github.com/r-lyeh-archived/fmt11
// The Unlicense
// This is free and unencumbered software released into the public domain.

// Anyone is free to copy, modify, publish, use, compile, sell, or
// distribute this software, either in source code form or as a compiled
// binary, for any purpose, commercial or non-commercial, and by any
// means.

// In jurisdictions that recognize copyright laws, the author or authors
// of this software dedicate any and all copyright interest in the
// software to the public domain. We make this dedication for the benefit
// of the public at large and to the detriment of our heirs and
// successors. We intend this dedication to be an overt act of
// relinquishment in perpetuity of all present and future rights to this
// software under copyright law.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
// OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// OTHER DEALINGS IN THE SOFTWARE.

// For more information, please refer to <http://unlicense.org>

#include <iomanip>
#include <map>
#include <sstream>
#include <string>
#include <tuple>

template <unsigned trail_args, typename Map, typename... Args>
extern std::string fmt11hlp(const Map *ctx, const char *format, Args... args);
extern std::string fmt11(const char *format);
template <typename... Args>
extern std::string fmt11(const char *format, Args... args);
template <typename Map>
extern std::string fmt11map(const Map &ctx, const char *format);
template <typename Map, typename... Args>
extern std::string fmt11map(const Map &ctx, const char *format, Args... args);

#endif FMT11_VERSION