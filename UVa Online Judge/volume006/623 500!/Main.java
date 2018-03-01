// 500!
// UVa ID: 623
// Verdict: Accepted
// Submission Date: 2016-08-17
// UVa Run Time: 0.420s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

import java.io.*;
import java.math.BigInteger;

public class Main
{
	public static void main(String[] args) throws IOException
	{
        BigInteger numbers[] = new BigInteger[1024];
        numbers[0] = new BigInteger("1");
        
        for (int i = 1; i <= 1000; i++)
            numbers[i] = numbers[i - 1].multiply(BigInteger.valueOf(i));
        
        BufferedReader stdin = new BufferedReader(new InputStreamReader(System.in));
        String line;
	    while ((line = stdin.readLine()) != null)
	    {
	        int n = Integer.parseInt(line);
		    System.out.println(line + "!");
		    System.out.println(numbers[n]);
	    }
	}
}
