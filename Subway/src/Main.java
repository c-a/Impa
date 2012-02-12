import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.PriorityQueue;
import java.util.StringTokenizer;


public class Main {

	private class Node implements Comparable<Node> {
		public int index;
		public int x, y;
		public double cost = Double.POSITIVE_INFINITY; 
		public boolean visited = false;
		
		public Node(int index, int x, int y) {
			this.index = index;
			this.x = x;
			this.y = y;
		}
		
		@Override
		public int compareTo(Node node) {
			return Double.compare(this.cost, node.cost);
		}
	}
	
	private ArrayList<Node> nodes = new ArrayList<Node>();
	private double[][] costs = new double[202][202];
	
	private PriorityQueue<Node> Q = new PriorityQueue<Node>();
	
	public Main(BufferedReader in) throws Exception {
		
		StringTokenizer st;
		int startX, startY, endX, endY;
		Node startNode, endNode;
		
		for (int i = 0; i < 202; i++) {
			for (int j = 0; j < 202; j++)
				costs[i][j] = Double.POSITIVE_INFINITY;
		}
		
		st = new StringTokenizer(in.readLine());
		startX = Integer.parseInt(st.nextToken());
		startY = Integer.parseInt(st.nextToken());
		startNode = new Node(0, startX, startY);
		nodes.add(startNode);
		
		endX = Integer.parseInt(st.nextToken());
		endY = Integer.parseInt(st.nextToken());
		endNode = new Node(1, endX, endY);
		nodes.add(endNode);
		
		costs[1][0] = costs[0][1] = calculateCost(startNode, endNode, false);
		
		while (true) {
			String line = in.readLine();
			if (line == null || line.length() == 0)
				break;
			
			st = new StringTokenizer(line);
			
			Node prevNode = null;
			while (true) {
				int x, y;
				x = Integer.parseInt(st.nextToken());
				if (x == -1)
					break;
				y = Integer.parseInt(st.nextToken());
				
				int i = nodes.size();
				Node node = new Node(i, x, y);
				nodes.add(node);
				
				if (prevNode != null)
					costs[i][i-1] = costs[i-1][i] = calculateCost(node, prevNode, true);
				
				prevNode = node;
			}
		}
		
		for (int i = 0; i < nodes.size(); i++) {
			for (int j = 0; j < nodes.size(); j++) {
				if (i != j && costs[i][j] == Double.POSITIVE_INFINITY)
					costs[i][j] = calculateCost(nodes.get(i), nodes.get(j), false);
			}
		}
		
		startNode.cost = 0;
		Q.add(startNode);
		while (!Q.isEmpty()) {
			
			Node node = Q.poll();
			
			if (node == endNode) {
				System.out.println (Math.round(node.cost / 60));
				return;
			}
			
			if (node.visited)
				continue;
			
			for (int j = 0; j < nodes.size(); j++) {
				
				if (costs[node.index][j] !=  Double.POSITIVE_INFINITY) {
					Node n2 = nodes.get(j);
					double newCost = node.cost + costs[node.index][j];
					
					if (newCost < n2.cost) {
						n2.cost = newCost;
						Q.add(n2);
					}
				}
			}
			
			node.visited = true;
		}
	}
	
	private double calculateCost (Node n1, Node n2, boolean sub) {
		double dist = Math.sqrt(Math.pow(n1.x - n2.x, 2) + Math.pow(n1.y - n2.y, 2));
		
		if (sub)
			return dist * 0.09;
		else
			return dist * 0.36; 
	}
	
	public static void main(String[] args) throws Exception {
		InputStreamReader isr = new InputStreamReader(System.in);
		BufferedReader in = new BufferedReader(isr);
		
		int cases = Integer.parseInt(in.readLine());
		in.readLine();
		
		for (int i = 0; i < cases; i++) {
			new Main(in);
			if (i != (cases - 1))
				System.out.println("");
		}
	}

}
