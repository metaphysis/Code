// High-Precision Number
// UVa ID: 11821
// Verdict: Accepted
// Submission Date: 2016-08-17
// UVa Run Time: 0.180s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

import java.io.*;
import java.util.*;
import java.math.BigDecimal;

public class Main
{
	public static void main(String[] args) throws IOException
	{
        Scanner s = new Scanner(System.in);
        int cases = s.nextInt();
        for (int c = 1; c <= cases; c++)
        {
            BigDecimal sum = new BigDecimal("0.0");
            while (true)
            {
                String n = s.next();
                System.out.println(n);
                if (n == "0") break;
                sum.add(new BigDecimal(n));
            }
            System.out.println(sum.stripTrailingZeros().toString());
        }
	}
}
