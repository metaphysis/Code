// The Base-1 Number SystemC
// UVa ID: 11398
// Verdict: Accepted
// Submission Date: 2018-03-05
// UVa Run Time: 0.080s
//
// 版权所有（C）2018，邱秋。metaphysis # yeah dot net

import java.io.*;
import java.util.*;
import java.math.BigInteger;

public class Main
{
    public static void main(String[] args) throws IOException
    {
        Scanner scan = new Scanner(System.in);
        String flag = "1";
        String number = new String();

        while (true)
        {
            String token = scan.next();
            if (token.equals("~")) break;
            if (token.equals("#"))
            {
                if (number.length() == 0)
                {
                    System.out.println("0");
                }
                else
                {
                    BigInteger n = new BigInteger(number, 2);
                    System.out.println(n.toString());
                }
                number = new String();
                continue;
            }
           
            if (token.equals("0")) flag = "1";
            else if (token.equals("00")) flag = "0";
            else
            {
                for (int i = 0; i < token.length() - 2; i++)
                    number += flag;
            }
        }
    }
}
