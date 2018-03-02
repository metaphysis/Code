// High-Precision Number
// UVa ID: 11821
// Verdict: Accepted
// Submission Date: 2018-03-02
// UVa Run Time: 0.070s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

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
            BigDecimal sum = BigDecimal.ZERO;
            while (true)
            {
                String n = s.next();
                if (n.equals("0")) break;
                sum = sum.add(new BigDecimal(n));
            }
            String r = sum.toPlainString();
            while (r.endsWith("0")) r = r.substring(0, r.length() - 1);
            if (r.endsWith(".")) r = r.substring(0, r.length() - 1);
            System.out.println(r);
        }
	}
}
