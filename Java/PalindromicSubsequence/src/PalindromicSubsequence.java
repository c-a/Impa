import java.io.BufferedReader;
import java.io.InputStreamReader;


class Main {
	
	static byte LEFTUP = 1;
	static byte LEFT = 2;
	static byte UP = 3;
	
	Main(BufferedReader in) throws Exception {
		
		String line;
		
		while ((line = in.readLine()) != null) {
			
			if (line.length() == 0)
				break;
			
			char[] c = line.toCharArray();
			int size = line.length();
			
			short[][] C = new short[2][size+1];
			int[][] lexC = new int[2][size+1];
			byte[][] dir = new byte[size+1][size+1];
			
			for (int i = 1; i <= size; i++) {
				
				int imp = (i-1) % 2;
				int impm = i % 2;
				
				for (int j = 1; j <= size; j++) {
					
					int ci = i - 1;
					int cj = size - j;
					
					if (c[ci] == c[cj]) {
						C[imp][j] = (short)(1 + C[impm][j-1]);
						lexC[imp][j] = lexC[impm][j-1] + c[ci];
						dir[i][j] = LEFTUP;
					}
					else {
						if (C[impm][j] > C[imp][j-1]) {
							C[imp][j] = C[impm][j];
							lexC[imp][j] = lexC[impm][j];
							dir[i][j] = UP;
						}
						else if (C[impm][j] < C[imp][j-1]) {
							C[imp][j] = C[imp][j-1];
							lexC[imp][j] = lexC[imp][j-1];
							dir[i][j] = LEFT;
						}
						else {
							C[imp][j] = C[impm][j];
							
							if (lexC[impm][j] <= lexC[imp][j-1]) {
								lexC[imp][j] = lexC[impm][j];
								dir[i][j] = UP;
							}
							else {
								lexC[imp][j] = lexC[imp][j-1];
								dir[i][j] = LEFT;
							}
						}
					}
						
				}
			}
			
			StringBuilder sb = new StringBuilder();
			int i = size;
			int j = size;
			while (true) {
				if (dir[i][j] == LEFTUP) {
					sb.append(c[i - 1]);
					i--;
					j--;
				}
				else if (dir[i][j] == LEFT) {
					j--;
				}
				else if (dir[i][j] == UP){
					i--;
				}
				else
					throw new Exception();
				
				if (i == 0 || j  == 0)
					break;
			}
			System.out.println(sb.toString());
		}
	}
	
	public static void main(String[] args) throws Exception {
		InputStreamReader isr = new InputStreamReader(System.in);
		BufferedReader in = new BufferedReader(isr);
		
		new Main(in);
	}

}
