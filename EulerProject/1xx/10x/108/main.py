# 1/x + 1/y = 1/n
# x,y,n are all integer
# x*y / (x + y)=n
# x*y = n*x + n*y
# let x --> x + n
# let y --> y + n
# x*y+n(x+y)+n^2 = n(x+y) + 2*n^2
# x*y = n^2
# x > -n, y > -n
# so, search the factor of n^2, including negative
# ex:
#   n = 4
#   16 has factors : 2 4 -2
#   let s = the number of factors below n
#   then the ans = 2*s+1
# now we need 2s+1>1000
# so s>=500
prime = [2]
# 传入 n 而不是 n^2
def retfactors(n):
	factors = {}
	i = 3
	while prime[-1]<n*n:
		s = True
		for j in prime:
			if i%j==0:
				s = False
				break
		if s:
			prime.append(i)
		i = i+1
	print("prime table over", flush=True)
	base = 0
	while n!=1:
		for j in prime[base:]:
			if n%j==0:
				n /= j
				if j in factors:
					factors[j] = factors[j] + 1;
				else:
					factors[j] = 1
				base = j
				break
	return factors
sum = 0
print(retfactors(48))

