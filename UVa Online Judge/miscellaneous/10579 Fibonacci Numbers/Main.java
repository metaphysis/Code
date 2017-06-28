// Fibonacci Numbers
// UVa ID: 10579
// Verdict: Accepted
// Submission Date: 2017-06-28
// UVa Run Time: 0.080s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

import java.io.*;
import java.util.*;
import java.math.*;

public class Main
{
    static PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));

    public static void main(String args[]) throws IOException
    {
        BigInteger[] f = new BigInteger[5002];
        f[1] = new BigInteger("1"); f[2] = new BigInteger("1");
        for(int i = 3; i <= 5000; i++) f[i] = f[i - 1].add(f[i - 2]);
        Scanner cin = new Scanner(System.in);
        while(cin.hasNext())
        {
            int n = cin.nextInt();
            System.out.println(f[n]);
        }
    }
}
