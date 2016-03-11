import java.io.*;
import java.math.BigInteger;

public class Main
{
	public static void main(String[] args) throws IOException
	{
	    //initialize();
	    
	    BufferedReader stdin = new BufferedReader(new InputStreamReader(System.in));
        String line;
        
        line = stdin.readLine();
        
        int cases = Integer.parseInt(line);
        
	    while (cases > 0)
	    {
	        line = stdin.readLine();
		    System.out.println(getPieces(line));
		    cases--;
	    }
	}

	public static BigInteger getPieces(String line)
	{
	    BigInteger numberOfLine = new BigInteger(line);
	    
	    BigInteger pieces = numberOfLine.pow(4);
	    pieces = pieces.subtract(new BigInteger("6").multiply(numberOfLine.pow(3)));
	    pieces = pieces.add(new BigInteger("23").multiply(numberOfLine.pow(2)));
	    pieces = pieces.subtract(new BigInteger("18").multiply(numberOfLine));
	    pieces = pieces.add(new BigInteger("24"));
	    pieces = pieces.divide(new BigInteger("24"));
	    
	    return pieces;  
	}
	
    public static void initialize()
    {
        int MAXM = 150, MAXD = 150;
        BigInteger result[][] = new BigInteger[MAXM][MAXD];

        for (int m = 0; m < MAXM; m++)
            for (int d = 0; d < MAXD; d++)
                result[m][d] = new BigInteger("0");

        for (int d = 0; d < MAXD; d++)
            result[0][d] = new BigInteger("1");

        for (int m = 1; m < MAXM; m++)
            for (int d = 1; d < MAXD; d++)
                for (int k = 0; k <= m - 1; k++)
                    result[m][d] = result[m][d].add(result[k][d - 1].multiply(result[m - k - 1][d]));
    }
}
