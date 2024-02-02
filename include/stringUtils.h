#include <cstdarg>
#include <string>

String joinStrings(const char sep, uint8_t n...)
{
    va_list args;
    va_start(args, n);

    String out;

    for (uint8_t i; i<n; i++)
    {
        out += va_arg(args, String);
        if (i<n-1)
        {
            out += ' ';
        }
    }
    va_end(args);
    return out;
}
