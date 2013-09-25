import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.StringTokenizer;


public class Main {

	private static class ECoin {
		public int C;
		public int I;
		
		public ECoin(int C, int I) {
			this.C = C;
			this.I = I;
		}
	}
	
	private static class PythagoreanTripleFinder {
		
		public class Triple {
			public int a, b, c;
			
			public Triple(int a, int b, int c) {
				this.a = a;
				this.b = b;
				this.c = c;
			}
		}
		
		private final Map<Integer, List<Triple>> triples = new HashMap<Integer, List<Triple>>();
		
		public PythagoreanTripleFinder(int max) {
			
			// Generate triples
			for (int a = 3; a <= max; a++) {
				for (int b = a;; b++) {
					double c = Math.sqrt(a*a+b*b);
					if (c > max)
						break;
					
					if (c == (int)c) {
						if (!triples.containsKey((int)c))
							triples.put((int)c, new LinkedList<Triple>());
						
						List<Triple> l = triples.get((int)c);
						l.add(new Triple(a, b, (int)c));
					}
				}
			}
		}
		
		private List<Triple> getTriples(int c) {
			return triples.get(c);
		}
	}
	
	private static class MinimumCoins {
		
		private final int[][] D;
		
		public MinimumCoins(int maxSum) {
			D = new int[maxSum+1][maxSum+1];
		}
		
		public int getMinimumCoins(int C, int I, List<ECoin> eCoins) {

			for (int c = 0; c <= C; c++) {
				for (int i = 0; i <= I; i++)
					D[c][i] = Integer.MAX_VALUE;
			}
			
			D[0][0] = 0;
			for (int c = 0; c <= C; c++) {
				for (int i = 0; i <= I; i++) {
					if (c == 0 && i == 0)
						continue;

					for (ECoin e : eCoins) {
						if (e.C > c)
							break;
						else if (e.I > i)
							continue;
						
						if (D[c-e.C][i-e.I] < Integer.MAX_VALUE)
							D[c][i] = Math.min(D[c][i], D[c-e.C][i-e.I] + 1);
					}
				}
			}
			
			return D[C][I];
		}
	}
	
	public Main(BufferedReader in) throws Exception {
		int N = Integer.parseInt(in.readLine().trim());
		
		PythagoreanTripleFinder ptf = new PythagoreanTripleFinder(300);
		MinimumCoins mc = new MinimumCoins(300);

		for (int n = 0; n < N; n++) {
			String line = in.readLine();
			if (line.length() == 0)
				line = in.readLine();
			StringTokenizer st = new StringTokenizer(line);
			int M = Integer.parseInt(st.nextToken());
			int S = Integer.parseInt(st.nextToken());
			
			ArrayList<ECoin> eCoins = new ArrayList<ECoin>();
			for (int m = 0; m < M; m++) {
				st = new StringTokenizer(in.readLine());
				int C = Integer.parseInt(st.nextToken());
				int I = Integer.parseInt(st.nextToken());
				eCoins.add(new ECoin(C, I));
			}
			
			Collections.sort(eCoins, new Comparator<ECoin>() {

				@Override
				public int compare(ECoin e1, ECoin e2) {
					if (e1.C == e2.C)
						return Integer.compare(e1.I, e2.I);
					else
						return Integer.compare(e1.C, e2.C);
				}
			});
			
			int minCoins = Math.min(mc.getMinimumCoins(S, 0, eCoins), mc.getMinimumCoins(0, S, eCoins));
			
			List<PythagoreanTripleFinder.Triple> lt = ptf.getTriples(S);
			if (lt != null) {
				for (PythagoreanTripleFinder.Triple t : lt) {
					minCoins = Math.min(minCoins, mc.getMinimumCoins(t.a, t.b, eCoins));
					minCoins = Math.min(minCoins, mc.getMinimumCoins(t.b, t.a, eCoins));
				}
			}
			
			if (minCoins != Integer.MAX_VALUE)
				System.out.println(minCoins);
			else
				System.out.println("not possible");
		}
	}

	public static void main(String[] args) throws Exception {
		InputStreamReader isr = new InputStreamReader(System.in);
		BufferedReader in = new BufferedReader(isr);

		new Main(in);
	}

}
