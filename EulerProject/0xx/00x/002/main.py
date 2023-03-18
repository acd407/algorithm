i = j = 1
sum = 0
while j <= 4e6:
    i, j = j, i
    j += i
    if j % 2 == 0:
        sum += j
print(sum)
