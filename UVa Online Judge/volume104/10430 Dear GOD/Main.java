// Dear GOD
// UVa ID: 10430
// Verdict: Accepted
// Submission Date: 2018-03-03
// UVa Run Time: 0.100s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net
//
// X / K = (T^(N-1) + T^(N-2) + ... + 1) / T^N

import java.io.*;
import java.util.*;
import java.math.BigInteger;

public class Main
{
    public static void main(String[] args) throws IOException
    {
        System.out.println("Dear GOD, Pardon Me");
        int cases = 0;

        Scanner scan = new Scanner(System.in);
        while (scan.hasNext())
        {
            if (cases++ > 0) System.out.println();
            int t = scan.nextInt(), n = scan.nextInt();
            
            // Special case.
            if (t == 1)
            {
                System.out.println("X = " + n);
                System.out.println("K = 1");
                continue;
            }

            // Formula.
            BigInteger T = BigInteger.valueOf(t);
            BigInteger K = T.pow(n);
            BigInteger X = T.pow(n).subtract(BigInteger.ONE).divide(BigInteger.valueOf(t - 1));
            System.out.println("X = " + X.toString());
            System.out.println("K = " + K.toString());
        }
    }
}
