// Throw the Dice
// UVa ID: 10238
// Verdict: Accepted
// Submission Date: 2018-06-07
// UVa Run Time: 1.320s
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
            int F = scan.nextInt(), N = scan.nextInt(), S = scan.nextInt();
            BigInteger[][] C = new BigInteger[N + 1][S + 1];
            for (int i = 0; i <= N; i++)
                for (int j = 0; j <= S; j++)
                    C[i][j] = BigInteger.ZERO;
            C[0][0] = BigInteger.ONE;
            for (int i = 1; i <= N; i++)
                for (int j = 1; j <= F; j++)
                    for (int k = Math.min(S, i * F); k >= j; k--)
                        C[i][k] = C[i][k].add(C[i - 1][k - j]);
            BigInteger T = BigInteger.ONE;
            for (int i = 1; i <= N; i++)
                T = T.multiply(BigInteger.valueOf(F));
            System.out.print(C[N][S]);
            System.out.print("/");
            System.out.println(T);
        }
    }
}
