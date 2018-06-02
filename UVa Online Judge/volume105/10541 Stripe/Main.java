// Stripe
// UVa ID: 10541
// Verdict: Accepted
// Submission Date: 2018-06-01
// UVa Run Time: 0.070s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

import java.io.*;
import java.util.*;
import java.math.BigInteger;

public class Main
{
    public static void main(String[] args) throws IOException
    {
        Scanner scan = new Scanner(System.in);
        int cases = scan.nextInt();
        for (int cs = 1; cs <= cases; cs++)
        {
            int N = scan.nextInt(), K = scan.nextInt();
            int T = 0;
            for (int i = 0; i < K; i++)
                T += scan.nextInt();
            N = N - T - (K - 1);
            if (N < 0)
            {
                System.out.println(0);
                continue;
            }
            N = N + K;
            BigInteger r = BigInteger.valueOf(1);
            for (int i = 0; i < K; i++)
                r = r.multiply(BigInteger.valueOf(N - i));
            for (int i = 2; i <= K; i++)
                r = r.divide(BigInteger.valueOf(i));
            System.out.println(r);
        }
    }
}
