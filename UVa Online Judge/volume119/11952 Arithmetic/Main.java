// Arithmetic
// UVa ID: 11952
// Verdict: Accepted
// Submission Date: 2018-03-02
// UVa Run Time: 0.040s
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
        line = stdin.readLine();
        int cases = Integer.parseInt(line);
        for (int cs = 1; cs <= cases; cs++)
        {
	        line = stdin.readLine();
	        Scanner s = new Scanner(line);
	        String a = s.next();
	        s.next();
	        String b = s.next();
	        s.next();
	        String c = s.next();

            String d = a + b + c;
	        char base = '0';
	        for (int i = 0; i < d.length(); i++)
	            if (d.charAt(i) > base)
	                base = d.charAt(i);

            boolean printed = false;
            int r1 = Integer.parseInt(a), r2 = Integer.parseInt(b), r3 = Integer.parseInt(c);
	        for (int radix = (base - '0' + 1); radix <= 18; radix++)
	        {
	            if (radix == r1 || radix == r2 || radix == r3) continue;
	            if (new BigInteger(a, radix).add(new BigInteger(b, radix)).compareTo(new BigInteger(c, radix)) == 0)
	            {
	                System.out.println(radix);
	                printed = true;
	                break;
	            }
	        }
	        if (!printed) System.out.println("0");
	    }
	}
}
