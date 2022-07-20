prime = [2,3]
i = 4
while len(prime)<10001:
    s = True
    for j in prime:
        if i%j == 0:
            s = False
            break
    if s:
        prime.append(i)
    i = i + 1
print(prime[-1])