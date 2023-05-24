#include <fmt/core.h>
#include <limits.h>
#include <string>
#include <string_view>
#include <vector>

std::string &&int2str (int num) {

    std::string_view base[] {"one", "two",   "three", "four", "five",
                             "six", "seven", "eight", "nine"};

    std::string_view teen[] {"eleven",    "twelve",   "thirteen",
                             "fourteen",  "fifteen",  "sixteen",
                             "seventeen", "eighteen", "ninteen"};

    std::string_view ty[] {"ten",   "twenty",  "thirty", "forty", "fifty",
                           "sixty", "seventy", "eighty", "ninty"};

    if (num == 0)
        return static_cast<std::string &&> (*new std::string ("zero")); // 0
    if (num < 0)
        return static_cast<std::string &&> (
            int2str (-num).insert (0, "negtive ")); // 负数
    if (num < 10)
        return static_cast<std::string &&> (
            *new std::string (base[num - 1])); // {1..9}
    if (num < 100 && num % 10 == 0)
        return static_cast<std::string &&> (
            *new std::string (ty[num / 10 - 1])); // 整十
    if (num < 20)
        return static_cast<std::string &&> (
            *new std::string (teen[num - 11])); // {11..19}
    // 100以内的其他数
    if (num < 100)
        return static_cast<std::string &&> (
            static_cast<std::string &&> (
                (*new std::string (ty[num / 10 - 1])) += "-") +=
            base[num % 10 - 1]);
    // 1e3以内的其他数
    if (num < 1e3) {
        if (num % 100 == 0)
            return static_cast<std::string &&> (int2str (num / 1e2) +=
                                                " hunderd"); // 整百
        return static_cast<std::string &&> (
            static_cast<std::string &&> (
                int2str (num / 100) += " hunderd and ") += int2str (num % 100));
    }
    // 1e6以内的其他数
    if (num < 1e6) {
        if (num % int (1e3) == 0)
            return static_cast<std::string &&> (int2str (num / 1e3) +=
                                                " thousand");
        return static_cast<std::string &&> (
            static_cast<std::string &&> (int2str (num / 1e3) += " thousand ") +=
            int2str (num % int (1e3)));
    }
    // 1e9以内的其他数
    if (num < 1e9) {
        if (num % int (1e6) == 0)
            return static_cast<std::string &&> (int2str (num / 1e6) +=
                                                " million");
        return static_cast<std::string &&> (
            static_cast<std::string &&> (int2str (num / 1e6) += " million ") +=
            int2str (num % int (1e6)));
    }
    // 1e12以内的其他数
    if (num < 1e12) {
        if (num % int (1e9) == 0)
            return static_cast<std::string &&> (int2str (num / 1e9) +=
                                                " billion");
        return static_cast<std::string &&> (
            static_cast<std::string &&> (int2str (num / 1e9) += " billion ") +=
            int2str (num % int (1e9)));
    }
    return static_cast<std::string &&> (*new std::string ("infinity"));
}

int main (int argc, const char *argv[]) {
    if (argc == 1) {
        for (int i = -30; i <= 29; i++)
            fmt::print ("{}\n", int2str (i));
        for (int i = 30; i <= 90; i += 10)
            fmt::print ("{}\n", int2str (i));
        for (int i = 100; i <= 900; i += 100)
            fmt::print ("{}\n", int2str (i));
        for (int i = 1000; i <= 9000; i += 1000)
            fmt::print ("{}\n", int2str (i));
        fmt::print ("{}\n{}\n{}\n", int2str (1e6), int2str (1e9),
                    int2str (INT_MAX));
    } else
        fmt::print ("{}\n", int2str (atoi (argv[1])));
    return 0;
}