import numpy
import random
import base64
import sys
import io
import os
import math

def square_and_multiply(H,x,n):
    H=bin(H)
    H=H[2:]
    y=x
    # print(H)
    # print(len(H))
    # print(H[0])
    for i in range(1,len(H)):
        y=(y*y)%n
        if(H[i]=='1'):
            y=(y*x)%n
    return y

def egcd(a, b):
	if a == 0:
		return (b, 0, 1)
	else:
		gcd, x, y = egcd(b % a, a)
		return (gcd, y - (b//a) * x, x)

def mod_inv(a,b):
    gcd,x,y=egcd(a,b)
    if(gcd==1):
        return x
    else:
        return 0


def miller_rabin_test(n,ite=20):
    if(n==2):
        return True
    if(not n & 1):
        return False
    m=n-1
    k=0
    while m % 2==0:
        m//=2
        k+=1
    for i in range(ite):
        a=random.randrange(2,n-2)
        b=square_and_multiply(m,a,n)
        if(b==1 or b==(n-1)):
            continue
        for j in range(k-1):
            b=square_and_multiply(2,b,n)
            if(b==n-1):
                break
        else:
            return False
    return True

def check_prime(p):
    for i in range(0,5):
        if(not miller_rabin_test(p)):
            return False
    return True

def init_1024():
    p=random.getrandbits(1024)
    not_prime=True
    while(not_prime):
        if(check_prime(p)):
            not_prime=False
            break
        p=random.getrandbits(1024)

    q=random.getrandbits(1024)
    while(not_prime or q==p):
        if(check_prime(q)):
            not_prime=False
            break
        q=random.getrandbits(1024)
    return p,q

def GenerateKey(p,q):
    n=p*q
    phi_n=(p-1)*(q-1)
    e=random.randrange(1,phi_n-1)
    r=math.gcd(e,phi_n)
    while(r!=1):
        e=random.randrange(1,phi_n-1)
        r=math.gcd(e,phi_n)

#def init_small():


action = sys.argv[1]
test = random.getrandbits(1024)
print(egcd(7,40))
#print(square_and_multiply(6,7,11))
# print(test)
# print(bin(test)[2:])
#random_key = os.urandom(16)
    
# if(check_prime(9973)):
#     print('true')
# else:
#     print('false')

if(action=='init'):
    if(sys.argv[2]=='1024'):
        mode=sys.argv[2]
        p,q=init_1024()

    if(sys.argv[2]=='small'):
        mode=sys.argv[2]
        #init_small()      





