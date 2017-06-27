// Edge Case
// UVa ID: 1646
// Verdict: Accepted
// Submission Date: 2017-06-27
// UVa Run Time: 0.000s
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
        BigInteger[] a = new BigInteger[10002];
        a[3] = new BigInteger("4"); a[4] = new BigInteger("7");
        for(int i = 5; i <= 10000; i++) a[i] = a[i-1].add(a[i-2]);
        Scanner cin = new Scanner(System.in);
        while(cin.hasNext())
        {
            int n = cin.nextInt();
            System.out.println(a[n]);
        }
    }
}
