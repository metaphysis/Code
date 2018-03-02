// Square Root
// UVa ID: 10023
// Verdict: Accepted
// Submission Date: 2016-08-17
// UVa Run Time: 1.710s
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
            if (c > 1) System.out.println();
            BigInteger n = s.nextBigInteger();
            BigInteger low = BigInteger.ONE, high = n.divide(BigInteger.valueOf(2));
            while (low.compareTo(high) <= 0)
            {
                BigInteger middle = low.add(high).divide(BigInteger.valueOf(2));
                if (middle.multiply(middle).compareTo(n) < 0)
                    low = middle.add(BigInteger.ONE);
                else
                    high = middle.subtract(BigInteger.ONE);
            }
            if (low.multiply(low).compareTo(n) > 0) low = low.subtract(BigInteger.ONE);
            System.out.println(low.toString());
        }
	}
}
