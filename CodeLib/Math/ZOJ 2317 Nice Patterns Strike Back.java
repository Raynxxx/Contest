/*
** ZOJ 2317 Nice Patterns Strike Back
** Created by Rayn @@ 2014/08/09
*/
import java.io.*;
import java.math.*;
import java.util.*;

class Martix {
	public int d;
	public long[][] a;
	
	public Martix(int d) {
		this.d = d;
		a = new long[d][d];
	}
	public Martix multiply(Martix b, long p) {
		Martix ret = new Martix(d);
		for (int i = 0; i < d; ++i) {
			for (int j = 0; j < d; ++j) {
				for (int k = 0; k < d; ++k) {
					ret.a[i][j] += this.a[i][k] * b.a[k][j];
				}
				ret.a[i][j] %= p;
			}
		}
		return ret;
	}
}

public class Main {
	
	private static Scanner cin;
	//private static FileInputStream fin;
	
	public static long Solve(BigInteger n, int m, long p) {
		int d = 1 << m;
		Martix a = new Martix(d);
		for (int i = 0; i < d; ++i) {
			for (int j = 0; j < d; ++j) {
				int x = i, y = j;
				for (int k = 1; k < m; ++k) {
					if ((x & 3) == (y & 3) && ((x & 3) == 0 || (y & 3) == 3)) {
						x = -1;
						break;
					} else {
						x >>= 1;
						y >>= 1;
					}
				}
				a.a[i][j] = (x == -1)? 0 : 1;
			}
		}
		Martix s = new Martix(d);
		for (int i = 0; i < d; ++i) {
			s.a[i][i] = 1;
		}
		for(int i = n.bitLength()-1; i >= 0; --i) {
			s = s.multiply(s, p);
			if(n.testBit(i)) {
				s = s.multiply(a, p);
			}
		}
		long ret = 0;
		for (int i = 0; i < d; ++i) {
			for (int j = 0; j < d; ++j) {
				ret += s.a[i][j];
			}
		}
		return ret % p;
	}
	public static void main(String[] args) {
		//fin = new FileInputStream("D:/Code/in.txt");
		//System.setIn(fin);
		cin = new Scanner(new BufferedInputStream(System.in));
		
		int T = cin.nextInt();
		while((T--) != 0)
		{
			BigInteger n = cin.nextBigInteger();
			int m = cin.nextInt();
			int p = cin.nextInt();
			System.out.println(Solve(n.subtract(BigInteger.ONE), m, p));
			if(T > 0)
				System.out.println();
		}
	}
}
