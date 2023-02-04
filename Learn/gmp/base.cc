#include <fmt/core.h>
#include <gmpxx.h>
#include <iostream>

int main()
{
    mpz_class res(1);
    int i(1);
    for (i=1;i!=100;++i)
        res*=i;
    //fmt::print("{}", res.get_str(16));
    std::cout << res << std::endl;
    return 0;
}