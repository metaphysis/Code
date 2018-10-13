// Super Lucky Numbers
// UVa ID: 10722
// Verdict: 
// Submission Date: 
// UVa Run Time: s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

import java.io.*;
import java.util.*;
import java.math.BigInteger;

public class Main
{
    static int B, N;
    static BigInteger[][] cache = new BigInteger[105][2];

    static BigInteger dfs(int i, int j)
    {
        if (!cache[i][j].equals(BigInteger.valueOf(-1))) return cache[i][j];
        if (j == 1)
            return cache[i][j] = (dfs(i + 1, 0).multiply(BigInteger.valueOf(B - 2))).add(dfs(i + 1, 1));
        return cache[i][j] = (dfs(i + 1, 0).multiply(BigInteger.valueOf(B - 1))).add(dfs(i + 1, 1));
    }

    public static void main(String[]args) throws java.lang.Exception
    {
        Scanner sc = new Scanner(System.in);
        while (true)
        {
            B = sc.nextInt();
            N = sc.nextInt();
            if (B == 0 && N == 0) break;
            for (int i = 0; i < 105; ++i)
                cache[i][0] = cache[i][1] = BigInteger.valueOf(-1);
            cache[N][0] = cache[N][1] = BigInteger.ONE;
            System.out.println(dfs(1, 1).add(dfs(1, 0).multiply(BigInteger.valueOf(B - 2))));
        }
    }
}
