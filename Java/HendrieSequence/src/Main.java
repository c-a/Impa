import java.io.BufferedReader;
import java.io.InputStreamReader;


class Hendrie {
	
	int depth;
	long leavePos;
	int result;
	
	public Hendrie(long n) {
		
		depth = 0;
		long p = n-1;
		while (p > 0) {
			depth++;
			p /= 2;
		}
		leavePos = n - pow(2, depth - 1) - 1;
		
		result = hendrie(0, 0, leavePos);
	}
	
	private int hendrie(int d, int value, long pos) {
		if (d == depth)
			return value;
		
		if (value == 0)
			return hendrie(d+1, 1, pos);
		
		long leaves = Math.max(1, pow(2, depth - d - 2));
		long nthChild = pos / leaves;
		if (nthChild < value)
			return hendrie(d+1, 0, pos-nthChild*leaves);
		else
			return hendrie(d+1, value+1, pos-value*leaves);
	}
	
	private static long pow(int a, int p) {
		long res = 1;
		for (int i = 0; i < p; i++) {
			res *= a;
		}
		return res;
	}
}
public class Main {

	public Main(BufferedReader in) throws Exception {
		
		while (true) {
			long n = Long.parseLong(in.readLine());
			if (n == 0)
				break;
			System.out.println((new Hendrie(n)).result);
		}
	}
	
	public static void main(String[] args) throws Exception {
		InputStreamReader isr = new InputStreamReader(System.in);
		BufferedReader in = new BufferedReader(isr);

		new Main(in);
	}

}
