import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.HashMap;
import java.util.Map;
import java.util.StringTokenizer;


public class Main {

	private static class Array {
		String name;
		int[] C;
		
		public Array(String s) {
			StringTokenizer st = new StringTokenizer(s);
			
			name = st.nextToken();
			
			int B = Integer.parseInt(st.nextToken());
			int CD = Integer.parseInt(st.nextToken());
			int D = Integer.parseInt(st.nextToken());
			
			int[] L = new int[D+1];
			int[] U = new int[D+1];
			for (int i = 1; i <= D; i++) {
				L[i] = Integer.parseInt(st.nextToken());
				U[i] = Integer.parseInt(st.nextToken());
			}
			
			C = new int[D+1];
			C[D] = CD;
			for (int d = D - 1; d > 0; d--)
				C[d] = C[d+1]*(U[d+1]-L[d+1]+1);
			
			C[0] = B;
			for (int d = 1; d <= D; d++)
				C[0] -= C[d]*L[d];
		}
		
		public int getAddress(int[] indexes) {
			int address = C[0];
			for (int d = 1; d < C.length; d++)
				address += C[d]*indexes[d];
			return address;
		}
	}
	
	public Main(BufferedReader in) throws Exception {
		StringTokenizer st = new StringTokenizer(in.readLine());
		int N = Integer.parseInt(st.nextToken());
		int R = Integer.parseInt(st.nextToken());
		
		Map<String, Array> arrays = new HashMap<String, Array>();
		for (int i = 0; i < N; i++) {
			Array a = new Array(in.readLine());
			arrays.put(a.name, a);
		}
		
		for (int i = 0; i < R; i++) {
			st = new StringTokenizer(in.readLine());
			String name = st.nextToken();
			Array a = arrays.get(name);
			
			int indexes[] = new int[a.C.length];
			for (int d = 1; d < indexes.length; d++)
				indexes[d] = Integer.parseInt(st.nextToken());
			
			System.out.format("%s[%d", name, indexes[1]);
			for (int d = 2; d < indexes.length; d++) {
				System.out.format(", %d", indexes[d]);
			}
			System.out.format("] = %d%n", a.getAddress(indexes));
		}
	}

	public static void main(String[] args) throws Exception {
		InputStreamReader isr = new InputStreamReader(System.in);
		BufferedReader in = new BufferedReader(isr);

		new Main(in);
	}
}
