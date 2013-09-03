import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.StringTokenizer;


public class Main {

	public Main(BufferedReader in) throws Exception {
		
		int N = Integer.parseInt(in.readLine());
		for (int i = 0; i < N; i++) {
			StringTokenizer st = new StringTokenizer(in.readLine());
			
			int L = Integer.parseInt(st.nextToken());
			int W = Integer.parseInt(st.nextToken());
			int omega = Integer.parseInt(st.nextToken());
			
			double radians = (omega*Math.PI)/180;
			double A = L / Math.cos(radians);
			double y = A * Math.sin(radians);
			
			int nCrossings = (int)y / W;
			double yPos;
			if (nCrossings % 2 == 0)
				yPos = y % W;
			else
				yPos = W - (y % W);
			
			double B = Math.sqrt(yPos*yPos + L*L);
			
			System.out.format("%.3f\n", A/B);
		}
	}
	public static void main(String[] args) throws Exception {
		InputStreamReader isr = new InputStreamReader(System.in);
		BufferedReader in = new BufferedReader(isr);

		new Main(in);
	}

}
