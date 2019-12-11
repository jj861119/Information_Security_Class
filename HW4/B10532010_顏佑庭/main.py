import numpy
import random
from random import randrange
import base64
import sys
import io
import os
import math
sys.setrecursionlimit(100000)
def square_and_multiply(H,x,n):
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

def miller_rabin_test(n,ite=5):
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

    not_prime=True
    q=random.getrandbits(1024)
    while(not_prime):
        if(check_prime(q)):
            not_prime=False
            break
        q=random.getrandbits(1024)
    return p,q

def GenerateKey(p,q):
    n=p*q
    phi_n=(p-1)*(q-1)
    while(True):
        e=random.randrange(1,phi_n)
        if(math.gcd(e,phi_n)==1):
            break
    d=mod_inv(e,phi_n)
    return n,e,d

def RSA_encrypt(plaintext,n,e):
    ciphertext = square_and_multiply(e, plaintext, n)
    return ciphertext

def RSA_decrypt(p,q,d,ciphertext):
    Xp=ciphertext%p
    Xq=ciphertext%q
    Dp=d%(p-1)
    Dq=d%(q-1)
    Yp=square_and_multiply(Dp,Xp,p)
    Yq=square_and_multiply(Dq,Xq,q)
    Cp=mod_inv(p,q)
    t=Cp
    u=((Yq-Yp)*t)%q
    plaintext = Yp+p*u
    return plaintext


def WriteFile(filename,content):
    with open(f"{filename}",'w') as file:
        file.write(str(content))

def ReadFile(filename):
    with open(f"{filename}",'r') as file:
        return file.read()

action = sys.argv[1]


if(action=='init'):
    print("init")
    p,q=init_1024()
    n,e,d=GenerateKey(p,q)
    WriteFile("p",p)
    WriteFile("q",q)
    WriteFile("n",n)
    WriteFile("e",e)
    WriteFile("d",d)
    print('p:',p)
    print('q:',q)
    print('n:',n)
    print('e:',e)
    print('d:',d)
if(action=='encrypt'):
    print("encrypt")
    plaintext = int.from_bytes(bytes(sys.argv[2],encoding='ascii'),byteorder='big')
    plaintext_length=len(sys.argv[2])
    n=int(ReadFile("n"))
    e=int(ReadFile("e"))
    ciphertext = RSA_encrypt(plaintext, n, e)
    WriteFile("ciphertext",ciphertext)
    WriteFile("plaintext_length",plaintext_length)
    print('ciphertext:',ciphertext)
if(action=='decrypt'):
    print("decrypt")
    ciphertext= int(ReadFile("ciphertext"))
    d=int(ReadFile("d"))
    p=int(ReadFile("p"))
    q=int(ReadFile("q"))
    plaintext_length=int(ReadFile("plaintext_length"))
    plaintext = RSA_decrypt(p,q,d,ciphertext)
    plaintext=plaintext.to_bytes(plaintext_length,byteorder='big')
    plaintext=str(plaintext,encoding='ascii')
    print('plaintext:',plaintext)




