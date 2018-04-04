// Anne's Game
// UVa ID: 10843
// Verdict: Accepted
// Submission Date: 2018-04-04
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
        BigInteger r = new BigInteger("2000000011");
        int cases = scan.nextInt();
        for (int c = 1; c <= cases; c++)
        {
            System.out.print("Case #" + c + ": ");
            int n = scan.nextInt();
            if (n <= 2) System.out.println(1);
            else
            {
                int exponent = n - 2;
                BigInteger base = BigInteger.valueOf(n);
                base = base.pow(exponent);
                System.out.println(base.remainder(r));
            }
        }
    }
}
