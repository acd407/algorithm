j = 1
k = 2
sum = 0
while(j<4e6) do
    if j%2==0 then
        sum = sum + j
    end
    k = k+j
    j = k-j
end
print(sum)