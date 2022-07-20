from math import lcm
i = 1
for j in range(2,21):
    i = lcm(i,j)
print(i)