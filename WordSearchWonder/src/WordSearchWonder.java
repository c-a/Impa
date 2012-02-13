import java.io.BufferedReader;
import java.io.InputStreamReader;


class Main {
	
	int l;
	char[][] letters;
	
	Main(BufferedReader in) throws Exception {		
		
		l = Integer.parseInt(in.readLine());
		
		letters = new char[l][l];
		for (int i = 0; i < l; i++) {
			
			for (int j = 0; j < l; j++) {
				letters[i][j] = (char)in.read();
			}
			in.readLine();
		}
		
		outer: while (true) {
			String line = in.readLine();
			
			if (line.equals("0"))
				break;
			
			char first = line.charAt(0);
			for (int i = 0; i < l; i++) {
				for (int j = 0; j < l; j++) {
					if (letters[i][j] == first) {
						
						/* Right */
						if (checkWord(line, i, j, 1, 0))
							continue outer;
						
						/* Left */
						else if (checkWord(line, i ,j,-1, 0))
							continue outer;
						
						/* Up */
						else if (checkWord(line, i, j, 0, 1))
							continue outer;
						
						/* Down */
						else if (checkWord(line, i, j, 0, -1))
							continue outer;
						
						/* Up-right */
						else if (checkWord(line, i, j, 1, 1))
							continue outer;
						
						/* Down-right */
						else if (checkWord(line, i, j, 1, -1))
							continue outer;
						
						/* Up-left */
						else if (checkWord(line, i, j, -1, 1))
							continue outer;
						
						/* Down-left */
						else if (checkWord(line, i, j, -1, -1))
							continue outer;
					}
				}
			}
			
			System.out.println("Not found");
		}
	}
	
	private boolean checkWord(String word, int startX, int startY, int deltaX, int deltaY)
	{
		int x = startX;
		int y = startY;
		
		for (int i = 1; i < word.length(); i++) {
			
			x += deltaX;
			y += deltaY;
			
			if (x < 0 || x >= this.l || y < 0 || y >= this.l)
				return false;
			
			if (word.charAt(i) != letters[x][y])
				return false;
		}
		
		System.out.format("%d,%d %d,%d\n", startX + 1, startY + 1, x + 1, y + 1);
		
		return true;
	}
	
	public static void main(String[] args) throws Exception {
		InputStreamReader isr = new InputStreamReader(System.in);
		BufferedReader in = new BufferedReader(isr);
		
		new Main(in);
	}

}
