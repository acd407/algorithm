import math

i = 600851475143
fact = []
for j in range(2, math.floor(math.sqrt(i))):
    if i % j == 0:
        i /= j
        fact.append(j)
        j = 2
print(max(fact))
