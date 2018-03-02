// Big Big Real Numbers
// UVa ID: 10464
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
            BigDecimal n1 = new BigDecimal(s.next());
            BigDecimal n2 = new BigDecimal(s.next());
            String r = n1.add(n2).stripTrailingZeros().toPlainString();
            if (!r.contains(".")) r += ".0";
            System.out.println(r);
        }
	}
}
