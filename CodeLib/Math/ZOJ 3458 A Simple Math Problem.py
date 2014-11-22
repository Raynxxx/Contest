import sys

for line in sys.stdin:
	a, b, n = map(int, line.split())
	m = 2 * (a + b)
	c = 2 if n % 4 == 0 else m
	c *= pow((a - b) * (b - a), n / 4, m)
	print (c - 1) % m
