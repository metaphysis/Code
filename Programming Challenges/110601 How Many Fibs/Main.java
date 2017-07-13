// How Many Fibs?
// UVa ID: 10183
// Verdict: Accepted
// Submission Date: 2017-07-02
// UVa Run Time: 0.100s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

import java.io.*;
import java.util.*;
import java.math.*;

public class Main
{
    public static void main(String args[]) throws IOException
    {
        BigInteger[] f = new BigInteger[501];

        f[1] = new BigInteger("1"); f[2] = new BigInteger("2");
        for(int i = 3; i <= 500; i++) f[i] = f[i - 1].add(f[i - 2]);
        
        Scanner cin = new Scanner(System.in);
        while(cin.hasNext())
        {
            BigInteger a = new BigInteger(cin.next());
            BigInteger b = new BigInteger(cin.next());

            if (a.compareTo(BigInteger.ZERO) == 0 && b.compareTo(BigInteger.ZERO) == 0) break;
            
            int counter = 0;
            for (int i = 1; i <= 500; i++)
                if (a.compareTo(f[i]) <= 0 && b.compareTo(f[i]) >= 0)
                    counter++;

            System.out.println(counter);
        }
    }
}
