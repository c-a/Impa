import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.BitSet;
import java.util.HashSet;
import java.util.Set;
import java.util.StringTokenizer;


public class Main {

	public Main(BufferedReader in) throws Exception {
		while (true) {
			int N = Integer.parseInt(in.readLine());
			if (N == 0)
				break;
			
			Set<BitSet> boards = new HashSet<BitSet>();
			BitSet board = new BitSet();
			int failMove = -1;
			for (int i = 0; i < 2*N; i++) {
				String s = in.readLine();
				if (failMove != -1)
					continue;
				
				StringTokenizer st = new StringTokenizer(s);
				int x = Integer.parseInt(st.nextToken());
				int y = Integer.parseInt(st.nextToken());
				int bitIndex = (y-1)*N + (x-1);
				board.flip(bitIndex);
				
				if (boards.contains(board)) {
					failMove = i;
				}
				else {
					addBoards(boards, N, board);
				}
			}
			if (failMove != -1) {
				int player = failMove % 2 == 0 ? 2 : 1;
				System.out.format("Player %d wins on move %d%n", player, failMove+1);
			}
			else
				System.out.println("Draw");
		}
	}
	
	private static void addBoards(Set<BitSet> boards, int N, BitSet board) {
		boards.add((BitSet)board.clone());
		
		// Add rotations
		for (int i = 0; i < 3; i++) {
			BitSet b = new BitSet();
			// Rotate by 90 degrees right
			 for (int j = board.nextSetBit(0); j >= 0; j = board.nextSetBit(j+1)) {
			     int x = j % N;
			     int y = j / N;
			     
			     int newX = N - 1 - y;
			     int newY = x;
			     int bitIndex = newY*N + newX;
			     b.set(bitIndex);
			 }
			 boards.add(b);
			 board = b;
		}
	}
	
	public static void main(String[] args) throws Exception {
		InputStreamReader isr = new InputStreamReader(System.in);
		BufferedReader in = new BufferedReader(isr);

		new Main(in);
	}

}
