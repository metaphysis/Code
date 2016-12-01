// Maximum Sub-sequence Product
// UVa ID: 787
// Verdict: Accepted
// Submission Date: 2016-12-01
// UVa Run Time: 0.080s
//
// 版权所有（C）2016，邱秋。metaphysis # yeah dot net

import java.io.*;
import java.math.BigInteger;

public class Main
{
	public static void main(String[] args) throws IOException
	{
	    int n = 0;
	    boolean run = false;
	    String line;
	    
        BigInteger numbers[] = new BigInteger[110];
        BufferedReader stdin = new BufferedReader(new InputStreamReader(System.in));
        
	    while ((line = stdin.readLine()) != null)
	    {
		    String[] parts = line.split(" ");
		    for (int i = 0; i < parts.length; i++)
		    {
		        if (!parts[i].equals("-999999"))
		            numbers[n++] = new BigInteger(parts[i]);
		        else
		            run = true;
		    }
		    
		    if (run)
		    {
		        System.out.println(maximum_product(numbers, n));
		        run = false;
		        n = 0;
	        }
	    }
	}
	
	public static BigInteger maximum_product(BigInteger data[], int n)
    {
        BigInteger maximum = data[0];
        BigInteger max_current = data[0], min_current = data[0];

        for (int i = 1; i < n; i++)
        {
            BigInteger next_max = max_current.multiply(data[i]);
            BigInteger next_min = min_current.multiply(data[i]);

            max_current = data[i].max(next_max.max(next_min));
            min_current = data[i].min(next_max.min(next_min));

            maximum = maximum.max(max_current);
        }

        return maximum;
    }
}
