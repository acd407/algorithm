#include <string>
using std::string;
#define max(x, y) ((x) > (y) ? (x) : (y))
#define min(x, y) ((x) < (y) ? (x) : (y))
template <typename type>
type GCD (type x, type y) {
    if (y == 0)
        return x;
    return GCD (y, x % y);
}
template <typename type>
type LCM (type x, type y) {
    return x * y / GCD (x, y);
}
#define swap(x, y) ((x) ^= (y) ^= (x) ^= (y))
template <typename type>
void reverse (type *source, size_t len) {
    for (size_t i = 0; i < len / 2; i++)
        swap (source[i], source[len - 1 - i]);
}

string strmul (string num1, string num2) {
    size_t l1 = num1.size();
    size_t l2 = num2.size();
    char *num3 = new char[l1 + l2 + 1]();
    for (int64_t i = l1 - 1; i >= 0; i--)
        for (int64_t j = l2 - 1; j >= 0; j--) {
            num3[i + j + 1] += (num1[i] - 48) * (num2[j] - 48);
            if (num3[i + j + 1] > 9) {
                num3[i + j] += num3[i + j + 1] / 10;
                num3[i + j + 1] %= 10;
            }
        }
    for (size_t i = 0; i < l1 + l2; i++)
        num3[i] += 48;
    size_t i = 0;
    while (num3[i] == 48)
        i++;
    if (i == l1 + l2)
        i--;
    string ret (num3 + i);
    delete[] (num3);
    return ret;
}

