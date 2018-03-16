import java.io.*;
import java.util.*;
import java.math.*;

public class Main
{
    public static void main(String args[]) throws IOException
    {
        BigInteger[] f = new BigInteger[10002];
        f[0] = new BigInteger("0");
        f[1] = new BigInteger("1");
        for(int i = 2; i <= 10000; i++) f[i] = f[i - 1].add(f[i - 2]);
        Scanner cin = new Scanner(System.in);
        while(cin.hasNext())
        {
            int n = cin.nextInt();
            System.out.println(f[n]);
        }
    }
}
