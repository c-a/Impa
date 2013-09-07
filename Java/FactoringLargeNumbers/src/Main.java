import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.PriorityQueue;

public class Main {

	public Main(BufferedReader in) throws Exception {
		
		while (true) {
			long N = Long.parseLong(in.readLine());
			if (N < 0)
				break;
			
			PriorityQueue<Long> pq = factorize(N);
			
			while (!pq.isEmpty()) {
				long l = pq.poll();
				System.out.println("    " + l);
			}
			System.out.println();
		}
	}
	
	static PriorityQueue<Long> factorize(long N) {
		PriorityQueue<Long> pq = new PriorityQueue<Long>();
		if (N == 0)
			pq.add(new Long(0));
		else {
			if (!factors(N, pq))
				pq.add(N);
		}
		return pq;
	}
	
	static boolean factors(long N, PriorityQueue<Long> pq) {
		long i;
		for (i = (long)Math.sqrt(N); i > 1; i--) {
			if (N % i == 0) {
				if (!factors(i, pq))
					pq.add(i);
				if (!factors(N/i, pq))
					pq.add(N/i);
				break;
			}
		}
		return i != 1;
	}

	public static void main(String[] args) throws Exception {
		InputStreamReader isr = new InputStreamReader(System.in);
		BufferedReader in = new BufferedReader(isr);

		new Main(in);
	}

}

