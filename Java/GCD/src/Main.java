import java.io.BufferedReader;
import java.io.InputStreamReader;


public class Main {

	Main(BufferedReader in) throws Exception
	{
		while (true)
		{
			int N = Integer.parseInt(in.readLine());
			if (N == 0)
				break;

			int G = 0;
			for(int j=1; j < N; j++)
				for(int k=j+1; k <= N; k++)
				    G += gcd(j,k);
			System.out.println(G);
		}
	}
	
	
	private int gcd(int a, int b) {
		while (b != 0) {
			int t = b;
			b = a % b;
			a = t;
		}
		return a;
	}
	
	public static void main(String[] args) throws Exception {
		InputStreamReader isr = new InputStreamReader(System.in);
		BufferedReader in = new BufferedReader(isr);
		
		new Main(in);
	}

}
