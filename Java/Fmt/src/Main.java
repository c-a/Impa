import java.io.BufferedReader;
import java.io.InputStreamReader;


public class Main {
	
	public Main(BufferedReader in) throws Exception {
		
		StringBuilder buf =  new StringBuilder();
		while (true) {
			String line = in.readLine();
			if (line == null) {
				if (buf.length() > 0) {
					System.out.println(buf.toString());
					buf.setLength(0);
				}
				break;
			}
			
			// Empty line
			line = line.replaceAll("\\s+$", "");
			if (line.length() == 0) {
				if (buf.length() > 0) {
					System.out.println(buf.toString());
					buf.setLength(0);
				}
				System.out.println();
				continue;
			}
			
			// Line starts with space, must output last newline
			else if (line.charAt(0) == ' ') {
				if (buf.length() > 0) {
					System.out.println(buf.toString());
					buf.setLength(0);
				}
			}
			
			// Replace newline with space
			if (buf.length() > 0)
				buf.append(" ");
			buf.append(line);
			
			// Output lines until our buffer is less than 72
			while (buf.length() > 72) {
				line = buf.toString();
				
				// Find end of last word that is less than 72
				boolean prevChar = true;
				int end = -1;
				for (int i = 0; i < line.length(); i++) {
					if (line.charAt(i) == ' ') {
						if (prevChar) {
							if (i <= 72) {
								end = i;
							}
							else {
								if (end == -1)
									end = i;
								break;
							}
						}
						prevChar = false;
					}
					else
						prevChar = true;
				}
				if (end == -1)
					end = line.length();
				
				// Replace leading whitespace with a newline if we've got a line longer than 72
				int startWord = 0;
				if (end > 72) {
					while (startWord < line.length() && line.charAt(startWord) == ' ') startWord++;
					if (startWord > 0)
						System.out.println();
				}
				
				// Output line
				System.out.println(line.subSequence(startWord, end));
				
				// Remove spaces after the last word
				while (end < line.length() && line.charAt(end) == ' ') end++;
				buf.delete(0, end);
			}
		}
	}
	
	public static void main(String[] args) throws Exception {
		InputStreamReader isr = new InputStreamReader(System.in);
		BufferedReader in = new BufferedReader(isr);

		new Main(in);
	}

}
