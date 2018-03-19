// Tiling
// UVa ID: 10359
// Verdict: Accepted
// Submission Date: 2018-03-19
// UVa Run Time: 0.140s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

import java.io.*;
import java.util.*;
import java.math.BigInteger;

public class Main
{
    public static void main(String[] args) throws IOException
    {
        BigInteger r[] = new BigInteger[256];
        r[0] = BigInteger.ONE;
        r[1] = BigInteger.ONE;
        r[2] = BigInteger.valueOf(3);
        for (int i = 3; i <= 250; i++)
            r[i] = r[i - 2].multiply(BigInteger.valueOf(2)).add(r[i - 1]);

        Scanner scan = new Scanner(System.in);
        while (scan.hasNext())
        {
            int n = scan.nextInt();
            System.out.println(r[n]);
        }
    }
}
