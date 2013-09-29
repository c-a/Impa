import java.io.BufferedReader;
import java.io.InputStreamReader;

public class Main {

	public Main(BufferedReader in) throws Exception {
		int N = Integer.parseInt(in.readLine().trim());
		for (int i = 0; i < N; i++) {
			String[] s = in.readLine().split(" ");
			Rainfall rf = rainfall(Float.parseFloat(s[0]), Float.parseFloat(s[1]),
					Float.parseFloat(s[2]), Float.parseFloat(s[3]), Float.parseFloat(s[4]));
			System.out.format("%.6f %.6f%n", rf.min, rf.max);
		}
	}
	
	private static class Rainfall {
		public double min;
		public double max;
		
		public Rainfall(double min, double max) {
			this.min = min;
			this.max = max;
		}
	}
	
	private static Rainfall rainfall(float L, float K, float T1, float T2, float H) {
		if (H < L)
			return new Rainfall(H, H);
		
		else if (H == L) {
			double max = computeRainfall(L, K, T1, H + K*T2);
			return new Rainfall(H, max);
		}
		
		else {
			double rain = computeRainfall(L, K, T1, H + K*T2); 
			return new Rainfall(rain, rain);
		}
	}
	
	private static double computeRainfall(double L, double K, double T1, double H) {
		
		double Fmax = (H/T1 + K)/2 + Math.sqrt((H/T1 + K)*(H/T1 + K)/4 - K*L/T1);
		
		return Fmax * T1;
	}
	
	public static void main(String[] args) throws Exception {
		InputStreamReader isr = new InputStreamReader(System.in);
		BufferedReader in = new BufferedReader(isr);

		new Main(in);
	}

}
