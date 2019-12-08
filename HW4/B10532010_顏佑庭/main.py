import numpy
import random
import base64
import sys
import io
import os

def miller_rabin_test(n):
    m=n-1
    k=0
    while m % 2==0:
        m>>=2
        k+=1
    a=random.randrange(2,n-2)
    b=(a**m)%n
    if(b!=1 and b!=(n-1)):
        i=1
        while(i<k and b!=n-1):
            b=(b**2)%n
            if(b==1):
                return False
            i+=1
        if(b!=n-1):
            return False
    return True

def init_1024():
    p=random.getrandbits(1024)

    q=random.getrandbits(1024)


def init_small():


action = sys.argv[1]
random_key = os.urandom(16)
    
if(miller_rabin_test(3)):
    print('true')
else:
    print('false')

if(action=='init'):
    if(sys.argv[2]=='1024'):
        mode=sys.argv[2]
        #init_1024()
    if(sys.argv[2]=='small'):
        mode=sys.argv[2]
        init_small()      





