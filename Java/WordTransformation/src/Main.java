import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.StringTokenizer;


public class Main {

	ArrayList<ArrayList<String>> array = new ArrayList<ArrayList<String>>(10);
	
	HashSet<String> usedWords = new HashSet<String>();
	
	int minPath;
	
	public Main(BufferedReader in) throws Exception {
		
		for (int i = 0; i < 10; i++) {
			array.add(new ArrayList<String>());
		}

		while (true) {
			String line = in.readLine();
			if (line.equals("*"))
				break;

			array.get(line.length() - 1).add(line);
		}

		while (true) {
			String line = in.readLine();
			if (line == null || line.length() == 0)
				return;
			
			StringTokenizer st = new StringTokenizer(line);

			String start = st.nextToken();
			String end = st.nextToken();

			minPath = Integer.MAX_VALUE;	
			usedWords.clear();
			usedWords.add(start);
			usedWords.add(end);
			
			findTransform(start, end, 1);
			
			System.out.println (start + " " + end + " " + minPath);
		}
	}
	
	public static void main(String[] args) throws Exception {
		InputStreamReader isr = new InputStreamReader(System.in);
		BufferedReader in = new BufferedReader(isr);
		
		int cases = Integer.parseInt(in.readLine());
		in.readLine();
		
		for (int i = 0; i < cases; i++) {
			new Main(in);
			if (i != (cases - 1))
				System.out.println("");
		}
	}
	
	private void findTransform(String str, String end, int pathSize) {
		
		if (pathSize >= minPath)
			return;
		
		if (diffOne (str, end)) {
			minPath = pathSize;
			return;
		}
		
		ArrayList<String> words = array.get(str.length() - 1);
		for (String word : words) {
			if (usedWords.contains(word))
				continue;
			
			if (diffOne (str, word)) {
				usedWords.add(word);
				findTransform(word, end, pathSize + 1);
				usedWords.remove(word);
				
				if ((pathSize + 1) >= minPath)
					return;
			}
		}
	}
	
	private boolean diffOne (String a, String b) {
		boolean diffOne = false;
		
		if (a.length() != b.length())
			return false;
		
		for (int i = 0; i < a.length(); i++) {
			if (a.charAt(i) != b.charAt(i)) {
				if (diffOne)
					return false;
				else
					diffOne = true;
			}
		}
		
		return diffOne;
	}

}
