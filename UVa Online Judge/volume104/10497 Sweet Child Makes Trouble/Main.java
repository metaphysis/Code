// Sweet Child Makes Trouble
// UVa ID: 10497
// Verdict: Accepted
// Submission Date: 2017-07-22
// UVa Run Time: 0.400s
//
// 版权所有（C）2017，邱秋。metaphysis # yeah dot net

import java.io.*;
import java.util.*;
import java.math.*;

public class Main
{
    public static void main(String args[]) throws IOException
    {
        BigInteger[] D = new BigInteger[801];
        D[1] = new BigInteger("0"); D[2] = new BigInteger("1");
        for(int i = 3; i <= 800; i++)
        {
            D[i] = BigInteger.valueOf(i - 1);
            D[i] = D[i].multiply(D[i - 1].add(D[i - 2]));
        }
            
        Scanner cin = new Scanner(System.in);
        while(cin.hasNext())
        {
            int n = cin.nextInt();
            if (n == -1) break;
            System.out.println(D[n]);
        }
    }
}
