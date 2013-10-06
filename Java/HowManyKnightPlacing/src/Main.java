import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.BitSet;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;

public class Main {

	private static class HowManyKnightPlacings {
		
		private int twoBoards = 0;
		Map<Short, List<Short>> transitions = new HashMap<Short, List<Short>>();
		
		public HowManyKnightPlacings() {
			BitSet[] rows = new BitSet[15];
			
			int index = 0;
			for (int i = 0; i < 5; i++) {
				for (int j = i+1; j < 6; j++) {
					BitSet bs = new BitSet();
					bs.set(i); bs.set(j);
					rows[index++] = bs;
				}
			}
			
			BitSet bs = new BitSet(18);
			for (int i = 0; i < 15; i++) {
				setAtOffset(bs, rows[i], 0);
				for (int j = 0; j < 15; j++) {
					setAtOffset(bs, rows[j], 6);
					if (validBoard(bs, 12))
						twoBoards++;
					for (int k = 0; k < 15; k++) {
						setAtOffset(bs, rows[k], 12);
						if (validBoard(bs, 18)) {
							short from = (short)(bs.toLongArray()[0] & 0xfff);
							short to = (short)((bs.toLongArray()[0] >> 6) & 0xfff);
							if (!transitions.containsKey(from))
								transitions.put(from, new ArrayList<Short>());
							transitions.get(from).add(to);
						}
					}
				}
			}
		}
		
		private static void setAtOffset(BitSet to, BitSet from, int offset) {
			 for (int i = 0; i < 6; i++) {
				 to.set(offset + i, from.get(i));
			 }
		}
		
		private static boolean validBoard(BitSet bs, int boardEnd) {
			 for (int i = bs.nextSetBit(0); i >= 0 && i < boardEnd; i = bs.nextSetBit(i+1)) {
				 int ti;
				 
				 ti = i - 2*6 - 1;
				 if ((i % 6) >= 1 && ti >= 0 && bs.get(ti))
					 return false;
				 
				 ti = i - 2*6 + 1;
				 if ((i % 6) <= 4 && ti >= 0 && bs.get(ti))
					 return false;
				 
				 ti = i - 1*6 - 2;
				 if ((i % 6) >= 2 && ti >= 0 && bs.get(ti))
					 return false;
				 
				 ti = i - 1*6 + 2;
				 if ((i % 6) <= 3 && ti >= 0 && bs.get(ti))
					 return false;
				 
				 ti = i + 1*6 - 2;
				 if ((i % 6) >= 2 && ti < boardEnd && bs.get(ti))
					 return false;
				 
				 ti = i + 1*6 + 2;
				 if ((i % 6) <= 3 && ti < boardEnd && bs.get(ti))
					 return false;
				 
				 ti = i + 2*6 - 1;
				 if ((i % 6) >= 1 && ti < boardEnd && bs.get(ti))
					 return false;
				 
				 ti = i + 2*6 + 1;
				 if ((i % 6) <= 4 && ti < boardEnd && bs.get(ti))
					 return false;
			 }
			 return true;
		}
		
		public long getPlacings(long n) {
			if (n == 1)
				return 15;
			else if (n == 2)
				return twoBoards;
			
			Map<Short, Integer> count = new HashMap<Short, Integer>();
			Map<Short, Integer> newCount = new HashMap<Short, Integer>();
			Map<Short, ArrayList<Short>> times = new HashMap<Short, ArrayList<Short>>();
			for (Short from : transitions.keySet()) {
				count.put(from, 1);
				
				List<Short> t = transitions.get(from);
				for (Short to : t) {
					times.put(to, new ArrayList<Short>());
					newCount.put(to, 0);
					if (!count.containsKey(to))
						count.put(to, 0);
				}
			}
			
			Map<String, Long> pSet = new HashMap<String, Long>();
			
			for (long i = 0; i < n - 2; i++) {
				for (Short to : newCount.keySet())
					newCount.put(to, 0);
				
				for (ArrayList<Short> a : times.values())
					a.clear();
				
				for (Short from : count.keySet()) {
					List<Short> t = transitions.get(from);
					if (t == null)
						continue;
					
					for (Short to : t) {
						int placings = newCount.get(to);
						
						placings = (placings + count.get(from)) % 10007;
						newCount.put(to, placings);
						
						times.get(to).add(from);
					}
				}
				
				if (i >= 0) {
					short j = 0;
					Map<Short, Short> index = new HashMap<Short, Short>();
					for (Short to : times.keySet()) {
						if (newCount.get(to) <= 1)
							continue;
						index.put(j++, to);
					}
					
					
					System.out.print("int v[] = { ");
					for (Short to : times.keySet()) {
						if (newCount.get(to) <= 1)
							continue;
						System.out.print(count.get(to) + ", ");
					}
					System.out.println("};");
					
					for (Short to : times.keySet()) {
						if (newCount.get(to) <= 1)
							continue;

						ArrayList<Short> from = times.get(to);
						System.out.print("{ ");
						for (short k = 0; k < index.size(); k++) {
							if (k > 0)
								System.out.print(", ");
							if (from.contains(index.get(k)))
								System.out.print(1);
							else
								System.out.print(0);
						}
						System.out.println("},");
					}
				}
				
				Map<Short, Integer> tmp = count;
				count = newCount;
				newCount = tmp;
			}
			
			int placings = 0;
			for (Integer p : count.values()) {
				placings = (placings + p) % 10007;
			}
			return placings;
		}
	}
	
