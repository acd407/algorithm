using System;
using System.Collections.Generic;

var prime = new List<ulong> {2};
ulong sum = 2;
for (ulong i = 3; i < 2e6; i++) {
    for (int j = 0; prime[j] <= Math.Sqrt(i); j++)
        if (i % prime[j] == 0)
            goto loop;
    prime.Add(i);
    sum += i;
loop:;
}
Console.WriteLine(sum);
