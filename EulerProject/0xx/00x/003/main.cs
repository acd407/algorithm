using System;
using System.Collections.Generic;

class Program {
    public static void Main() {
        ulong num = 600851475143;
        var factors = new List<ulong>();
        while (num != 1) {
            for (ulong i = 2; i <= Math.Sqrt(num); i++)
                if (num % i == 0) {
                    factors.Add(i);
                    num /= i;
                    goto cycle;
                }
            factors.Add(num);
            break;
        cycle:;
        }
        ulong max = 0;
        foreach (var i in factors)
            if (i > max)
                max = i;
        Console.WriteLine(max);
    }
}