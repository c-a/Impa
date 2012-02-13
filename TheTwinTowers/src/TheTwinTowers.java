import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.StringTokenizer;


class Main {
	
	int[] tower1;
	int[] tower2;
	
	Main(BufferedReader in) throws Exception {
		
		for (int towerN = 1;;towerN++) {
			StringTokenizer st;
			int N1, N2;
			
			 st = new StringTokenizer(in.readLine());
			 N1 = Integer.parseInt(st.nextToken());
			 N2 = Integer.parseInt(st.nextToken());
			 
			 if (N1 == 0 || N2 == 0)
				 break;
			 
			 tower1 = new int[N1];
			 st = new StringTokenizer(in.readLine());
			 for (int j = 0; j < N1; j++) {
				 tower1[j] = Integer.parseInt(st.nextToken());
			 }
			 
			 tower2 = new int[N2];
			 st = new StringTokenizer(in.readLine());
			 for (int j = 0; j < N2; j++) {
				 tower2[j] = Integer.parseInt(st.nextToken());
			 }
			 
			 int [][] C = new int[N1 + 1][N2 + 1];
			 
			 for (int i = 0; i < N1; i++) {
				 for (int j = 0; j < N2; j++) {
					 if (tower1[i] == tower2[j])
						 C[i + 1][j + 1] = 1 + C[i][j];
					 else
						 C[i + 1][j + 1] = Math.max(C[i + 1][j], C[i][j + 1]);
				 }
			 }
			 
			 System.out.println("Twin Towers #" + towerN);
			 System.out.println("Number of Tiles : " + C[N1][N2]);
			 System.out.println();
		}
	}
	
	public static void main(String[] args) throws Exception {
		InputStreamReader isr = new InputStreamReader(System.in);
		BufferedReader in = new BufferedReader(isr);
		
		new Main(in);
	}

}
