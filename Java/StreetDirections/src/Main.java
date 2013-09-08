import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.LinkedList;
import java.util.Queue;
import java.util.StringTokenizer;


public class Main {

	private static class Corner {
		public static class Neighbor {
			public Corner c;
			public boolean to = false;
			public boolean from = false;
			
			public Neighbor(Corner c) {
				this.c = c;
			}
		}
		public int index = 0;
		
		public Neighbor neighbors[] = new Neighbor[4];
		public int nNeighbors = 0;
		
		public Corner(int index) {
			this.index = index;
		}
	}

	private boolean[] marked;
	private int cnt;
	private int[] pre;
	private int[] low;
	
	Main(BufferedReader in) throws Exception
	{
		for (int caseN = 1;; caseN++)
		{
			StringTokenizer st = new StringTokenizer(in.readLine());
			int n = Integer.parseInt(st.nextToken());
			int m = Integer.parseInt(st.nextToken());
			if (n == 0 || m == 0)
				break;
			
			Corner[] corners = new Corner[n+1];
			for (int i = 1; i <= n; i++)
				corners[i] = new Corner(i);

			for (int i = 0; i < m; i++) {
				st = new StringTokenizer(in.readLine());
				int n1 = Integer.parseInt(st.nextToken());
				int n2 = Integer.parseInt(st.nextToken());
				
				Corner c1 = corners[n1];
				Corner c2 = corners[n2];
				c1.neighbors[c1.nNeighbors++] = new Corner.Neighbor(c2);
				c2.neighbors[c2.nNeighbors++] = new Corner.Neighbor(c1);
			}
			
			marked = new boolean[n+1];
	        for (int i = 1; i < n + 1; i++)
	        	if (marked[i] == false)
	        		dfs(corners[i]);
	        
			low = new int[n+1];
	        pre = new int[n+1];
	        cnt = 0;
	        for (int v = 0; v <= n; v++) low[v] = -1;
	        for (int v = 0; v <= n; v++) pre[v] = -1;
	        
	        for (int i = 1; i <= n; i++)
	        	if (pre[i] == -1)
	        		addBridges(corners[i], corners[i]);
	        
			System.out.println(caseN + "\n");

			for (int i = 1; i <= n; i++) {
				Corner c = corners[i];
				for (int j = 0; j < c.nNeighbors; j++) {
					if (c.neighbors[j].to)
						System.out.println(c.index + " " + c.neighbors[j].c.index);
				}
			}
			System.out.println("#");
		}
	}
	
	private void dfs(Corner c) {
		marked[c.index] = true;
		
		for (int i = 0; i < c.nNeighbors; i++) {

			Corner.Neighbor n = c.neighbors[i];

			// If edge not added at all 
			if (!n.to && !n.from) {
				n.to = true;
				setFrom(c, n.c);
			}

			if (marked[n.c.index] == false)
				dfs(n.c);
		}
	}
	
	private void addBridges(Corner p, Corner c) {
		pre[c.index] = cnt++;
		low[c.index] = pre[c.index];
		
		for (int i = 0; i < c.nNeighbors; i++) {
			
			Corner.Neighbor n = c.neighbors[i];
			if (n.to == false)
				continue;
			
			if (pre[n.c.index] == -1) {
				addBridges(c, n.c);
				low[c.index] = Math.min(low[c.index], low[n.c.index]);
				if (low[n.c.index] == pre[n.c.index]) {
					// bridge, need to add back edge
					n.from = true;
					setTo(c, n.c);
				}
			}
			
			// update low number - ignore reverse of edge leading to c
			else if (n.c != p)
				low[c.index] = Math.min(low[c.index], pre[n.c.index]);
		}
	}
	
	private static void setFrom(Corner from, Corner to) {
		for (int j = 0; j < to.nNeighbors; j++) {
			if (to.neighbors[j].c == from) {
				to.neighbors[j].from = true;
				break;
			}
		}
	}

	private static void setTo(Corner to, Corner from) {
		for (int j = 0; j < from.nNeighbors; j++) {
			if (from.neighbors[j].c == to) {
				from.neighbors[j].to = true;
				break;
			}
		}
	}
	
	/*
	Main(BufferedReader in) throws Exception
	{
		for (int caseN = 1;; caseN++)
		{
			StringTokenizer st = new StringTokenizer(in.readLine());
			int n = Integer.parseInt(st.nextToken());
			int m = Integer.parseInt(st.nextToken());
			if (n == 0 || m == 0)
				break;
			
			Corner[] corners = new Corner[n+1];
			for (int i = 1; i <= n; i++)
				corners[i] = new Corner(i);

			for (int i = 0; i < m; i++) {
				st = new StringTokenizer(in.readLine());
				int n1 = Integer.parseInt(st.nextToken());
				int n2 = Integer.parseInt(st.nextToken());
				
				Corner c1 = corners[n1];
				Corner c2 = corners[n2];
				c1.neighbors[c1.nNeighbors++] = new Corner.Neighbor(c2);
				c2.neighbors[c2.nNeighbors++] = new Corner.Neighbor(c1);
			}
			
			boolean[] visited = new boolean[n+1];
			boolean[] marked = new boolean[n+1];
			for (int i = 1; i <= n; i++) {
				if (visited[i])
					continue;
				
				Corner c = corners[i];
				while (c != null) {
					visited[c.index] = true;
					dfs(c, corners, marked);
					
					Corner nextCorner = null;
					for (int j = 0; j < c.nNeighbors; j++) {
						if (marked[c.neighbors[j].c.index])
							continue;
						
						if (!c.neighbors[j].from) {
							c.neighbors[j].to = true;
							setFrom(c, c.neighbors[j].c);
							nextCorner = c.neighbors[j].c;
							break;
						}
					}
					if (nextCorner != null) {
						c = nextCorner;
						continue;
					}
					
					for (int j = 0; j < c.nNeighbors; j++) {
						if (marked[c.neighbors[j].c.index])
							continue;
						
						if (!c.neighbors[j].to) {
							c.neighbors[j].to = true;
							setFrom(c, c.neighbors[j].c);
							nextCorner = c.neighbors[j].c;
							break;
						}
					}
					c = nextCorner;
				}
			}
			
			System.out.println(caseN + "\n");

			for (int i = 1; i <= n; i++) {
				Corner c = corners[i];
				for (int j = 0; j < c.nNeighbors; j++) {
					if (c.neighbors[j].to)
						System.out.println(c.index + " " + c.neighbors[j].c.index);
				}
			}
			System.out.println("#");
		}
	}
	
	private void dfs(Corner source, Corner[] corners, boolean[] marked) {
		for (int i = 0; i < marked.length; i++)
			marked[i] = false;
		
		LinkedList<Corner> q = new LinkedList<Corner>();
		q.add(source);
		while (!q.isEmpty()) {
			Corner c = q.poll();
			marked[c.index] = true;
			for (int i = 0; i < c.nNeighbors; i++) {
				if (marked[c.neighbors[i].c.index] == false && c.neighbors[i].to == true)
					q.addFirst(c.neighbors[i].c);
			}
		}
	}
	*/
	
	public static void main(String[] args) throws Exception {
		InputStreamReader isr = new InputStreamReader(System.in);
		BufferedReader in = new BufferedReader(isr);
		
		new Main(in);
	}
}
