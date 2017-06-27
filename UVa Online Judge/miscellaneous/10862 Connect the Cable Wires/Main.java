// Connect the Cable Wires
// UVa ID: 10862
// Verdict: Accepted
// Submission Date: 2017-06-27
// UVa Run Time: 0.090s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

import java.io.*;
import java.util.*;
import java.math.*;

public class Main
{
    static PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));

    public static void main(String args[]) throws IOException
    {
        BigInteger[] f = new BigInteger[2048];
        f[1] = new BigInteger("1"); f[2] = new BigInteger("3");
        for(int i = 3; i <= 2000; i++)
            f[i] = f[i - 1].multiply(new BigInteger("3")).subtract(f[i - 2]);
        Scanner cin = new Scanner(System.in);
        while(cin.hasNext())
        {
            int n = cin.nextInt();
            if (n == 0) break;
            System.out.println(f[n]);
        }
    }
}
