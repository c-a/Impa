import java.io.BufferedReader;
import java.io.InputStreamReader;


public class Main {

	public Main(BufferedReader in) throws Exception {
		while (true) {
			String line = in.readLine();
			if (line == null || line.length() == 0)
				break;
			
			line = line.trim();
			boolean palindrome = palindrome(line);
			
			String rev = reverse(line);
			boolean mirrored = rev != null ? rev.equals(line) : false;
			
			if (palindrome && mirrored)
				System.out.format("%s -- is a mirrored palindrome.%n", line);
			else if (palindrome)
				System.out.format("%s -- is a regular palindrome.%n", line);
			else if (mirrored)
				System.out.format("%s -- is a mirrored string.%n", line);
			else
				System.out.format("%s -- is not a palindrome.%n", line);
			System.out.println();
		}
	}
	
	private static String reverse(String s) {
		char[] alphaReverseTable = {
				'A', 0, 0, 0, '3', 0, 0, 'H', 'I', 'L', 0, 'J',
				'M', 0, 'O', 0, 0, 0, '2', 'T', 'U', 'V', 'W', 'X', 'Y', '5' };
		char[] numericReverseTable = {
				0, '1', 'S', 'E', 0, 'Z', 0, 0, '8', 0 };
		
		StringBuilder sb = new StringBuilder();
		for (char c : s.toCharArray()) {
			char[] table;
			int index;
			
			if (c >= 'A' && c <= 'Z') {
				table = alphaReverseTable;
				index = c - 'A';
			}
			else {
				table = numericReverseTable;
				index = c - '0';
			}
			
			if (table[index] != 0)
				sb.append(table[index]);
			else
				return null;
		}
		
		return sb.reverse().toString();
	}
	
	private static boolean palindrome(String s) {
		for (int i = 0; i < s.length() / 2; i++)
			if (s.charAt(i) != s.charAt(s.length() - i - 1))
				return false;
		return true;
	}

	
	public static void main(String[] args) throws Exception {
		InputStreamReader isr = new InputStreamReader(System.in);
		BufferedReader in = new BufferedReader(isr);

		new Main(in);
	}

}
