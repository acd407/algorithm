using System;
using System.Collections.Generic;

class Program {
    public static ulong Gcd (ulong x,ulong y) {
        if (y == 0)
            return x;
        return Gcd (y, x % y);
    }
    public static ulong Lcm (ulong x,ulong y) {
        return x * y / Gcd (x, y);
    }
    public static void Main () {
        ulong ans = 1;
        for (ulong i = 1; i <= 20; i++) {
            ans = Lcm (ans, i);
        }
        Console.WriteLine(ans);
    }
}
