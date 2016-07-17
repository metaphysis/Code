// Pascal's Triangle of Death
// UVa ID: 485
// Verdict: Accepted
// Submission Date: 2016-07-17
// UVa Run Time: 0.440s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

import java.io.*;
import java.math.BigInteger;

public class Main
{
	public static void main(String[] args) throws IOException
	{
	    BigInteger[] number = new BigInteger[220];
	    
	    for (int i = 1; i <= 205; i++)
	    {
	        number[i] = new BigInteger("1");
	        
	        for (int j = i - 1; j > 1; j--)
	            number[j] = number[j].add(number[j - 1]);
            
            for (int j = 1; j <= i; j++)
            {
                if (j > 1) System.out.print(' ');
                System.out.print(number[j]);
            }
            System.out.println();
	    }
	}
}
