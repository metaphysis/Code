// Who Said Crisis?
// UVa ID: 11448
// Verdict: Accepted
// Submission Date: 2018-03-02
// UVa Run Time: 0.560s
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
        int n = s.nextInt();
	    while (n > 0)
	    {
	        BigInteger a = s.nextBigInteger();
	        BigInteger b = s.nextBigInteger();
	        System.out.println(a.subtract(b).toString());
	        n--;
	    }
	}
}
