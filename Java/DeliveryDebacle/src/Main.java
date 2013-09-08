import java.io.BufferedReader;
import java.io.InputStreamReader;


public class Main {
	
	Main(BufferedReader in) throws Exception
	{
		long answers[] = new long[45];
		
		answers[0] = 1;
		for (int i = 0; i < 42; i++) {
			answers[i+1] += answers[i];
			answers[i+2] += 4*answers[i];
			answers[i+3] += 2*answers[i];
		}
		
		int t = Integer.parseInt(in.readLine());
		for (int i = 0; i < t; i++) {
			int length = Integer.parseInt(in.readLine());
			System.out.println(answers[length]);
		}
		
		/*
		int t = Integer.parseInt(in.readLine());
		for (int i = 0; i < t; i++)
		{
			int length = Integer.parseInt(in.readLine());
			
			long nBoxLengths = 0;
			for (int twos = 0; length >= 0; length -= 2, twos++)
				for (int ones = length, threes = 0; ones >= 0; ones -= 3, threes++)
				{
					int slots = ones + twos + threes;
					long permutations = f(slots) / (f(ones)*f(twos)*f(threes));
					
					nBoxLengths += permutations * Math.pow(4,twos) * Math.pow(2,threes);
				}
			
			System.out.println(nBoxLengths);
		} */
	}

	private long f(int n) {
		long res = 1;
		for (int i = 2; i <= n; i++)
			res *= i;
		
		return res;
	}
	
	public static void main(String[] args) throws Exception {
		InputStreamReader isr = new InputStreamReader(System.in);
		BufferedReader in = new BufferedReader(isr);
		
		new Main(in);
	}

}
