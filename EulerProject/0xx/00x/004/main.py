import math
def ispalindrome(x):
    y = str(x)
    for i in range(0,math.floor(len(y)/2)):
        if y[i] != y[-i-1]:
            return False
    return True
table = []
for i in range(999,99,-1):
    for j in range(999,i,-1):
        if ispalindrome(i*j):
            table.append(i*j)
print(max(table))