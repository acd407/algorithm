using System;
using System.Collections.Generic;
using System.Linq;

class Program {
    public static void Main() {
        ulong num = 600851475143;
        var factors = new List<ulong>();
        while (num != 1) {
            for (ulong i = 2; i <= Math.Sqrt(num); i++)
                if (num % i == 0) {
                    factors.Add(i);
                    num /= i;
                    goto loop;
                }
            factors.Add(num);
            break;
        loop:;
        }
        Console.WriteLine(factors.Max());
    }
}