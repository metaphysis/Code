// Ternary
// UVa ID: 11185
// Verdict: Accepted
// Submission Date: 2018-03-02
// UVa Run Time: 0.040s
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
	        if (line.charAt(0) == '-') break;
	        BigInteger n = new BigInteger(line);
	        System.out.println(n.toString(3));
	    }
	}
}
