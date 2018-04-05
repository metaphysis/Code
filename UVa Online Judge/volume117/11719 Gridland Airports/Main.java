// Gridland Airports
// UVa ID: 11719
// Verdict: Accepted
// Submission Date: 2018-04-05
// UVa Run Time: 0.720s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

import java.io.*;
import java.util.*;
import java.math.BigInteger;

public class Main
{
    public static void main(String[] args) throws IOException
    {
        BigInteger R, C;
        BigInteger r = new BigInteger("10000000000000007");

        Scanner scan = new Scanner(System.in);

        int cases = scan.nextInt();
        for (int c = 1; c <= cases; c++)
        {
            long n = scan.nextInt();
            long m = scan.nextInt();
    
            long left = ((n + 1) / 2) * ((m + 1) / 2) + (n / 2) * (m / 2);
            long right = n * m - left;

            R = BigInteger.valueOf(left);
            C = BigInteger.valueOf(right);

            R = modPow(R, right - 1, r);
            C = modPow(C, left - 1, r);

            System.out.println(R.multiply(C).remainder(r));
        }

    }
    
    private static BigInteger modPow(BigInteger n, long k, BigInteger mod)
    {
        if (k == 0) return BigInteger.ONE;
        BigInteger r = modPow(n.multiply(n).remainder(mod), k >> 1, mod);
        if (k % 2 == 1) r = r.multiply(n).remainder(mod);
        return r;
    }
}
