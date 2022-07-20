import math
prime = [2,3]
def isprime(n):
	if n<=prime[-1]:
		return n in prime
	else:
		i = prime[-1]+2
		while n>prime[-1]:
			j = 0
			while j<math.sqrt(len(prime)):
				s = True
				if i%prime[j]==0:
					s = False
					break
				j = j+1
			if s:
				prime.append(i)
			i = i+1
		return n in prime
def odd(up,down):
	bits=[]
	sign=[]
	up %= down;
	up *= 10;
	bits.append(up//down)
	up %= down
	while up not in sign:
		sign.append(up)
		up *= 10;
		bits.append(up//down)
		up %= down
	bits.pop()
	return bits
maxv = 0
maxi = 0
loop = open("loop.txt",'w')
for i in range(2,1000):
	if isprime(i):
		if len(odd(1,i))>maxv:
			maxv = len(odd(1,i))
			maxi = i
		print(i,len(odd(1,i)),file=loop)
print(maxi,maxv)