table = {1, 2, 5, 10, 20, 50, 100, 200}
nt = {0:0, 1:1}
def sol(n):
	if n<=0:
		return 0
	elif n in nt:
		return nt[n]
	else:
		sum = 0 #方法数
		for i in table:
			sum += sol(n-i)
		nt[n] = sum
		return nt[n]
print(sol(200))
for i in nt:
	print(i, nt[i])