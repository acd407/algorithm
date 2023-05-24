#include <string>
#include <iostream>
using namespace std;
class Solution {
    public:
        string multiply(string num1, string num2) {
            int l1 = num1.size();
            int l2 = num2.size();
            char* num3 = new char[l1 + l2 + 1]();
            for (int i = l1 - 1; i >= 0; i--)
                for (int j = l2 - 1; j >= 0; j--) {
                    num3[i + j + 1] += (num1[i] - 48) * (num2[j] - 48);
                    if (num3[i + j + 1] > 9) {
                        num3[i + j] += num3[i + j + 1] / 10;
                        num3[i + j + 1] %= 10;
                    }
                }
            for (int i = 0; i < l1 + l2; i++)
                num3[i] += 48;
            int i = 0;
            while (num3[i] == 48)
                i++;
            if (i == l1 + l2)
                i--;
            string ret(num3 + i);
            delete [](num3);
            return ret;
        }
};
int main() {
    string a("9133"), b("15"), c;
    Solution sol;
    c = sol.multiply(a, b);
    cout << c;
}
