/*
 * ZOJ 2313 Chinese Girls' Amusement
 * Created by Rayn @@ 2014/08/09
 */
import java.util.*;
import java.io.*;
import java.math.*;

public class Main {
	
	public static Scanner input = new Scanner(new BufferedInputStream(System.in));
	
	public static void main(String[] args) {
		int T = input.nextInt();
		while((T--) != 0)
		{
			BigInteger n = input.nextBigInteger();
			BigInteger k = new BigInteger("0");
			if(n.mod(BigInteger.valueOf(2)).equals(BigInteger.ONE))
			{
				k = n.divide(BigInteger.valueOf(2));
			}
			else 
			{
				if(n.mod(BigInteger.valueOf(4)).equals(BigInteger.ZERO))
				{
					k = n.divide(BigInteger.valueOf(2));
					k =	k.subtract(BigInteger.ONE);
				}
				else if(n.mod(BigInteger.valueOf(4)).equals(BigInteger.valueOf(2)))
				{
					n = n.subtract(BigInteger.valueOf(2));
					k = n.divide(BigInteger.valueOf(2));
					k =	k.subtract(BigInteger.ONE);
				}
			}
			System.out.println(k);
			if(T > 0)
				System.out.println();
		}
	}
}
