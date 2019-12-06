import sys
sys.setrecursionlimit(10000000)
import random
from random import randrange
import math

def RSA(plaintext):
    #encrypt part
    p,q,d,e,n=genkey()
    cipher=square_and_multiply(plaintext_int,e,n)
    
    # decrypt part
    plain=CRT(p,q,d,cipher)
    return cipher,plain
    
def CRT(p,q,d,c):
    dp = d % (p-1)
    dq = d % (q-1)
    q_inverse = modinv(q,p)
    m1=square_and_multiply(c,dp,p)
    m2=square_and_multiply(c,dq,q)
    h=(q_inverse*(m1-m2)) % p
    m = m2 + (h*q)
    return m

def getpq():
    p=random.getrandbits(1024)
    flag=False
    while(flag==False):
        if(isPrime(p)):
            flag=True
            break
        p=random.getrandbits(1024)
    q=random.getrandbits(1024)
    flag=False
    while(flag==False and p != q):
        if(isPrime(q)):
            flag=True
            break
        q=random.getrandbits(1024)
    print('p:',p)
    print('q:',q)
    return p,q

def isPrime(n):
    for i in range(1,5):
        if(not (miller_rabin(n))):
            return False
    return True

def miller_rabin(n, k=10):
	if n == 2:
		return True
	if not n & 1:
		return False
	def check(a, s, d, n):
		x = pow(a, d, n)
		if x == 1:
			return True
		for i in range(s - 1):
			if x == n - 1:
				return True
			x = pow(x, 2, n)
		return x == n - 1
	s = 0
	d = n - 1
	while d % 2 == 0:
		d >>= 1
		s += 1
	for i in range(k):
		a = randrange(2, n - 1)
		if not check(a, s, d, n):
			return False
	return True

def genkey():
    p,q=getpq()
    n=p*q
    phi=(p-1)*(q-1)
    e=random.randint(1,phi)
    g=math.gcd(e,phi)
    while(g != 1):
        e=random.randint(1,phi)
        g=math.gcd(e,phi)
    
    #find d for decrypt
    d=modinv(e,phi)
    return p,q,d,e,n #return public keys(e,N)
    
def egcd(a, b):
    if a == 0:
        return (b, 0, 1)
    else:
        g, y, x = egcd(b % a, a)
        return (g, x - (b // a) * y, y)

def modinv(a, m):
    g, x, y = egcd(a, m)
    if g != 1:
        raise Exception('modular inverse does not exist')
    else:
        return x % m

def square_and_multiply(x, H,n):
    H = bin(H)
    H = H[2:]
    y = 1
    l = len(H)
    for i in range(0, l):
	    y = (y*y) % n
	    if (H[i] == '1'):
		    y = (y * x) % n
    return y

if __name__ == '__main__':
    plaintext=sys.argv[1]
    '''
    plaintext:string -> bytes -> integer
    because python cannot convert string into integer
    '''
    tmp=bytes(plaintext,encoding='utf-8')
    plaintext_len=len(tmp)
    plaintext_int=int.from_bytes(tmp,byteorder='big')
    cipher,plain=RSA(plaintext_int)
    plain=plain.to_bytes(plaintext_len,byteorder='big')
    plain=str(plain,encoding='utf-8')
    print('cipher text:',cipher)
    print('plain text:',plain)
    