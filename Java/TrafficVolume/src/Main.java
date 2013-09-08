import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.StringTokenizer;


public class Main {

	Main(BufferedReader in) throws Exception
	{
		while (true)
		{
			String line = in.readLine();
			StringTokenizer st = new StringTokenizer(line);
			
			int L = Integer.parseInt(st.nextToken());
			int f = Integer.parseInt(st.nextToken());
			if (L == 0 ||f == 0)
				break;
			
			double v = Math.sqrt(2*f*L);
			System.out.format("%.8f %.8f\n", v, 3600/(L/v + v/(2*f)));
		}
	}
	public static void main(String[] args) throws Exception {
		InputStreamReader isr = new InputStreamReader(System.in);
		BufferedReader in = new BufferedReader(isr);
		
		new Main(in);
	}

}
