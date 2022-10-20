isprime_list = [2];
def isprime(n):
    if n <= isprime_list[-1]:
        if n in isprime_list:
            return True;
        else:
            return False;
    else:
        for i in isprime_list:
            if n % i == 0:
                return False;
        isprime_list.append(n);
        return True;

n = 1;
total = 0;
while n < 1e6:
    if isprime(n*n+1) and isprime(n*n+3) and isprime(n*n+7) and isprime(n*n+9) and isprime(n*n+13) and isprime(n*n+27):
        print(n);
        total = total + n;
    n = n + 1;
print(total);