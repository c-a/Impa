import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.List;
import java.util.StringTokenizer;


public class Main {

	private static class Node {
		public Node parent = null;
		public List<Node> children = new ArrayList<Node>();
		
		public void addChild(Node c) {
			children.add(c);
		}
	}
	
	int evenNodes;
	int oddNodes;
	
	private void countEvenOddNodes(Node n, boolean even) {
		if (even)
			evenNodes += 1;
		else
			oddNodes += 1;
		
		for (Node c : n.children) {
			countEvenOddNodes(c, !even);
		}
	}
	
	public Main(BufferedReader in) throws Exception {
		while (true) {
			int N = Integer.parseInt(in.readLine());
			if (N == 0)
				break;
			
			Node[] nodes = new Node[N];
			for (int i = 0; i < N; i++)
				nodes[i] = new Node();
			
			Node root = null;
			for (int i = 0; i < N; i++) {
				StringTokenizer st = new StringTokenizer(in.readLine());
				int p = Integer.parseInt(st.nextToken().split(":")[0]);
				
				while (st.hasMoreTokens()) {
					int c = Integer.parseInt(st.nextToken());
					nodes[p].addChild(nodes[c]);
					nodes[c].parent = nodes[p];
				}
				
				if (nodes[p].parent == null)
					root = nodes[p];
			}
			
			evenNodes = 0;
			oddNodes = 0;
			countEvenOddNodes(root, true);
			
			int minSum = Math.min(evenNodes+2*oddNodes, 2*evenNodes+oddNodes);
			System.out.println(minSum);
			
			in.readLine();
		}
	}
	
	public static void main(String[] args) throws Exception {
		InputStreamReader isr = new InputStreamReader(System.in);
		BufferedReader in = new BufferedReader(isr);

		new Main(in);
	}

}
