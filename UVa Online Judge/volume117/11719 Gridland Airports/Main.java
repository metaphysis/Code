// Gridland Airports
// UVa ID: 11719
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
    public static void main(String[] args) throws IOException
    {
        BigInteger R, C, G;
        BigInteger r = new BigInteger("10000000000000007");

        Scanner scan = new Scanner(System.in);

        int cases = scan.nextInt();
        for (int c = 1; c <= cases; c++)
        {
            int n = scan.nextInt();
            int m = scan.nextInt();
            R = BigInteger.valueOf(n);
            C = BigInteger.valueOf(m);
            R = modPow(R, m - 1, r);
            C = modPow(C, n - 1, r);
            G = R.multiply(C);
            System.out.println(G.remainder(r));
        }

    }
    
    private static BigInteger modPow(BigInteger n, int k, BigInteger mod)
    {
        if (k == 0) return BigInteger.ONE;
        BigInteger r = modPow(n.multiply(n).remainder(mod), k >> 1, mod);
        if (k % 2 == 1) r = r.multiply(n).remainder(mod);
        return r;
    }
}
