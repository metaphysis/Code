// Bees' Ancestors
// UVa ID: 12459
// Verdict: Accepted
// Submission Date: 2018-03-02
// UVa Run Time: 0.040s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

import java.io.*;
import java.math.BigInteger;

public class Main
{
	public static void main(String[] args) throws IOException
	{
        BigInteger numbers[] = new BigInteger[84];
        numbers[0] = new BigInteger("1");
        numbers[1] = new BigInteger("1");

        for (int i = 2; i <= 80; i++)
            numbers[i] = numbers[i - 1].add(numbers[i - 2]);
        
        BufferedReader stdin = new BufferedReader(new InputStreamReader(System.in));
        String line;
	    while ((line = stdin.readLine()) != null)
	    {
	        int n = Integer.parseInt(line);
	        if (n == 0) break;
		    System.out.println(numbers[n]);
	    }
	}
}