	private static final int howManyKnightPlacings(long n) {
		if (n == 1)
			return 15;
		else if (n == 2)
			return 69;
		else if (n == 3)
			return 118;
		else if (n == 4)
			return 266;
		else if (n == 5)
			return 746;

		int v[] = { 5, 30, 30, 30, 5, 1, 1, 33, 1, 30, 18, 39, 33, 33, 5, 30, 5, 33, 30, 5, 3, 30, 5, 1, 18, 3, 30, 30, 14, 3, 33, 18, 18, 39, 14, 30, 33, 3 };
		int[] vn = new int[v.length];
		for (long i = 0; i < n - 5; i++) {
			vn[0] = (v[31]) % 10007;
			vn[1] = (v[13] + v[18] + v[21]) % 10007;
			vn[2] = (v[1] + v[12] + v[15]) % 10007;
			vn[3] = (v[26] + v[30] + v[35]) % 10007;
			vn[4] = (v[28]) % 10007;
			vn[5] = (v[37]) % 10007;
			vn[6] = (v[29]) % 10007;
			vn[7] = (v[27] + v[33] + v[36]) % 10007;
			vn[8] = (v[20]) % 10007;
			vn[9] = (v[26] + v[30] + v[35]) % 10007;
			vn[10] = (v[7] + v[19] + v[22]) % 10007;
			vn[11] = (v[0] + v[1] + v[4] + v[12] + v[15] + v[16]) % 10007;
			vn[12] = (v[9] + v[11] + v[17]) % 10007;
			vn[13] = (v[27] + v[33] + v[36]) % 10007;
			vn[14] = (v[34]) % 10007;
			vn[15] = (v[2] + v[3] + v[7]) % 10007;
			vn[16] = (v[24]) % 10007;
			vn[17] = (v[27] + v[33] + v[36]) % 10007;
			vn[18] = (v[26] + v[30] + v[35]) % 10007;
			vn[19] = (v[32]) % 10007;
			vn[20] = (v[14]) % 10007;
			vn[21] = (v[1] + v[12] + v[15]) % 10007;
			vn[22] = (v[10]) % 10007;
			vn[23] = (v[25]) % 10007;
			vn[24] = (v[0] + v[12] + v[16]) % 10007;
			vn[25] = (v[4]) % 10007;
			vn[26] = (v[13] + v[18] + v[21]) % 10007;
			vn[27] = (v[13] + v[18] + v[21]) % 10007;
			vn[28] = (v[5] + v[12] + v[23]) % 10007;
			vn[29] = (v[14]) % 10007;
			vn[30] = (v[9] + v[11] + v[17]) % 10007;
			vn[31] = (v[0] + v[12] + v[16]) % 10007;
			vn[32] = (v[7] + v[19] + v[22]) % 10007;
			vn[33] = (v[2] + v[3] + v[7] + v[14] + v[19] + v[22]) % 10007;
			vn[34] = (v[6] + v[7] + v[8]) % 10007;
			vn[35] = (v[2] + v[3] + v[7]) % 10007;
			vn[36] = (v[9] + v[11] + v[17]) % 10007;
			vn[37] = (v[4]) % 10007;
			
			int[] tmp = v;
			v = vn;
			vn = tmp;
		}
		
		int res = 24;
		for (int i = 0; i < v.length; i++) {
			res = (res + v[i]) % 10007;
		}
		return res;
	}
	
