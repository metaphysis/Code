// !! Really Strange !!
// UVa ID: 10519
// Verdict: Accepted
// Submission Date: 2018-03-02
// UVa Run Time: 0.060s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

import java.io.*;
import java.util.*;
import java.math.BigInteger;

public class Main
{
	public static void main(String[] args) throws IOException
	{       
        BufferedReader stdin = new BufferedReader(new InputStreamReader(System.in));
        String line;
	    while ((line = stdin.readLine()) != null)
	    {
	        BigInteger n = new BigInteger(line);
	        if (n.compareTo(BigInteger.ZERO) == 0)
	            System.out.println("1");
	        else
	            System.out.println(n.multiply(n).subtract(n).add(BigInteger.valueOf(2)).toString());
	    }
	}
}
