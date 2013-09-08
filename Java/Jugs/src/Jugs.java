import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.StringTokenizer;


class Main {
	
	Main(BufferedReader in) throws Exception {
		
		while (true) {
			
			try {
				StringTokenizer st = new StringTokenizer(in.readLine());
				
				int Ca = Integer.parseInt(st.nextToken());
				int Cb = Integer.parseInt(st.nextToken());
				int N = Integer.parseInt(st.nextToken());
				
				if (Cb == N) {
					System.out.println("fill B");
					System.out.println("success");
				}
				else if (Ca == N) {
					System.out.println("fill A");
					System.out.println("success");
				}
				
				else {
					int remainder = N % Ca;
					int B = 0;

					if (remainder != 0) {
						while (B != remainder) {

							/* Fill B */
							int nFills = (Cb - B) / Ca;
							for (int i = 0; i <= nFills; i++) {
								System.out.println("fill A");
								System.out.println("pour A B");
							}

							B = Ca - ((Cb - B) % Ca);
							System.out.println("empty B");
							System.out.println("pour A B");
						}
					}
					
					for (int i = 0; i < (N / Ca); i++) {
						System.out.println("fill A");
						System.out.println("pour A B");
					}

					System.out.println("success");
				}
			}
			catch (Exception e) {
				break;
			}
		}
	}
	
	public static void main(String[] args) throws Exception {
		InputStreamReader isr = new InputStreamReader(System.in);
		BufferedReader in = new BufferedReader(isr);
		
		new Main(in);
	}

}
