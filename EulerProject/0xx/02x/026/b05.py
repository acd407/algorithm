import math
fistr = open("b051626.txt",'r+')
fostr = open("out.txt","r+")
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
while line := fistr.readline():
	if isprime(int(line.split(" ")[0])):
		print(line,file=fostr,end="")
fistr.close()
fostr.close()