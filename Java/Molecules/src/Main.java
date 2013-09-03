import java.io.BufferedReader;
import java.io.InputStreamReader;


public class Main {

	public Main(BufferedReader in) throws Exception {
		
		String[] molecules = new String[4];
		
		while (true) {
			molecules[0] = in.readLine();
			if (molecules[0].charAt(0) == 'Q')
				break;
			
			for (int i = 1; i < 4; i++)
				molecules[i] = in.readLine();
			
			System.out.println(maxArea(molecules));
		}
	}
	
	private int maxArea(String[] molecules) {
		
		for (int i = 0; i < molecules.length; i++)
			molecules[i] = molecules[i].substring(1, molecules[i].length()-1);
		int max = 0;
		for (int i = 0; i < 4; i++)
			for (int j = i + 1; j < 4; j++) {
				String h1, h2, v1 = null, v2 = null;
				
				h1 = molecules[i];
				h2 = molecules[j];
				
				for (int k = 0; k < 4; k++) {
					if (i == k || j == k)
						continue;
					
					if (v1 == null)
						v1 = molecules[k];
					else {
						v2 = molecules[k];
						break;
					}
				}
				max = Math.max(max, maxAreaF(h1, h2, v1, v2));
			}
		return max;
	}
	
	private int maxAreaF(String h1, String h2, String v1, String v2) {
		int max = 0;
		
		for (int x1 = 0; x1 < h1.length(); x1++) {
			
			for (int y1 = 0; y1 < v1.length(); y1++) {
				if (h1.charAt(x1) != v1.charAt(y1))
					continue;
				
				// check from left
				for (int x2 = 0; x2 < h1.length(); x2++) {
					if (x2 >= x1 - 1 && x2 <= x1 + 1)
						continue;
					
					for (int y2 = 0; y2 < v2.length(); y2++) {
						if (h1.charAt(x2) != v2.charAt(y2))
							continue;
						
						String subv1, subv2;
						int skipY;
						if (y1 >= y2) {
							int yDiff = y1 - y2;
							skipY = y1 - yDiff;
							subv1 = v1.substring(yDiff, v1.length());
							subv2 = v2.substring(0, v2.length()-yDiff);
						}
						else {
							int yDiff = y2 - y1;
							skipY = y2 - yDiff;
							subv1 = v1.substring(0, v1.length()-yDiff);
							subv2 = v2.substring(yDiff, v2.length());
						}
						
						String lv, rv;
						int xDiff;
						if (x1 >= x2) {
							xDiff = x1 - x2;
							lv = subv2;
							rv = subv1;
						}
						else {
							xDiff = x2 - x1;
							lv = subv1;
							rv = subv2;
						}
						
						for (int y3 = 0; y3 < subv1.length(); y3++) {
							if (y3 >= skipY - 1 && y3 <= skipY + 1)
								continue;
							
							char lc = lv.charAt(y3);
							char rc = rv.charAt(y3);
							for (int x3 = 0; x3 < (h2.length() - xDiff); x3++) {
								if (lc == h2.charAt(x3) && rc == h2.charAt(x3+xDiff)) {
									int height = Math.abs(y3 - skipY);
									int width = xDiff;
									
									max = Math.max(max, (width - 1) * (height - 1));
								}
							}
						}
					}
				}
			}
		}
		return max;
	}
	
	public static void main(String[] args) throws Exception {
		InputStreamReader isr = new InputStreamReader(System.in);
		BufferedReader in = new BufferedReader(isr);

		new Main(in);
	}

}
