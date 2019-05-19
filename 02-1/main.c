#include <stdio.h>
#include <stdint.h>

int main()
{
    int8_t letters = 26;
    int8_t digits = 10;
    int64_t result = 0;
    int64_t tmp = 0;
    int32_t ch = 0;
    while((ch = getchar()) != EOF) {
        if (ch == '&') {
            result &= tmp;
            tmp = 0;
        }
        if (ch == '|') {
            result |= tmp;
            tmp = 0;
        }
        if (ch == '^') {
            result ^= tmp;
            tmp = 0;
        }
        if (ch == '~')   result = ~result;
        if ('a' <= ch && 'z' >= ch) tmp |= 1ULL << (ch - 'a' + digits + letters);
        if ('A' <= ch && 'Z' >= ch) tmp |= 1ULL << (ch - 'A' + digits);
        if ('0' <= ch && '9' >= ch) tmp |= 1ULL << (ch - '0');
    }
    int32_t res = '1';
    int i = 0;
    while (i < 2 * letters + digits) {
        if (i < digits) res = i + '0';
        if (i >= digits && i < digits + letters) res = i - digits + 'A';
        if (i >= digits + letters && i < digits + 2 * letters) {
            res = i - letters - digits + 'a';
        }
        if (((result >> i) & 1)) printf("%c", res);
        ++i;
    }
    return 0;
}
