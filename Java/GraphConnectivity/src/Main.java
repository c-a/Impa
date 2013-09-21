import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;


public class Main {

	private static class ConnectedSubgraphs {
		
		private ArrayList<ArrayList<Integer>> nodes;
		private boolean[] marked;
		private int C = 0;
		
		public ConnectedSubgraphs(BufferedReader in) throws Exception {
			int N = in.readLine().charAt(0) - 'A' + 1;
			nodes = new ArrayList<ArrayList<Integer>>(N);
			for (int i = 0; i < N; i++)
				nodes.add(new ArrayList<Integer>());
			marked = new boolean[N];
			
			while (true) {
				String line = in.readLine();
				if (line == null || line.length() == 0)
					break;
				
				int n1 = line.charAt(0) - 'A';
				int n2 = line.charAt(1) - 'A';
				nodes.get(n1).add(n2);
				nodes.get(n2).add(n1);
			}
			
			for (int i = 0; i < N; i++) {
				if (!marked[i]) {
					C++;
					dfs(i);
				}
			}
		}
		
		public int getC() {
			return C;
		}
		
		private void dfs(int n) {
			marked[n] = true;
			for (int i : nodes.get(n)) {
				if (!marked[i])
					dfs(i);
			}
		}
	}

	public Main(BufferedReader in) throws Exception {
		int N = Integer.parseInt(in.readLine());
		in.readLine();
		for (int i = 0; i < N; i++) {
			ConnectedSubgraphs cs = new ConnectedSubgraphs(in);
			if (i > 0)
				System.out.println();
			System.out.println(cs.getC());
		}
	}
	
	public static void main(String[] args) throws Exception {
		InputStreamReader isr = new InputStreamReader(System.in);
		BufferedReader in = new BufferedReader(isr);

		new Main(in);
	}

}
