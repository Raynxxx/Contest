/*
 * HDU 5050 Divided Land
 * Created by Rayn @@ 2014/09/27
 */
import java.io.*;
import java.math.*;
import java.util.*;


public class Main {
	public static Scanner cin = new Scanner(new BufferedInputStream(System.in));
	public static PrintWriter cout = new PrintWriter(new OutputStreamWriter(System.out));
	
	public static void main(String[] args) {
		String buf = new String();
		int T = cin.nextInt();
		int cases = 0;
		while(T-- > 0) {
			buf = cin.next();
			BigInteger L = new BigInteger(buf, 2);
			buf = cin.next();
			BigInteger W = new BigInteger(buf, 2);
			System.out.println("Case #" + (++cases) + ": " + L.gcd(W).toString(2));
		}
	}
}
