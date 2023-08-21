#include "main.h"
int _printf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    int charCount = 0;
    while (*format != '\0') {
        if (*format == '%') {
            format++;
            switch (*format) {
                case 'c':
                    putchar(va_arg(args, int));
                    charCount++;
                    break;
                case 's': {
                    char str = va_arg(args, char);
                    while (*str != '\0') {
                        putchar(*str);
                        str++;
                        charCount++;
                    }
                    break;
                }
                case '%':
                    putchar('%');
                    charCount++;
                    break;
                default:
                    break;
            }
        } else {
            putchar(*format);
            charCount++;
        }
        format++;
    }
    va_end(args);
    return charCount;
}
