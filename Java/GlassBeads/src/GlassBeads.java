import java.io.BufferedReader;
import java.io.InputStreamReader;


class Main {

	char[] neck;
	int    neckSize;
	
	Main(BufferedReader in) throws Exception {
		String line = in.readLine();
		
		neck = line.toCharArray();
		neckSize = line.length();
		
		int wStart = 0;
		int wEnd = 0;
		outer : while (true) {
			
			int next = (wEnd + 1) % neckSize;
			
			if (next == wStart)
				break;
			
			if (neck[next] < neck[wStart]) {
				wStart = next;
				wEnd = next;
			}
			
			else if (neck[next] == neck[wStart] &&
					wStart != wEnd)
			{
				int i = next;
				int j = wStart;
				while (neck[i] == neck[j])
				{
					i = (i + 1) % neckSize;
					j = (j + 1) % neckSize;
					
					if (i == next)
						break outer;
				}
				if (neck[i] < neck[j])
				{
					wStart = next;
					wEnd = next;
				}
				else
					wEnd = next;
			}
			else
				wEnd = next;
		}
		
		System.out.println(wStart + 1);
	}
	
	
	public static void main(String[] args) throws Exception {
		InputStreamReader isr = new InputStreamReader(System.in);
		BufferedReader in = new BufferedReader(isr);
		
		int cases = Integer.parseInt(in.readLine());
		for (int i = 0; i < cases; i++) {
			new Main(in);
		}
	}

}
