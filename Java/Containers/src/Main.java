import java.io.BufferedReader;
import java.io.InputStreamReader;

public class Main {

	public Main(BufferedReader in) throws Exception {
		int testCases = Integer.parseInt(in.readLine());
		
		for (int c = 0; c < testCases; c++) {
			long containers = Long.parseLong(in.readLine());
			long stacks = (containers + 4) / 5;
			
			long width = Long.MAX_VALUE;
			long height = Long.MAX_VALUE;
			long area = Long.MAX_VALUE;
			
			long approximation = (long)Math.sqrt(stacks);
			
			long hn = Math.max(approximation - 10000000, 1);
			long hmax = Math.min(approximation + 10000000, stacks);
			for (hn = 1; hn <= hmax; hn++) {
				long vn = stacks / hn;
				while (hn*vn < stacks)
					vn++;
				
				long w, h;

				w = 44*hn + 4;
				h = 10*vn + 2;
				if (h*w < area ||
						(h*w == area && Math.abs(w-h) < Math.abs(width-height))) {
					width = w;
					height = h;
					area = w*h;
				}
			}
			
			System.out.format("%d X %d = %d%n", Math.max(width, height),
					Math.min(width, height), width*height);
		}
	}
	
	public static void main(String[] args) throws Exception {
		InputStreamReader is = new InputStreamReader(System.in);
		BufferedReader in = new BufferedReader(is);
		new Main(in);
	}

}
