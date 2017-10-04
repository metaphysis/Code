// Count the Trees
// UVa ID: 10007
// Verdict: Accepted
// Submission Date: 2016-12-24
// UVa Run Time: 0.080s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

import java.io.*;
import java.math.BigInteger;

public class Main
{
	public static void main(String[] args) throws IOException
	{
        BigInteger numbers[] = new BigInteger[310];
        
        numbers[0] = BigInteger.ZERO;
        numbers[1] = BigInteger.ONE;
        
        for (int i = 2; i <= 300; i++)
            numbers[i] = numbers[i - 1].multiply(BigInteger.valueOf(4 * i - 2)).multiply(BigInteger.valueOf(i)).divide(BigInteger.valueOf(i + 1));

        String line;
        BufferedReader stdin = new BufferedReader(new InputStreamReader(System.in));
        
	    while ((line = stdin.readLine()) != null)
	    {
		    int n = Integer.parseInt(line);
		    if (n == 0) break;
		    System.out.println(numbers[n]);
	    }
	}
}
