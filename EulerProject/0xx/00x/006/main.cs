using System;
using System.Collections.Generic;

class Program {
    public static void Main () {
        ulong sum1 = 0, sum2 = 0;
        for (ulong i = 0; i <= 100; i++) {
            sum1 += i * i;
            sum2 += i;
        }
        sum2 *= sum2;
        Console.WriteLine(sum2 - sum1);
    }
}
