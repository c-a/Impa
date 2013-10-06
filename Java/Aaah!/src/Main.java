import java.io.BufferedReader;
import java.io.InputStreamReader;


public class Main {

	public Main(BufferedReader in) throws Exception {
		String line1 = in.readLine();
		String line2 = in.readLine();
		
		if (line1.length() >= line2.length())
			System.out.println("go");
		else
			System.out.println("no");
	}
	
	public static void main(String[] args) throws Exception {
		InputStreamReader isr = new InputStreamReader(System.in);
		BufferedReader in = new BufferedReader(isr);

		new Main(in);
	}

}
