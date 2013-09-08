import java.io.BufferedReader;
import java.io.InputStreamReader;


public class Main {

	public Main(BufferedReader in) throws Exception {
		while (true) {
			String[] lines = in.readLine().split("/");
			if (lines[0].equals("e") && lines[1].equals("o") && lines[2].equals("i"))
				break;
			
			if (countSyllables(lines[0]) != 5)
				System.out.println(1);
			else if (countSyllables(lines[1]) != 7)
				System.out.println(2);
			else if (countSyllables(lines[2]) != 5)
				System.out.println(3);
			else
				System.out.println("Y");
		}
	}
	
	private static int countSyllables(String s) {
		String[] words = s.split(" ");
		int syllables = 0;
		for (int i = 0; i < words.length; i++) {
			for (int j = 0; j < words[i].length(); j++) {
				if (isVowel(words[i].charAt(j)) &&
						(j == 0 || !isVowel(words[i].charAt(j-1))))
					syllables++;
			}
		}
		return syllables;
	}
	
	private static boolean isVowel(char c) {
		switch (c) {
			case 'a':
			case 'e':
			case 'i':
			case 'o':
			case 'u':
			case 'y':
				return true;
				
			default:
				return false;
		}
	}
	
	public static void main(String[] args) throws Exception {
		InputStreamReader isr = new InputStreamReader(System.in);
		BufferedReader in = new BufferedReader(isr);

		new Main(in);
	}

}
