import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Arrays;
import java.util.Locale;
import java.util.StringTokenizer;


class MinShoppingTrip {
	
	public static class Store {
		int node;
		int save;
		
		public Store(int node, int save) {
			this.node = node;
			this.save = save;
		}
	}
	
	private final int[][] D = new int[51][51];
	private int N;
	
	public MinShoppingTrip() {
		for (int i = 0; i < D.length; i++) {
			D[i] = new int[51];
		}
	}
	
	public void reset(int N) {
		this.N = N;
		for (int i = 0; i < D.length; i++) {
			Arrays.fill(D[i], Integer.MAX_VALUE/2);
			D[i][i] = 0;
		}
	}
	
	public void addEdge(int u, int v, int cost) {
		if (cost < D[u][v]) {
			D[u][v] = cost;
			D[v][u] = cost;
		}
	}
	
	public int calculateSaving(Store[] stores, int home) {
		
		// Calculate all pairs shortest path using Floyd Warshall
		for (int k = 0; k < N; k++) {
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					D[i][j] = Math.min(D[i][j], D[i][k] + D[k][j]);
				}
			}
		}
		
		this.home = home;
		this.maxSave = 0;
		int savingPotential = 0;
		for (Store s : stores)
			savingPotential += s.save;
		eulerCycle(home, stores, stores.length, 0, savingPotential);
		return maxSave;
	}
	
	private int home;
	private int maxSave;
	
	private void eulerCycle(int node, Store[] stores, int nStores, int save,
			int savingPotential) {
		
		// Prune
		if ((save + savingPotential) < maxSave)
			return;
		
		int max = save - D[node][home];
		maxSave = Math.max(maxSave, max);
		for (int i = 0; i < nStores; i++) {
			Store s = stores[i];
			swap(stores, i, nStores-1);
			eulerCycle(s.node, stores, nStores-1,
					save+s.save-D[node][s.node], savingPotential - s.save);
			swap(stores, nStores-1, i);
		}
	}
	
	private static void swap(Store[] stores, int i, int j) {
		Store tmp = stores[i];
		stores[i] = stores[j];
		stores[j] = tmp;
	}
}

public class Main {

	public Main(BufferedReader in) throws Exception {
		int scenarios = Integer.parseInt(in.readLine());
		
		MinShoppingTrip mst = new MinShoppingTrip();
		while (scenarios-- > 0) {
			in.readLine();
			
			StringTokenizer st = new StringTokenizer(in.readLine());
			int N = Integer.parseInt(st.nextToken());
			int M = Integer.parseInt(st.nextToken());
			
			mst.reset(N+1);
			for (int m = 0; m < M; m++) {
				st = new StringTokenizer(in.readLine());
				int u = Integer.parseInt(st.nextToken());
				int v = Integer.parseInt(st.nextToken());
				float cost = Float.parseFloat(st.nextToken());
				mst.addEdge(u, v, (int)((cost+0.001)*100));
			}
			
			int P = Integer.parseInt(in.readLine());
			MinShoppingTrip.Store[] stores = new MinShoppingTrip.Store[P];
			for (int p = 0; p < P; p++) {
				st = new StringTokenizer(in.readLine());
				int node = Integer.parseInt(st.nextToken());
				float save = Float.parseFloat(st.nextToken());
				stores[p] = new MinShoppingTrip.Store(node, (int)((save+0.001)*100));
			}
			
			int save = mst.calculateSaving(stores, 0);
			if (save > 0)
				System.out.format("Daniel can save $%.2f%n", (float)save/100);
			else
				System.out.println("Don't leave the house");
		}
	}
	
	public static void main(String[] args) throws Exception {
		Locale.setDefault(Locale.US);
		InputStreamReader is = new InputStreamReader(System.in);
		BufferedReader in = new BufferedReader(is);
		new Main(in);
	}

}
