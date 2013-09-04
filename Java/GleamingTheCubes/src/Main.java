import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.StringTokenizer;


public class Main {

	private static class Cube {
		int x1, x2;
		int y1, y2;
		int z1, z2;
		
		public Cube(BufferedReader in) throws Exception {
			final StringTokenizer st = new StringTokenizer(in.readLine());
			x1 = Integer.parseInt(st.nextToken());
			y1 = Integer.parseInt(st.nextToken());
			z1 = Integer.parseInt(st.nextToken());
			int width = Integer.parseInt(st.nextToken());
			x2 = x1 + width;
			y2 = y1 + width;
			z2 = z1 + width;
		}
		
		public Cube(int x1, int x2, int y1, int y2, int z1, int z2) {
			this.x1 = x1;
			this.x2 = x2;
			this.y1 = y1;
			this.y2 = y2;
			this.z1 = z1;
			this.z2 = z2;
		}
		
		public Cube intersection(Cube c) {
			int xStart = Math.max(x1, c.x1);
			int xEnd = Math.min(x2, c.x2);
			if (xStart >= xEnd)
				return null;
			
			int yStart = Math.max(y1, c.y1);
			int yEnd = Math.min(y2, c.y2);
			if (yStart >= yEnd)
				return null;
			
			int zStart = Math.max(z1, c.z1);
			int zEnd = Math.min(z2, c.z2);
			if (zStart >= zEnd)
				return null;
			
			return new Cube(xStart, xEnd, yStart, yEnd, zStart, zEnd);
		}
	}
	public Main(BufferedReader in) throws Exception {
		while (true) {
			int nCubes = Integer.parseInt(in.readLine());
			if (nCubes == 0)
				break;
			
			Cube c = new Cube(in);
			for (int i = 1; i < nCubes; i++) {
				Cube c2 = new Cube(in);
				if (c != null)
					c = c.intersection(c2);
			}

			if (c != null)
				System.out.println((c.x2-c.x1)*(c.y2-c.y1)*(c.z2-c.z1));
			else
				System.out.println(0);
		}
	}
	
	public static void main(String[] args) throws Exception {
		InputStreamReader isr = new InputStreamReader(System.in);
		BufferedReader in = new BufferedReader(isr);

		new Main(in);
	}

}
