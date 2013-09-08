import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.StringTokenizer;


public class Main {

	Main(BufferedReader in) throws Exception
	{
		int N = Integer.parseInt(in.readLine());
		in.readLine();
		for (int i = 0; i < N; i++)
		{
			if (i != 0)
				System.out.println();
			System.out.println("Case #" + (i + 1) + ":");
			while (true)
			{
				String line = in.readLine();
				if (line.length() == 0)
					break;
				
				StringTokenizer st = new StringTokenizer(line);
				StringBuilder sb = new StringBuilder();
				
				int index = 0;
				while (st.hasMoreTokens()) {
					String word = st.nextToken();
					if (index >= word.length())
						continue;
					
					sb.append(word.charAt(index));
					index++;
				}
				System.out.println(sb.toString());
			}
		}
	}

	public static void main(String[] args) throws Exception {
		InputStreamReader isr = new InputStreamReader(System.in);
		BufferedReader in = new BufferedReader(isr);
		
		new Main(in);
	}

}
