/*
** HDU 4919 Exclusive or
** Created by Rayn @@ 2014/08/18
*/
import java.util.*;
import java.math.*;

public class Main {
	
	public static Scanner input = new Scanner(System.in);
	public static Map<BigInteger, BigInteger> map = new HashMap<BigInteger, BigInteger>();
	
	public static BigInteger x0 = new BigInteger("0");
	public static BigInteger x1 = new BigInteger("1");
	public static BigInteger x2 = new BigInteger("2");
	public static BigInteger x4 = new BigInteger("4");
	public static BigInteger x6 = new BigInteger("6");
	
	public static BigInteger DFS(BigInteger x) {
		if(map.get(x) != null)
			return map.get(x);
		
		BigInteger ans;
		BigInteger k = x.divide(x2);
		BigInteger dk = DFS(k);
		
		if(x.mod(x2).equals(x0))
		{
			BigInteger dk2 = DFS(k.subtract(x1));
			ans = dk.multiply(x2);
			ans = ans.add(dk2.multiply(x2));
			ans = ans.add(k.multiply(x4));
			ans = ans.subtract(x4);
		}
		else
		{
			ans = dk.multiply(x4);
			ans = ans.add(k.multiply(x6));
		}
		map.put(x, ans);
		return ans;
	}
	public static void main(String[] args) {
		
		map.clear();
		map.put(BigInteger.valueOf(0), BigInteger.valueOf(0));
		map.put(BigInteger.valueOf(1), BigInteger.valueOf(0));
		map.put(BigInteger.valueOf(2), BigInteger.valueOf(0));
		map.put(BigInteger.valueOf(3), BigInteger.valueOf(6));
		
		String str;
		while(input.hasNext())
		{
			str = input.next();
			System.out.println(DFS(new BigInteger(str)));
		}
	}
}