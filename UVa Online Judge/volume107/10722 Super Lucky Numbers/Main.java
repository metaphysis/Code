// Super Lucky Numbers
// UVa ID: 10722
// Verdict: Accepted
// Submission Date: 2018-10-13
// UVa Run Time: 0.770s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

import java.io.*;
import java.util.*;
import java.math.BigInteger;

public class Main
{
    static int LAST_DIGIT_NOT_ONE = 0, LAST_DIGIT_IS_ONE = 1;
    public static void main(String[]args) throws java.lang.Exception
    {
        int B, N;
        BigInteger[][] dp = new BigInteger[101][2];
        Scanner sc = new Scanner(System.in);
        while (true)
        {
            B = sc.nextInt();
            N = sc.nextInt();
            if (B == 0) break;
            dp[1][LAST_DIGIT_NOT_ONE] = BigInteger.valueOf(B - 2);
            dp[1][LAST_DIGIT_IS_ONE] = BigInteger.ONE;
            for (int i = 2; i <= N; i++)
            {
                dp[i][LAST_DIGIT_NOT_ONE] = dp[i - 1][LAST_DIGIT_IS_ONE].multiply(BigInteger.valueOf(B - 2)).add(dp[i - 1][LAST_DIGIT_NOT_ONE].multiply(BigInteger.valueOf(B - 1)));
                dp[i][LAST_DIGIT_IS_ONE] = dp[i - 1][LAST_DIGIT_IS_ONE].add(dp[i - 1][LAST_DIGIT_NOT_ONE]);
            }
            System.out.println(dp[N][LAST_DIGIT_NOT_ONE].add(dp[N][LAST_DIGIT_IS_ONE]));
        }
    }
}
