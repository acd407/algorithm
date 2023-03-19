using System;

for (int c = 1000; c > 0; c--)
    for (int a = (1000 - c) / 2; a > 0; a--) {
        int b = 1000 - c - a;
        if (a * a + b * b == c * c) {
            Console.WriteLine($"{a}^2 + {b}^2 = {c}^2");
            return;
        }
    }