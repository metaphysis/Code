// Uncle Jack
// UVa ID: 11115
// Verdict: Accepted
// Submission Date: 2018-05-31
// UVa Run Time: 0.270s
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
            BigInteger N = scan.nextBigInteger();
            int D = scan.nextInt();
            if (N.compareTo(BigInteger.ZERO) == 0) break;
            System.out.println(N.pow(D));
        }
    }
}

