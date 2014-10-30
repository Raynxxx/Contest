/*
 * HDU 4927 Series 1
 * Created by Rayn @@ 2014/08/09
 */
import java.util.*;
import java.math.*;

public class Main {
	
	public static Scanner input = new Scanner(System.in);
	public static BigInteger[] C = new BigInteger[3010];
	public static BigInteger[] arr = new BigInteger[3010];
	
	public static void main(String[] args) {
		int T = input.nextInt();
		
		while((T--) != 0)
		{
			int n = input.nextInt();
			for(int i = 0; i < n; ++i)
			{
				arr[i] = input.nextBigInteger();
			}
			if(n == 1)
			{
				System.out.println(arr[0]);
				continue;
			}
			BigInteger ans = new BigInteger("0");
			C[0] = BigInteger.valueOf(1);
			for(int i = 1; i < n; ++i)
			{
				C[i] = C[i-1].multiply(BigInteger.valueOf(n-i));
				C[i] = C[i].divide(BigInteger.valueOf(i));
			}
			int flag = 1;
			for(int i = n-1; i >= 0; --i)
			{
				if(flag == 1)
					ans = ans.add(arr[i].multiply(C[i]));
				else
					ans = ans.subtract(arr[i].multiply(C[i]));
				flag ^= 1;
			}
			System.out.println(ans);
		}
	}
}
