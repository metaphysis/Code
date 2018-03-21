import java.io.*;
import java.util.*;
import java.math.*;

public class Main
{
    public static void main(String args[]) throws IOException
    {
        BigInteger[] fibs = new BigInteger[10002];
        fibs[0] = new BigInteger("0");
        fibs[1] = new BigInteger("1");
        for(int i = 2; i <= 10000; i++)
            fibs[i] = fibs[i - 1].add(fibs[i - 2]);
        Scanner cin = new Scanner(System.in);
        while(cin.hasNext())
        {
            int n = cin.nextInt();
            System.out.println(fibs[n]);
        }
    }
}
