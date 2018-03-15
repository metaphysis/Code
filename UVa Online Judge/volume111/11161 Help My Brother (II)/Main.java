// Help My Brother (II)
// UVa ID: 11161
// Verdict: Accepted
// Submission Date: 2018-03-15
// UVa Run Time: 0.110s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

import java.io.*;
import java.util.*;
import java.math.BigInteger;

public class Main
{
    public static void main(String[] args) throws IOException
    {
        BigInteger[] anchor = new BigInteger[1510], interval = new BigInteger[1510];
        BigInteger ZERO = BigInteger.ZERO, ONE = BigInteger.ONE, TWO = BigInteger.valueOf(2);
        
        anchor[0] = ZERO;
        anchor[1] = ONE;
        interval[0] = ONE;
        interval[1] = ONE;
        for (int i = 2; i <= 1500; i++)
        {
            anchor[i] = anchor[i - 1].add(interval[i - 1]);
            interval[i] = interval[i - 1].add(interval[i - 2]);
        }

        Scanner scan = new Scanner(System.in);
        int cases = 0;
        while (true)
        {
            int n = scan.nextInt();
            if (n == 0) break;

            System.out.println("Set " + (++cases) + ":");
            BigInteger r;
            if (interval[n - 1].remainder(TWO).compareTo(ZERO) == 0)
                r = anchor[n - 1].add(interval[n - 1].divide(TWO)).subtract(ONE);
            else
                r = anchor[n - 1].add(interval[n - 1].add(ONE).divide(TWO)).subtract(ONE);

            System.out.println(r);
        }
    }
}
