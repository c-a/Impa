import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.StringTokenizer;


public class Main {

	/**
	 * @param args
	 */
	public static void main(String[] args) throws Exception {
		InputStreamReader isr = new InputStreamReader(System.in);
		BufferedReader in = new BufferedReader(isr);
		
		String line = in.readLine();
		int cases = Integer.parseInt(line);
		for (int i = 0; i < cases; i++) {
			line = in.readLine();
			StringTokenizer st = new StringTokenizer(line);
			
			int N = Integer.parseInt(st.nextToken());
			int M = Integer.parseInt(st.nextToken());
			
			long sN = (int)Math.ceil((double)(N-2) / 3);
			long sM = (int)Math.ceil((double)(M-2) / 3);
			
			System.out.println((long)sN * sM);
		}
	}

}
