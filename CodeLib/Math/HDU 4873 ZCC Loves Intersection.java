/*
** HDU 4873 ZCC Loves Intersection
** Created by Rayn @@ 2014/08/17
*/
import java.util.*;
import java.math.*;

public class Main {
	
	public static Scanner input = new Scanner(System.in);
	
	public static void main(String[] args) {
		BigInteger N;
		int D;
		while(input.hasNext())
		{
			N = input.nextBigInteger();
			D = input.nextInt();
			BigInteger top = N.add(BigInteger.valueOf(4));
			top = top.multiply(top);
			top = top.multiply(BigInteger.valueOf(D)).multiply(BigInteger.valueOf(D-1));
			BigInteger bot = BigInteger.valueOf(18);
			bot = bot.multiply(N.pow(D));
			BigInteger GCD = top.gcd(bot);
			top = top.divide(GCD);
			bot = bot.divide(GCD);
			if(top.equals(BigInteger.ONE)) {
				System.out.println(top);
			}
			else {
				System.out.println(top + "/" + bot);
			}
		}
	}
}