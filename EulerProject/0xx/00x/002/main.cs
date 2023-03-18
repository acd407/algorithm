using System;
using System.Collections.Generic;

static class Fib {
    static public void fib(ref long cur, ref long next) {
        next += cur;
        cur = next - cur;
    }
    static public void Main() {
        long a = 1, b = 1;
        long sum = 0;
        while (b < 4e6) {
            fib(ref a, ref b);
            if (b % 2 == 0)
                sum += b;
        }
        Console.WriteLine(sum);
    }
}
