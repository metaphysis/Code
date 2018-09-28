// Coin Toss
// UVa ID: 10328
// Verdict: Accepted
// Submission Date: 2018-06-07
// UVa Run Time: 0.640s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

import java.io.*;
import java.util.*;
import java.math.BigInteger;

public class Main
{
    static BigInteger cache[][];

    public static BigInteger dfs(int n, int k, int s)
    {
        if (n < 0 || s < 0) return BigInteger.ZERO;
        if (n < s) return BigInteger.ZERO;
        if (cache[n][s] != null) return cache[n][s];
        if (s == 0) return cache[n][s] = new BigInteger("2").pow(n);
        return cache[n][s] = dfs(n - 1, k, k).add(dfs(n - 1, k, s - 1));
    }

    public static void main(String[]args) throws IOException
    {
        Scanner scan = new Scanner(System.in);
        int n, k;
        while (scan.hasNextInt())
        {
            n = scan.nextInt();
            k = scan.nextInt();
            cache = new BigInteger[n + 1][k + 1];
            System.out.println(dfs(n, k, k));
        }
    }
}
