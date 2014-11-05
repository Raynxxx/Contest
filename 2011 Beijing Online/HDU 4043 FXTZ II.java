/*
** HDU 4043 FXTZ II
** Created by Rayn @@ 2014/11/04
*/
import java.math.*;
import java.util.*;

public class Main {
	public static BigInteger[] top = new BigInteger[510];
	public static BigInteger[] bot = new BigInteger[510];
	private static Scanner cin;
	
	public static void Init() {
		top[1] = BigInteger.valueOf(1);
        bot[1] = BigInteger.valueOf(2);
        for(int i = 2; i <= 500; ++i) {
        	top[i] = top[i - 1].multiply(BigInteger.valueOf(2 * i - 1));
        	bot[i] = bot[i - 1].multiply(BigInteger.valueOf(2)).multiply(BigInteger.valueOf(i));
        }
	}
    public static void main(String[] args) {
        Init();
        cin = new Scanner(System.in);
        int C = cin.nextInt();
        while(C-- > 0) {
        	int n = cin.nextInt();
        	BigInteger g = top[n].gcd(bot[n]);
        	BigInteger f1 = top[n].divide(g);
        	BigInteger f2 = bot[n].divide(g);
        	System.out.println(f1 + "/" + f2);
        }
    }
}
