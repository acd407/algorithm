table = []
for i in range(10):
    for j in range(10):
        for k in range(10):
            for m in range(10):
                for n in range(10):
                    for a in range(10):
                        if(100000*a+10000*n+1000*m+100*k+10*i+j==i**5+j**5+k**5+m**5+n**5+a**5):
                            table.append(100000*a+10000*n+1000*m+100*k+10*i+j)
table.remove(0)
table.remove(1)
print(table,"\n",sum(table))