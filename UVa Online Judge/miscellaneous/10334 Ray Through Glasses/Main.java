// Ray Through Glasses
// UVa ID: 10334
// Verdict: Accepted
// Submission Date: 2017-06-27
// UVa Run Time: 0.160s
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
        BigInteger[] f = new BigInteger[1002];
        f[0] = new BigInteger("1"); f[1] = new BigInteger("2");
        for(int i = 2; i <= 1000; i++) f[i] = f[i - 1].add(f[i - 2]);
        Scanner cin = new Scanner(System.in);
        while(cin.hasNext())
        {
            int n = cin.nextInt();
            System.out.println(f[n]);
        }
    }
}
