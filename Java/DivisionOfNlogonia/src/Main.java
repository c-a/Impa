import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.StringTokenizer;


public class Main {

	static private class HomeLocationFinder {
		
		public enum Location {
			NORTH_WEST,
			NORTH_EAST,
			SOUTH_WEST,
			SOUTH_EAST,
			BORDER
		}
		
		private final int borderX, borderY;
		
		public HomeLocationFinder(int x, int y) {
			this.borderX = x;
			this.borderY = y;
		}
		
		public Location getLocation(int x, int y) {
			if (x == borderX || y == borderY)
				return Location.BORDER;
			
			if (y < borderY) {
				if (x < borderX)
					return Location.SOUTH_WEST;
				else
					return Location.SOUTH_EAST;
			} else {
				if (x < borderX)
					return Location.NORTH_WEST;
				else
					return Location.NORTH_EAST;
			}
		}
	}
	
	public Main(BufferedReader in) throws IOException {
		while (true) {
			int K = Integer.parseInt(in.readLine());
			if (K == 0)
				break;
			
			StringTokenizer st = new StringTokenizer(in.readLine());
			HomeLocationFinder hlf = new HomeLocationFinder(Integer.parseInt(st.nextToken()),
					Integer.parseInt(st.nextToken()));
			
			for (int i = 0; i < K; i++) {
				st = new StringTokenizer(in.readLine());
				int x = Integer.parseInt(st.nextToken());
				int y = Integer.parseInt(st.nextToken());
				switch (hlf.getLocation(x, y)) {
					case NORTH_WEST:
						System.out.println("NO");
						break;
					case NORTH_EAST:
						System.out.println("NE");
						break;
					case SOUTH_WEST:
						System.out.println("SO");
						break;
					case SOUTH_EAST:
						System.out.println("SE");
						break;
					case BORDER:
						System.out.println("divisa");
				}
			}
		}
	}

	public static void main(String[] args) throws IOException {
		InputStreamReader isr = new InputStreamReader(System.in);
		BufferedReader in = new BufferedReader(isr);

		new Main(in);
	}

}
