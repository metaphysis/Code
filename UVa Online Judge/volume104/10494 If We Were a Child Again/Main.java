// If We Were a Child Again
// UVa ID: 10494
// Verdict: Accepted
// Submission Date: 2018-03-02
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
        BufferedReader stdin = new BufferedReader(new InputStreamReader(System.in));
        String line;
	    while ((line = stdin.readLine()) != null)
	    {
	        Scanner s = new Scanner(line);
	        BigInteger n1 = new BigInteger(s.next());
	        String sign = s.next();
	        BigInteger n2 = new BigInteger(s.next());

	        if (sign.charAt(0) == '/')
	            System.out.println(n1.divide(n2).toString());
	        else
	            System.out.println(n1.remainder(n2).toString());
	    }
	}
}
