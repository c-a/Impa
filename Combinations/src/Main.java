import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.StringTokenizer;

class Main {

	private static List<Integer> primeFactors(int number) {
		int n = number; 
		List<Integer> factors = new ArrayList<Integer>();
		for (int i = 2; i <= n / i; i++) {
			while (n % i == 0) {
				factors.add(i);
				n /= i;
			}
		}
		if (n > 1) {
			factors.add(n);
		}
		return factors;
	}
	
	public static void main(String[] args) throws Exception {
		InputStreamReader isr = new InputStreamReader(System.in);
		BufferedReader in = new BufferedReader(isr);
		
		while (true) {
			String line = in.readLine();
			StringTokenizer st = new StringTokenizer(line);
			
			int N, M;
			
			N = Integer.parseInt(st.nextToken());
			M = Integer.parseInt(st.nextToken());
			if (N == 0 && M == 0)
				break;
			
			List<Integer> num = new ArrayList<Integer>();
			
			for (int i = 2; i <= N; i++) {
				num.addAll(primeFactors(i));
			}
			
			List<Integer> den = new ArrayList<Integer>();
			for (int i = 2; i <= M; i++) {
				List<Integer> factors = primeFactors(i);
				
				Iterator<Integer> iter = factors.iterator();
				while (iter.hasNext()) {
					Integer factor = iter.next();
					if (num.remove(factor))
						iter.remove();
				}
				
				den.addAll(factors);
			}
			
			for (int i = 2; i <= (N - M); i++) {
				List<Integer> factors = primeFactors(i);
				
				Iterator<Integer> iter = factors.iterator();
				while (iter.hasNext()) {
					Integer factor = iter.next();
					if (num.remove(factor))
						iter.remove();
				}
				
				den.addAll(factors);
			}
			
			long C = 1;
			for (Integer factor : num) {
				C *= factor.intValue();
			}
			for (Integer factor : den) {
				C /= factor.intValue();
			}
			
			System.out.println(N + " things taken " + M + " at a time is " + C + " exactly.");
		}
	}
}