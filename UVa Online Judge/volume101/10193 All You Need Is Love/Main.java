// All You Need Is Love
// UVa ID: 10193
// Verdict: Accepted
// Submission Date: 2016-08-17
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
        Scanner s = new Scanner(System.in);
        int cases = s.nextInt();
        for (int c = 1; c <= cases; c++)
        {
            System.out.print("Pair #" + c + ": ");
            BigInteger n1 = new BigInteger(s.next(), 2);
            BigInteger n2 = new BigInteger(s.next(), 2);
            if (n1.gcd(n2).compareTo(BigInteger.ONE) > 0)
                System.out.println("All you need is love!");
            else
                System.out.println("Love is not all you need!");
        }
	}
}
