import java.io.BufferedReader;
import java.io.InputStreamReader;

class Main {
	
	public static void main(String[] args) throws Exception {
		InputStreamReader isr = new InputStreamReader(System.in);
		BufferedReader in = new BufferedReader(isr);
		
		while (true) {
			String line = in.readLine();
			if (line == null)
				return;
			
			long x = Integer.parseInt(line);
			
			long C = (x*x*x*x + 2*x*x*x + x*x) / 4;
			
			System.out.println(C);
		}
	}
}