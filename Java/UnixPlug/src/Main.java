import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.HashMap;
import java.util.StringTokenizer;


public class Main {
	
	private HashMap<String, Integer> receptables = new HashMap<String, Integer>();
	
	private class Adapter {
		String from, to;
		
		public Adapter(String from, String to) {
			this.from = from;
			this.to = to;
		}
	}
	public Main(BufferedReader in) throws Exception {
		
		int n = Integer.parseInt(in.readLine());
		for (int i = 0; i < n; i++) {
			String rec = in.readLine();
			
			Integer nRec = receptables.get(rec);
			if (nRec != null)
				receptables.put(rec, nRec + 1);
			else
				receptables.put(rec,  1);
		}
		
		int m = Integer.parseInt(in.readLine());
		for (int i = 0; i < m; i++) {
			StringTokenizer st = new StringTokenizer(in.readLine());
			
			in.readLine();
			
			String plug = st.nextToken();
			Integer nRec = receptables.get(plug);
			if (nRec != null) {
				if (nRec > 1)
					receptables.put(plug, nRec - 1);
				else
					receptables.remove(plug);
			}
			
			plugs.add(plug);
		}
		
		int k = Integer.parseInt(in.readLine());
		for (int i = 0; i < k; i++) {
			StringTokenizer st = new StringTokenizer(in.readLine());
			String to = st.nextToken();
			String from = st.nextToken();
			
			adapters.add(new Adapter(from, to));
		}
		
		
		while (adapters.size() > 0) {
			Integer nRec = receptables.get(key)
		}
	}
	
	private extendAdapters(List<Adapters> adapters) {
		while (true) {
			for (int i = 0; i < adapters.size(); i++) {
				
			}
		}
	}
	
	public static void main(String[] args) {
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
