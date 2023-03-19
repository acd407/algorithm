using System;
using System.Collections.Generic;
using System.Linq;

class Program {
    static void Main() {
        var tab = new List<int>();
        for (int i = 100; i <= 1000; i++)
            for (int j = 100; j <= 1000; j++) {
                int num = i * j;
                var str = num.ToString();
                var len = str.Length;
                for (var k = 0; k < len / 2; k++) {
                    if (str[k] != str[len - 1 - k])
                        goto loop;
                }
                tab.Add(num);
            loop:;
            }
        Console.WriteLine(tab.Max());
    }
}