// Basic Remains
// UVa ID: 10551
// Verdict: Accepted
// Submission Date: 2018-03-02
// UVa Run Time: 0.200s
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
	        int radix = s.nextInt();
	        if (radix == 0) break;
	        BigInteger p = new BigInteger(s.next(), radix);
	        BigInteger m = new BigInteger(s.next(), radix);
	        BigInteger r = p.remainder(m);
	        System.out.println(r.toString(radix));
	    }
	}
}