	private static void mmm(int[][] A, int[][] B, int[][] C) {
		for (int i = 0; i < A.length; i++)
			for (int j = 0; j < A.length; j++) {
				C[i][j] = 0;
				for (int k = 0; k < A.length; k++)
					C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % 10007;
			}
	}
	
	private static void mvm(int[][] A, int[] B, int[] C) {
		for (int i = 0; i < A.length; i++) {
			C[i] = 0;
			for (int j = 0; j < A.length; j++)
				C[i] = (C[i] + A[i][j]*B[j]) % 10007;
		}
	}
	
	private static final int howManyKnightPlacingsMatrix(long n) {
		if (n == 1)
			return 15;
		else if (n == 2)
			return 69;
		else if (n == 3)
			return 118;
		else if (n == 4)
			return 266;
		else if (n == 5)
			return 746;
		
		int m[][] = {
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{ 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0},
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0},
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0},
				{ 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{ 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0},
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
				{ 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0},
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0},
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{ 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{ 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{ 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{ 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{ 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
				{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
		};
		int v[] = { 5, 30, 30, 30, 5, 1, 1, 33, 1, 30, 18, 39, 33, 33, 5, 30, 5, 33, 30, 5, 3, 30, 5, 1, 18, 3, 30, 30, 14, 3, 33, 18, 18, 39, 14, 30, 33, 3 };
		int[] vn = new int[v.length];
		for (long i = 0; i < n - 5; i++) {
			mvm(m, v, vn);
			int[] tmp = v;
			v = vn;
			vn = tmp;
		}
		
		int res = 24;
		for (int i = 0; i < v.length; i++) {
			res = (res + v[i]) % 10007;
		}
		return res;
	}
	
	private static class HowManyKnightPlacingsFast {
		
		private final int[][][] M;
		
		public HowManyKnightPlacingsFast(long max) {
			int nMatrices = (int)(Math.log(max) / Math.log(2) + 1);
			
			int m[][] = {
					{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
					{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
					{ 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
					{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0},
					{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
					{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
					{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
					{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0},
					{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
					{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0},
					{ 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
					{ 1, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
					{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
					{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0},
					{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
					{ 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
					{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
					{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0},
					{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0},
					{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
					{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
					{ 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
					{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
					{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
					{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
					{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
					{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
					{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
					{ 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
					{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
					{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
					{ 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
					{ 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
					{ 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
					{ 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
					{ 0, 0, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
					{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
					{ 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
			};
			M = new int[m.length][m.length][nMatrices];
			M[0] = m;
			
			for (int i = 1; i < nMatrices; i++) {
				M[i] = new int[m.length][m.length];
				for (int j = 0; j < m.length; j++)
					M[i][j] = new int[m.length];
				
				mmm(M[i-1], M[i-1], M[i]);
			}
		}
		
		public int getPlacings(long n) {
			if (n == 1)
				return 15;
			else if (n == 2)
				return 69;
			else if (n == 3)
				return 118;
			else if (n == 4)
				return 266;
			else if (n == 5)
				return 746;
			
			n -= 5;
			int v[] = { 5, 30, 30, 30, 5, 1, 1, 33, 1, 30, 18, 39, 33, 33, 5, 30, 5, 33, 30, 5, 3, 30, 5, 1, 18, 3, 30, 30, 14, 3, 33, 18, 18, 39, 14, 30, 33, 3 };
			int[] vn = new int[v.length];
			while (n > 0) {
				int matrix = (int)(Math.log(n) / Math.log(2));
				
				mvm(M[matrix], v, vn);
				int[] tmp = v;
				v = vn;
				vn = tmp;
				
				n -= Math.pow(2, matrix);
			}
			
			int res = 24;
			for (int i = 0; i < v.length; i++) {
				res = (res + v[i]) % 10007;
			}
			return res;
		}
	}
	
	public Main(BufferedReader in) throws Exception {
		final HowManyKnightPlacingsFast hmkp = new HowManyKnightPlacingsFast(1000000000);
		
		int T = Integer.parseInt(in.readLine().trim());
		for (int i = 0; i < T; i++) {
			long n = Long.parseLong(in.readLine().trim());
			System.out.println(hmkp.getPlacings(n));
		}
	}
	
	public static void main(String[] args) throws Exception {
		InputStreamReader isr = new InputStreamReader(System.in);
		BufferedReader in = new BufferedReader(isr);

		new Main(in);
	}

}
