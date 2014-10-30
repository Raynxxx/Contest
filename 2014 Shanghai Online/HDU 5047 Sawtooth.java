/*
 * HDU 5047 Sawtooth
 * Created by Rayn @@ 2014/09/27
 */
import java.io.*;
import java.math.*;

public class Main {
	public static BufferedReader cin = new BufferedReader(new InputStreamReader(System.in));
    public static BufferedWriter cout = new BufferedWriter(new OutputStreamWriter(System.out));
	public static BigInteger x8 = new BigInteger("8");
	public static BigInteger x7 = new BigInteger("7");
	
	public static void main(String[] args) throws Exception {
		int T = Integer.parseInt(cin.readLine());
		int cases = 0;
		while(T-- > 0) {
			BigInteger n = new BigInteger(cin.readLine());
			BigInteger ret = n.multiply(n).multiply(x8);
			ret = ret.subtract(n.multiply(x7)).add(BigInteger.ONE);
			cout.write("Case #" + (++cases) + ": " + ret);
			cout.newLine();
		}
		cout.flush();
	}
}
