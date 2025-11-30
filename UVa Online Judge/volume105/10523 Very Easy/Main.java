// Very Easy !!!
// UVa ID: 10523
// Verdict: Accepted
// Submission Date: 2018-03-02
// UVa Run Time: 0.280s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

import java.io.*;
import java.math.BigInteger;

public class Main
{
	public static void main(String[] args) throws IOException
	{       
        BufferedReader stdin = new BufferedReader(new InputStreamReader(System.in));
        String line;
	    while ((line = stdin.readLine()) != null)
	    {
	        line = line.trim();
	        int n = 0, a = 0;
	        for (int i = 0; i < line.length(); i++)
	        {
	            if (line.charAt(i) != ' ' && line.charAt(i) != '\t')
	                n = n * 10 + line.charAt(i) - '0';
                else
                {
                    while (line.charAt(i) == ' ' || line.charAt(i) == '\t') i++;
                    for (int j = i; j < line.length(); j++)
                        a = a * 10 + line.charAt(j) - '0';
                    break;
                }
	        } 
		    
		    BigInteger nn = BigInteger.valueOf(n);
		    BigInteger aa = BigInteger.valueOf(a);
		    BigInteger r = BigInteger.ZERO;
		    for (int i = 1; i <= n; i++)
		    {
		        r = r.add(aa.multiply(BigInteger.valueOf(i)));
		        aa = aa.multiply(BigInteger.valueOf(a));
		    }
		    System.out.println(r);
	    }
	}
}
