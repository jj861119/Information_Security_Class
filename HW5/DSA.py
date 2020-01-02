import numpy
import random
from random import randrange
import base64
import sys
import io
import os
import math
import hashlib
def SquareAndMultiply(H,x,n):
    H=bin(H)
    H=H[2:]
    y=x
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
    return x%b

def MillerRabinTest(n,ite=5):
    if(n==2):
        return True
    if(n%2==0):
        return False
    m=n-1
    k=0
    while m % 2==0:
        m=m//2
        k+=1
    for i in range(ite):
        a=random.randrange(2,n-2)
        b=SquareAndMultiply(m,a,n)
        if(b==1 or b==(n-1)):
            continue
        for j in range(k-1):
            b=SquareAndMultiply(2,b,n)
            if(b==n-1):
                break
        else:
            return False
    return True

def CheckPrime(p):
    for i in range(0,5):
        if(not MillerRabinTest(p)):
            return False
    return True

def GenPrime(bits):
    p=random.getrandbits(bits-1)
    not_prime=True
    while(not_prime):
        if(CheckPrime(p)):
            not_prime=False
            break
        p=random.getrandbits(bits-1)
    return p

def WriteFile(filename,content):
    with open(f"{filename}",'w') as file:
        file.write(str(content))

def ReadFile(filename):
    with open(f"{filename}",'r') as file:
        return file.read()

def Keygen():
    print("keygen")
    q=GenPrime(160)
    p=(q*random.getrandbits(864))+1
    while(not CheckPrime(p)):
        p=(q*random.getrandbits(864))+1
    
    h=random.randrange(2,p-2)
    while(True):
        if(SquareAndMultiply((p-1)//q,h,p)>1):
            break  
        h=random.randrange(2,p-2)
    alpha=SquareAndMultiply((p-1)//q,h,p)

    d=random.randrange(1,q-1)
    beta=SquareAndMultiply(d,alpha,p)
    return(p,q,alpha,beta,d)

def Sign(message,p,q,alpha,beta,d):
    print("sign")
    kE=random.randrange(1,q-1)
    r=SquareAndMultiply(kE,alpha,p) % q
    sha1 = int(hashlib.sha1(message.encode('utf-8')).hexdigest(),16)
    kE_inverse=mod_inv(kE,q)
    s=((sha1+d*r)*kE_inverse)%q
    return r,s

def Verify(message,r,s,alpha,beta,p,q):
    print("verify")
    w = mod_inv(s,q)
    sha1 = int(hashlib.sha1(message.encode('utf-8')).hexdigest(),16)

    u1 = (w * sha1) % q
    u2 = (w * r) % q

    v = ((SquareAndMultiply(u1,alpha,p)*SquareAndMultiply(u2,beta,p)) % p) % q

    if v==r:
        print("Valid")
    else:
        print("Invalid")

action = sys.argv[1]

if(action=='-keygen'):
    bits=sys.argv[2]
    p,q,alpha,beta,d=Keygen()
    print("p:   ",p)
    print("q:   ",q)
    print("alpha:   ",alpha)
    print("beta:   ",beta)
    print("d:   ",d)
    WriteFile("p",p)
    WriteFile("q",q)
    WriteFile("alpha",alpha)
    WriteFile("beta",beta)
    WriteFile("d",d)
if(action=='-sign'):
    message=sys.argv[2]
    p=int(ReadFile("p"))
    q=int(ReadFile("q"))
    alpha=int(ReadFile("alpha"))
    beta=int(ReadFile("beta"))
    d=int(ReadFile("d"))
    r,s = Sign(message,p,q,alpha,beta,d)
    print("r:   ",r)
    print("s:   ",s)
    WriteFile("r",r)
    WriteFile("s",s)
if(action=='-verify'):
    message=sys.argv[2]
    message=sys.argv[2]
    p=int(ReadFile("p"))
    q=int(ReadFile("q"))
    alpha=int(ReadFile("alpha"))
    beta=int(ReadFile("beta"))
    r=int(ReadFile("r"))
    s=int(ReadFile("s"))
    Verify(message,r,s,alpha,beta,p,q)



