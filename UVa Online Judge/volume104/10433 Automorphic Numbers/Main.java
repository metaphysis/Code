// Automorphic Numbers
// UVa ID: 10433
// Verdict: Accepted
// Submission Date: 2018-03-02
// UVa Run Time: 0.600s
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
	        line = line.trim();
	        BigInteger a = new BigInteger(line);
	        BigInteger b = a.multiply(a);
	        String sb = b.toString();
	        int flag = 0;
	        if (sb.length() > line.length())
	        {
	            flag = 1;
	            for (int i = sb.length() - 1, j = line.length() - 1; j >= 0 && i >= 0; i--, j--)
	                if (sb.charAt(i) != line.charAt(j))
	                {
	                    flag = 0;
	                    break;
	                }
            }
            if (flag == 1)
            {
                System.out.print("Automorphic number of ");
                System.out.print(line.length());
                System.out.println("-digit.");
            }
            else
                System.out.println("Not an Automorphic number.");
	    }
	}
}
