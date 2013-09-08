import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Set;


public class Main {
	
	public Main(BufferedReader in) throws IOException {
		while (true) {
			String a = in.readLine();
			if (a == null)
				break;
			String b = in.readLine();
			String start = in.readLine();

			String z = in.readLine();
			System.out.println(check(a, b, start, z) ? "YES" : "NO");

		}
	}
	
	private boolean check(String a, String b, String start, String z) {
		
		if (start.indexOf(z) != -1)
			return true;
		
		Set<String> set = new HashSet<String>();
		Queue<String> q = new LinkedList<String>();
		
		
		int maxLength = z.length() * Math.max(a.length(), b.length());
		char[] c = new char[maxLength];
		
		if (start.length() <= z.length()) {
			set.add(start);
			q.add(start);
		}
		else {
			for (int j = 0; j <= start.length() - z.length(); j++) {
				String sub = start.substring(j, j+z.length());
				if (!set.contains(sub)) {
					set.add(sub);
					q.add(sub);
				}
			}
		}
		
		while (!q.isEmpty()) {
			String s = q.poll();
			
			int ni = 0;
			for (int i = 0; i < s.length(); i++) {
				String append;
				if (s.charAt(i) == 'a') {
					append = a;
				}
				else {
					append = b;
				}
				
				for (int j = 0; j < append.length(); j++) {
					c[ni++] = append.charAt(j);
				}
			}
			
			String news = new String(c, 0, ni);
			if (news.indexOf(z) != -1)
				return true;
			
			if (news.length() <= z.length()) {
				if (!set.contains(news)) {
					set.add(news);
					q.add(news);
				}
			}
			else {
				for (int j = 0; j <= news.length() - z.length(); j++) {
					String sub = news.substring(j, j+z.length());
					if (!set.contains(sub)) {
						set.add(sub);
						q.add(sub);
					}
				}
			}
		}
		return false;
	}
	
	public static void main(String[] args) throws Exception {
		InputStreamReader isr = new InputStreamReader(System.in);
		BufferedReader in = new BufferedReader(isr);

		new Main(in);
	}

}
