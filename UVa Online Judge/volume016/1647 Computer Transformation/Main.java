// Computer Transformation
// UVa ID: 1647
// Verdict: Accepted
// Submission Date: 2022-01-04
// UVa Run Time: 0.670s
//
// 版权所有（C）2022，邱秋。metaphysis # yeah dot net

import java.io.*;
import java.math.BigInteger;

public class Main
{
    public static void main(String[]args) throws IOException
    {
        BufferedReader stdin = new BufferedReader(new InputStreamReader(System.in));
        String line;
        BigInteger[] F = new BigInteger[1024];
        F[0] = new BigInteger("2");
        F[1] = BigInteger.ZERO;
        F[2] = BigInteger.ONE;
        for (int i = 3; i <= 1000; i++) F[i] = F[0].pow(i - 3).add(F[i - 2]);
        while (true)
        {
            line = stdin.readLine();
            if (line == null) break;
            int n = Integer.parseInt(line);
            System.out.println(F[n]);
        }
    }
}
