// Opening Doors
// UVa ID: 10606
// Verdict: Accepted
// Submission Date: 2018-12-01
// UVa Run Time: 0.910s
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
            BigInteger N = new BigInteger(line);
            if (N.compareTo(BigInteger.ZERO) == 0) break;
            BigInteger lowN = BigInteger.ZERO, highN = N, middleN;
            while (lowN.compareTo(highN) <= 0)
            {
                middleN = lowN.add(highN).divide(BigInteger.valueOf(2));
                if (middleN.multiply(middleN).compareTo(N) > 0) highN = middleN.subtract(BigInteger.ONE);
                else lowN = middleN.add(BigInteger.ONE);
            }
            lowN = lowN.subtract(BigInteger.ONE);
            System.out.println(lowN.multiply(lowN));
        }
    }
}
