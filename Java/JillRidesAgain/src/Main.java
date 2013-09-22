import java.io.BufferedReader;
import java.io.InputStreamReader;

public class Main {

	private static class MaxSubarray {
		
		public static class Result {
			public Result(int low, int high, int sum) {
				this.low = low;
				this.high = high;
				this.sum = sum;
			}

			public int low, high;
			public int sum;
		}
		
		private final Result result;
		
		public MaxSubarray(int[] array) {
			result = maxSubArray(array, 0, array.length-1);
		}
		
		public Result getResult() {
			return this.result;
		}
		
		private static Result maxSubArray(int[] array, int low, int high) {
			if (low == high)
				return new Result(low, high, array[low]);
			
			int middle = low + (high - low) / 2;
			
			Result[] res = new Result[3];
			res[0] = maxSubArray(array, low, middle);
			res[1] = maxSpanningArray(array, low, high, middle);
			res[2] = maxSubArray(array, middle + 1, high);
			
			// Filter by sum
			int maxSum = Integer.MIN_VALUE;
			for (int i = 0; i < 3; i++)
				if (res[i].sum > maxSum)
					maxSum = res[i].sum;
			
			int sumInsert = 0;
			for (int i = 0; i < 3; i++)
				if (res[i].sum == maxSum)
					res[sumInsert++] = res[i];
			
			// Filter by length
			int maxLength = Integer.MIN_VALUE;
			for (int i = 0; i < sumInsert; i++) {
				int length = res[i].high - res[i].low; 
				if (length  > maxLength)
					maxLength = length;
			}
			
			int lengthInsert = 0;
			for (int i = 0; i < sumInsert; i++) {
				int length = res[i].high - res[i].low;
				if (length == maxLength)
					res[lengthInsert++] = res[i];
			}
			
			// Return leftmost path
			return res[0];
		}
		
		private static Result maxSpanningArray(int[] array, int low, int high, int middle) {
			
			int sum;
			
			int lSum = Integer.MIN_VALUE;
			sum = 0;
			int sLow = middle;
			for (int i = middle; i >= low; i--) {
				sum += array[i];
				if (sum >= lSum) {
					lSum = sum;
					sLow = i;
				}
			}
			
			int rSum = Integer.MIN_VALUE;
			sum = 0;
			int sHigh = middle + 1;
			for (int i = middle + 1; i <= high; i++) {
				sum += array[i];
				if (sum >= rSum) {
					rSum = sum;
					sHigh = i;
				}
			}
			
			return new Result(sLow, sHigh, lSum + rSum);
		}
	}
	
	public Main(BufferedReader in) throws Exception {
		int b = Integer.parseInt(in.readLine());
		for (int i = 0; i < b; i++) {
			int s = Integer.parseInt(in.readLine());
			int[] array = new int[s-1];
			for (int j = 0; j < s-1; j++) {
				array[j] = Integer.parseInt(in.readLine().trim());
			}
			
			MaxSubarray ms = new MaxSubarray(array);
			if (ms.getResult().sum > 0) {
				System.out.format("The nicest part of route %d is between stops %d and %d%n", i + 1, 
						ms.getResult().low + 1, ms.getResult().high + 2);
			}
			else
				System.out.format("Route %d has no nice parts%n", i + 1);
		}
	}

	public static void main(String[] args) throws Exception {
		InputStreamReader isr = new InputStreamReader(System.in);
		BufferedReader in = new BufferedReader(isr);

		new Main(in);
	}

}
