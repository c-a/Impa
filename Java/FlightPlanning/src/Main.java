import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.List;
import java.util.ArrayList;
import java.util.StringTokenizer;


public class Main {

	private static class Graph {
		private final ArrayList<Integer>[] adj;
		private int V;
		
		public Graph(int maxSize) {
			adj = (ArrayList<Integer>[])new ArrayList[maxSize];
			for (int i = 0; i < maxSize; i++)
				adj[i] = new ArrayList<Integer>();
		}
		
		public void reset(int V) {
			this.V = V;
			for (int v = 0; v < V; v++) {
				adj[v].clear();
			}
		}
		
		public void addEdge(int v, int w) {
			adj[v].add(w);
			adj[w].add(v);
		}
		
		public int V() {
			return this.V;
		}
		
		public Iterable<Integer> adj(int v) {
			return adj[v];
		}
	}
	
	private static class Edge {
		public int u, v;
		
		public void set(int u, int v) {
			if (u < v) {
				this.u = u;
				this.v = v;
			}
			else {
				this.u = v;
				this.v = u;
			}
		}
	}
	private static class LongestPathFinder {
		private static class Res {
			public List<Integer> depth;
			public List<Integer> diameter;
			
			public Res(int v) {
				depth = diameter = new ArrayList<Integer>();
				depth.add(v);
			}
			
			public Res(List<Integer> depth, List<Integer> diameter) {
				this.depth = depth;
				this.diameter = diameter;
			}
		}
		
		private Graph G;
		private final boolean marked[];
		
		public LongestPathFinder(int maxSize) {
			marked = new boolean[maxSize];
		}
		
		public List<Integer> getPath(Graph G, int start, int exclude) {
			this.G = G;
			Arrays.fill(marked, 0, G.V(), false);
			if (exclude >= 0)
				marked[exclude] = true;
			
			Res res = longestPath(start);
			return res.diameter;
		}
		
		private Res longestPath(int v) {
			marked[v] = true;
			
			List<Integer> d = null;
			List<Integer> dp1 = null;
			List<Integer> dp2 = null;
			Res r = null;
			for (int w : G.adj(v)) {
				if (marked[w]) continue;
				
				r = longestPath(w);
				if (d == null || r.diameter.size() > d.size())
					d = r.diameter;
				
				List<Integer> dp = r.depth;
				if (dp1 == null)
					dp1 = r.depth;
				else if (dp2 == null || dp.size() > dp2.size()) {
					if (dp.size() > dp1.size()) {
						dp2 = dp1;
						dp1 = dp;
					}
					else
						dp2 = dp;
				}
			}
			
			if (r == null)
				return new Res(v);
			
			dp1.add(v);
			if (dp2 != null && dp1.size() + dp2.size() > d.size()) {
				for (int i = dp1.size() - 1; i >= 0; i--)
					dp2.add(dp1.get(i));
				d = dp2;
			}
			else if (dp1.size() > d.size())
				d = dp1;
			
			r.depth = dp1;
			r.diameter = d;
			return r;
		}
	}
	
	public Main(BufferedReader in) throws Exception {
		Graph G = new Graph(2500);
		LongestPathFinder lpf = new LongestPathFinder(2500);
		Edge rmEdge = new Edge(), addEdge = new Edge();
		
		int N = Integer.parseInt(in.readLine().trim());
		for (int n = 0; n < N; n++) {
			int V = Integer.parseInt(in.readLine().trim());
			G.reset(V);
			for (int v = 0; v < V-1; v++) {
				StringTokenizer st = new StringTokenizer(in.readLine());
				int u = Integer.parseInt(st.nextToken());
				int w = Integer.parseInt(st.nextToken());
				G.addEdge(u-1, w-1);
			}
			
			List<Integer> path = lpf.getPath(G, 0, -1);
			int minD = path.size();
			for (int i = 0; i < path.size() - 1; i++) {
				int u = path.get(i);
				int v = path.get(i+1);
				
				List<Integer> p1 = lpf.getPath(G, u, v);
				List<Integer> p2 = lpf.getPath(G, v, u);
				
				int r1 = p1.size() / 2 + 1;
				int r2 = p2.size() / 2 + 1;
				int D = Math.max(p1.size(), Math.max(p2.size(), r1+r2));
				if (D < minD) {
					minD = D;
					rmEdge.set(u, v);
					addEdge.set(p1.get(r1-1), p2.get(r2-1));
				}
			}
			System.out.println(minD-1);
			System.out.format("%d %d%n", rmEdge.u + 1, rmEdge.v + 1);
			System.out.format("%d %d%n", addEdge.u + 1, addEdge.v + 1);
			
		}
	}
	
	public static void main(String[] args) throws Exception {
		InputStreamReader isr = new InputStreamReader(System.in);
		BufferedReader in = new BufferedReader(isr);

		new Main(in);
	}

}
