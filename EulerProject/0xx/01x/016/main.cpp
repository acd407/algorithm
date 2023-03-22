#include <iostream>
#include <string>
using namespace std;
string number; // 逆序存储

void mul2() {
    char up = 0;
    for (auto& var : number) {
        var -= 48;
        var *= 2;
        var += up;
        up = 0;
        if (var > 9) {
            up += var / 10;
            var %= 10;
        }
        var += 48;
    }
    if (up != 0)
        number.push_back (up + '0');
}
int main() {
    number.push_back ('1');
    for (int i = 0; i < 1000; i++)
        mul2();
    long long sum = 0;
    for (auto var : number)
        sum += var - 48;
    cout << sum << endl;
}