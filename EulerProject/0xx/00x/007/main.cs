using System;
using System.Collections.Generic;

public class Prime {
    public static void Main() {
        var primeTable = new List<ulong>();
        ulong i = 2;
        while (primeTable.Count < 1e4 + 1) {
            foreach (var elem in primeTable)
                if (i % elem == 0)
                    goto loop;
            primeTable.Add(i);
        loop:
            i++;
        }
        Console.WriteLine(primeTable[primeTable.Count-1]);
    }
}