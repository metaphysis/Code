// Edge Case
// UVa ID: 1646
// Verdict: Accepted
// Submission Date: 2017-06-27
// UVa Run Time: 0.000s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

import java.io.*;
import java.util.*;
import java.math.*;

public class Main
{
    public static void main(String args[]) throws IOException
    {
        BigInteger[] f = new BigInteger[10002];
        f[3] = new BigInteger("4"); f[4] = new BigInteger("7");
        for(int i = 5; i <= 10000; i++) f[i] = f[i - 1].add(f[i - 2]);
        Scanner cin = new Scanner(System.in);
        while(cin.hasNext())
        {
            int n = cin.nextInt();
            System.out.println(f[n]);
        }
    }
}
