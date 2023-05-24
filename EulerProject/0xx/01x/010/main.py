import math
# pypy 0.29ç§’
prime = [2, 3]
i = 4
sum = 5
while i < 2e6:
    isprime = True
    index = 0
    while prime[index] <= math.sqrt(i):
        if i % prime[index] == 0:
            isprime = False
            break
        index += 1
    if isprime:
        prime.append(i)
        sum += i
    i += 1
    # if i % 2e4 == 0:
    #     print(f'{i/2e4:-3}%',end='\r')
print(sum)
