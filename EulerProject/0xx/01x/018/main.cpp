#include <iostream>
using namespace std;
#define max(x,y) ((x)>(y)?(x):(y))
int Array[] = {
    75,
    95, 64,
    17, 47, 82,
    18, 35, 87, 10,
    20, 04, 82, 47, 65,
    19, 01, 23, 75, 03, 34,
    88, 02, 77, 73, 07, 63, 67,
    99, 65, 04, 28, 06, 16, 70, 92,
    41, 41, 26, 56, 83, 40, 80, 70, 33,
    41, 48, 72, 33, 47, 32, 37, 16, 94, 29,
    53, 71, 44, 65, 25, 43, 91, 52, 97, 51, 14,
    70, 11, 33, 28, 77, 73, 17, 78, 39, 68, 17, 57,
    91, 71, 52, 38, 17, 14, 91, 43, 58, 50, 27, 29, 48,
    63, 66, 04, 68, 89, 53, 67, 30, 73, 16, 69, 87, 40, 31,
    04, 62, 98, 27, 23, 9, 70, 98, 73, 93, 38, 53, 60, 04, 23
};
#define width 15
void setmax(int i, int j) {
    if (j == 0)
        Array[i * (i + 1) / 2 + j] += Array[i * (i - 1) / 2 + j];
    else if (j == i)
        Array[i * (i + 1) / 2 + j] += Array[i * (i - 1) / 2 + j - 1];
    else
        Array[i * (i + 1) / 2 + j] += max(Array[i * (i - 1) / 2 + j], Array[i * (i - 1) / 2 + j - 1]);
}
int main() {
    for (int i = 1; i < width; i++)
        for (int j = 0; j <= i; j++)
            setmax(i, j);
    int maxum = 0;
    for (int i = width * (width - 1) / 2 + 0; i < width * (width - 1) / 2 + 15; i++)
        if (maxum < Array[i])
            maxum = Array[i];
    cout << maxum;
}
