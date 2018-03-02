// Division
// UVa ID: 10083
// Verdict: Accepted
// Submission Date: 2018-03-02
// UVa Run Time: 0.140s
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
	        Scanner scan = new Scanner(line);
	        int t = scan.nextInt(), a = scan.nextInt(), b = scan.nextInt();

            System.out.print("(");
	        System.out.print(t);
	        System.out.print("^");
	        System.out.print(a);
            System.out.print("-1)/");

	        System.out.print("(");
	        System.out.print(t);
	        System.out.print("^");
	        System.out.print(b);
            System.out.print("-1) ");

            // Prune.
            if (a < b || t == 1 || (a - b) * Math.log10(t) >= 100)
            {
                System.out.println("is not an integer with less than 100 digits.");
                continue;
            }

            if (a == b)
            {
                System.out.println("1");
                continue;
            }

            BigInteger bb = BigInteger.valueOf(t).pow(b);
            BigInteger aa = bb.multiply(BigInteger.valueOf(t).pow(a - b));
            bb = bb.subtract(BigInteger.ONE);
            aa = aa.subtract(BigInteger.ONE);
	        BigInteger[] r = aa.divideAndRemainder(bb);

	        if (r[0].toString().length() <= 100 && r[1] == BigInteger.ZERO)
                System.out.println(r[0].toString());
	        else
	            System.out.println("is not an integer with less than 100 digits.");
	    }
	}
}
