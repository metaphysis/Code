// Krakovia
// UVa ID: 10925
// Verdict: Accepted
// Submission Date: 2018-03-02
// UVa Run Time: 0.230s
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
        int bills = 1;
	    while (s.hasNext())
	    {
	        int N = s.nextInt(), F = s.nextInt();
	        if (N == 0) break;
	        BigInteger v = BigInteger.ZERO;
	        for (int i = 0; i < N; i++)
	            v = v.add(s.nextBigInteger());
	        System.out.print("Bill #" + bills + " costs ");
	        System.out.print(v.toString());
	        System.out.print(": each friend should pay ");
	        System.out.println(v.divide(BigInteger.valueOf(F)).toString());
	        System.out.println();
	        bills++;
	    }
	}
}
