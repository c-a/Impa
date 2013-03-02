import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.StringTokenizer;


class Main {
	
	Main(BufferedReader in) throws Exception {
		StringTokenizer st;
		int n, m;
		int[][] edges;
		
		st = new StringTokenizer (in.readLine());
		
		n = Integer.parseInt(st.nextToken());
		m = Integer.parseInt(st.nextToken());
		
		edges = new int[m][2];
		
		boolean res = true;
		for (int i = 1; i <= n; i++) {
			st = new StringTokenizer(in.readLine());
			
			if (res) {
				for (int j = 0; j < m; j++) {
					String s = st.nextToken();
					if (s.equals("1")) {
						if (edges[j][0] == 0)
							edges[j][0] = i;
						else if (edges[j][1] == 0)
							edges[j][1] = i;
						else {
							res = false;
							break;
						}
					}
				}
			}
		}
		
		if (!res) {
			System.out.println("No");
			return;
		}
		
		for (int i = 0; i < m; i++) {
			
			/* All edges should have two nodes */
			if (edges[i][0] == 0 || edges[i][1] == 0) {
					System.out.println("No");
					return;
			}
			
			if (edges[i][0] == edges[i][1]) {
				System.out.println("No");
				return;
			}
			
			/* Check duplicates */
			for (int j = i - 1; j >= 0; j--) {
				if ((edges[i][0] == edges[j][0] && edges[i][1] == edges[j][1]) ||
						(edges[i][1] == edges[j][0] && edges[i][0] == edges[j][1])) {
					System.out.println("No");
					return;
				}
			}
		}
		
		System.out.println("Yes");
	}
	
	public static void main(String[] args) throws Exception {
		InputStreamReader isr = new InputStreamReader(System.in);
		BufferedReader in = new BufferedReader(isr);
		
		int cases = Integer.parseInt(in.readLine());
		
		for (int i = 0; i < cases; i++) {
			new Main(in);
		}
	}

}
