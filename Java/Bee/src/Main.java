import java.io.BufferedReader;
import java.io.InputStreamReader;


public class Main {

	public Main(BufferedReader in) throws Exception {
		while (true) {
			int N = Integer.parseInt(in.readLine());
			if (N == -1)
				break;
			
			long mp = 0;
			long m = 0;
			for (int i = 0; i < N; i++) {
				long tmp = m;
				m = 1 + m + mp;
				mp = tmp;
			}
			
			System.out.format("%d %d%n", m, m + 1 + mp);
		}
	}

	public static void main(String[] args) throws Exception {
		InputStreamReader isr = new InputStreamReader(System.in);
		BufferedReader in = new BufferedReader(isr);

		new Main(in);
	}
}
