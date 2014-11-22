/*
 * ZOJ 3380 Patchouli's Spell Cards
 * Created by Rayn @@ 2014/06/01
 */
import java.math.*;
import java.util.*;

public class Main {
	static BigInteger[][] dp = new BigInteger[105][105];
	static BigInteger[][] c = new BigInteger[105][105];
	static Scanner cin = new Scanner(System.in); 
	
	static void Init() {
		for(int i = 0; i < 104; ++i) 
		{
			c[i][0] = c[i][i] = BigInteger.ONE;
			for(int j = 1; j < i; ++j) 
			{
				c[i][j] = c[i-1][j-1].add(c[i-1][j]);
			}
		}
	}
	public static void main(String[] args) {
		int m, n, l;
		
		Init();
		while(cin.hasNext()) 
		{
			m = cin.nextInt();
			n = cin.nextInt();
			l = cin.nextInt();
			
			BigInteger tot = BigInteger.valueOf(n).pow(m);
			BigInteger ans = BigInteger.ZERO;
			
			if(l > m)
			{
				System.out.println("mukyu~");
				continue;
			}
			else if (l > m/2)
			{
				for(int i = l; i <= m; ++i)
				{
					ans = ans.add(c[m][i].multiply(BigInteger.valueOf(n-1).pow(m-i)));
				}
				ans = ans.multiply(BigInteger.valueOf(n));
				BigInteger gcd = ans.gcd(tot);
				System.out.println(ans.divide(gcd) + "/" + tot.divide(gcd));
				continue;
			}
			
			for(int i = 0; i <= n; ++i)
			{
				for(int j = 0; j <= m; ++j) 
				{
					dp[i][j] = BigInteger.ZERO;
				}
			}
			dp[0][0] = BigInteger.ONE;
			for(int i = 1; i <= n; ++i) 
			{
				for(int j = 1; j <= m; ++j) 
				{
					for(int k = 0; k < l && k <= j; ++k) 
					{
						dp[i][j] = dp[i][j].add(dp[i-1][j-k].multiply(c[m-(j-k)][k]));
					}
				}
			}
			
			for(int i = 1; i <= n; ++i) 
			{
				ans = ans.add(dp[i][m]);
			}
			ans = tot.subtract(ans);
			BigInteger gcd = ans.gcd(tot);
			System.out.println(ans.divide(gcd) + "/" + tot.divide(gcd));
		}
	}
}
