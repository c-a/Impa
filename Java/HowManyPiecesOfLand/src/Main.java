import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.math.BigInteger;


public class Main {

	public Main(BufferedReader in) throws Exception {
		int S = Integer.parseInt(in.readLine());
		for (int i = 0; i < S; i++) {
			int n = Integer.parseInt(in.readLine());
			System.out.println(pieces(n));
		}
	}

	private static BigInteger pieces(int n) {
		
		/* Summation.
		pieces = 1;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n - i; j++)
				pieces += (j-1)*(i-1) + 1;
		}
		*/
		
		// Closed form ((n*n*n*n) - 6*(n*n*n) + 23*(n*n) - 18*n)/24 + 1.
		BigInteger N = BigInteger.valueOf(n);
		BigInteger N2 = N.multiply(N);
		BigInteger N3 = N2.multiply(N);
		BigInteger N4 = N3.multiply(N);
		BigInteger pieces = N4;
		pieces = pieces.subtract(N3.multiply(BigInteger.valueOf(6)));
		pieces = pieces.add(N2.multiply(BigInteger.valueOf(23)));
		pieces = pieces.subtract(N.multiply(BigInteger.valueOf(18)));
		pieces = pieces.divide(BigInteger.valueOf(24));
		pieces = pieces.add(BigInteger.valueOf(1));

		return pieces;
	}
	
	public static void main(String[] args) throws Exception {
		InputStreamReader isr = new InputStreamReader(System.in);
		BufferedReader in = new BufferedReader(isr);

		new Main(in);
	}

}
