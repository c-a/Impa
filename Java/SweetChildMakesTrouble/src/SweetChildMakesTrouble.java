import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.math.BigInteger;


class Main {
	
	BigInteger subfactorials[] = new BigInteger[801];
	
	Main(BufferedReader in) throws Exception {
		
		int items;
		
		subfactorials[0] = new BigInteger("0");
		subfactorials[1] = new BigInteger("0");
		while ((items = Integer.parseInt(in.readLine())) != -1)
		{
			BigInteger subfactorial = subfactorial(items);
			System.out.println(subfactorial.toString());
		}
	}
	
	BigInteger subfactorial(int n) {
		
		if (subfactorials[n] != null)
			return subfactorials[n];
		
		BigInteger b = BigInteger.valueOf(n);
		b = b.multiply(subfactorial(n-1));
		
		if (n % 2 == 0)
			b = b.add(BigInteger.valueOf(1));
		else
			b = b.add(BigInteger.valueOf(-1));
		
		subfactorials[n] = b;
		return b;
	}

	public static void main(String[] args) throws Exception {
		InputStreamReader isr = new InputStreamReader(System.in);
		BufferedReader in = new BufferedReader(isr);

		new Main(in);
	}

}
