// Facing Problem With Trees
// UVa ID: 10643
// Verdict: Accepted
// Submission Date: 2018-06-02
// UVa Run Time: 0.230s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net
//
// P=1/2*(m!)/((m/2)!*(m/2)!).

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
            System.out.print("Case " + cs + ": ");
            int m = scan.nextInt();
            BigInteger r = BigInteger.valueOf(1);
            for (int i = m / 2 + 1; i <= m; i++)
                r = r.multiply(BigInteger.valueOf(i));
            for (int i = 2; i <= m / 2; i++)
                r = r.divide(BigInteger.valueOf(i));
            r = r.divide(BigInteger.valueOf(2));
            System.out.println(r);
        }
    }
}
