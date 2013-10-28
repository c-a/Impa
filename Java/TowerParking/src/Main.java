import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.StringTokenizer;


public class Main {

	private static class Car implements Comparable<Car> {
		public int floor, position, index;
		
		public Car(int f, int p, int index) {
			this.floor = f;
			this.position = p;
			this.index = index;
		}

		@Override
		public int compareTo(Car arg0) {
			return index - arg0.index;
		}
	}
	
	public Main(BufferedReader in) throws Exception {
		int N = Integer.parseInt(in.readLine());
		Car cars[] = new Car[50*50];
		
		for (int n = 0; n < N; n++) {
			StringTokenizer st = new StringTokenizer(in.readLine());
			int H = Integer.parseInt(st.nextToken());
			int L = Integer.parseInt(st.nextToken());
			
			int floorPos[] = new int[H];
			int nCars = 0;
			
			for (int h = 0; h < H; h++) {
				st = new StringTokenizer(in.readLine());
				for (int l = 0; l < L; l++) {
					int r = Integer.parseInt(st.nextToken());
					if (r != -1) {
						cars[r-1] = new Car(h, l, r);
						nCars++;
					}
				}
			}
			
			long time = 0;
			for (int i = 0; i < nCars; i++) {
				Car c = cars[i];
	
				int turn = Math.abs(floorPos[c.floor] - c.position);
				turn = Math.min(turn, L-turn);

				time += c.floor*2*10 + turn*5;
				floorPos[c.floor] = c.position;
			}
			
			System.out.println(time);
		}
	}
	
	public static void main(String[] args) throws Exception {
		InputStreamReader is = new InputStreamReader(System.in);
		BufferedReader in = new BufferedReader(is);
		new Main(in);
	}

}
