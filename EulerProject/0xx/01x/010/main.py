#太慢了510秒
prime = [2,3]
i = 4
sum = 5
while i < 2e6:
    s = True
    for j in prime:
        if i%j==0:
            s = False
            break
    if s:
        prime.append(i)
        sum += i
    i = i + 1
    if i%1e4==0:
        print(i/1e4)
print(sum)