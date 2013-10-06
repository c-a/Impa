import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Comparator;
import java.util.LinkedList;
import java.util.StringTokenizer;
import java.util.TreeSet;

public class Main {

	private static class MinCacheMisses {
		
		private final LinkedList<Integer>[] objects;
		private TreeSet<Integer> cache;
		
		private int cacheSize;
		
		private final int[] accesses;
		private int nAccesses;
		
		public MinCacheMisses(int maxObjects, int maxCache, int maxAcceses) {
			objects = (LinkedList<Integer>[])new LinkedList[maxObjects];
			for (int i = 0; i < objects.length; i++)
				objects[i] = new LinkedList<Integer>();
			
			// TreeSet that holds the cached in the items in the order such that
			// items that are last accessed (or not at all) are first.
			cache = new TreeSet<Integer>(new Comparator<Integer>() {

				@Override
				public int compare(Integer o0, Integer o1) {
					if (objects[o0].size() == 0 || objects[o1].size() == 0) {
						if (objects[o0].size() == 0 || objects[o1].size() > 0)
							return -1;
						else if (objects[o0].size() > 0 || objects[o1].size() == 0)
							return 1;
						else
							return o0 - o1;
					}
					
					return objects[o1].get(0) - objects[o0].get(0);
				}
			});
			
			accesses = new int[maxAcceses];
		}
		
		public void start(int cacheSize, int nObjects) {
			this.cacheSize = cacheSize;
			cache.clear();
			
			for (int i = 0; i < nObjects; i++)
				objects[i].clear();
			
			nAccesses = 0;
		}
		
		public void addAccess(int object) {
			accesses[nAccesses] = object;
			objects[object].add(nAccesses);
			nAccesses++;
		}
		
		public int finish() {
			int cacheMisses = 0;
			for (int i = 0; i < nAccesses; i++) {
				int a = accesses[i];
				
				if (cache.contains(a)) {
					cache.remove(a);
					objects[a].removeFirst();
					cache.add(a);
					continue;
				}
				
				cacheMisses++;
				if (cache.size() == cacheSize) {
					// Remove element that won't be accessed again for the longest time.
					cache.pollFirst();
				}
				objects[a].removeFirst();
				cache.add(a);
			}
			return cacheMisses;
		}
	}
	public Main(BufferedReader in) throws Exception {
		final MinCacheMisses mcm = new MinCacheMisses(100000, 10000, 100000);
		while (true) {
			String line = in.readLine();
			if (line == null || line.length() == 0)
				break;
			
			StringTokenizer st = new StringTokenizer(line);
			int C = Integer.parseInt(st.nextToken());
			int N = Integer.parseInt(st.nextToken());
			int A = Integer.parseInt(st.nextToken());
			
			mcm.start(C, N);
			for (int a = 0; a < A; a++) {
				mcm.addAccess(Integer.parseInt(in.readLine().trim()));
			}
			
			System.out.println(mcm.finish());
		}
	}
	
	public static void main(String[] args) throws Exception {
		InputStreamReader isr = new InputStreamReader(System.in);
		BufferedReader in = new BufferedReader(isr);

		new Main(in);
	}
}
