import numpy
from PIL import Image
from Crypto import Random
from Crypto.Cipher import AES
import base64
import sys
import io
import os

def padding(data, pad_length):
    return data + bytes([pad_length]*pad_length)

def XOR(blockData,IV):
    result = bytearray()
    for blockData, IV in zip(blockData, IV):
        result.append(blockData ^ IV)
    return bytes(result)

def encrypt_ECB(data: bytes, key):
    aes = AES.new(key, AES.MODE_ECB)
    blocks=[data[i:i+16]for i in range(0,len(data),16)]
    #print(blocks.shape)
    #print(len(blocks))
    cipherBlocks=[]
    #print(blocks)
    cipher=b''
    for n in range(0,len(blocks),1):
        cipherBlocks.append(aes.encrypt(blocks[n]))  

    cipher=bytes().join([cipherBlock for cipherBlock in cipherBlocks])  
       
    return cipher

def encrypt_CBC(data: bytes, key):
    aes = AES.new(key, AES.MODE_ECB)

    IV=os.urandom(16)
    with open(f"IV",'wb') as file:
        file.write(IV)

    #print("IV:")
    #print(IV)
    blocks=[data[i:i+16]for i in range(0,len(data),16)]
    cipherBlocks=[]
    cipher=b''
    for n in range(0,len(blocks),1):
        tmpBlock = XOR(blocks[n],IV)
        cipherBlocks.append(aes.encrypt(tmpBlock))
        IV=cipherBlocks[n]
       
    cipher=bytes().join([cipherBlock for cipherBlock in cipherBlocks])
    return cipher


# img = Image.open('./penguin.ppm')
# width = img.width
# height = img .height


#print(sys.argv[1])
#print(sys.argv[2])
mode = sys.argv[1]
filename = sys.argv[2]
with open(f"{filename}.ppm",'rb') as file:
    header = file.readline() + file.readline() + file.readline()
    data = file.read()
    length = len(data)


pad_length = 16 - length % 16
if(pad_length!=16):
    data=padding(data,pad_length)


random_key = os.urandom(16)
with open(f"key",'wb') as file:
    file.write(random_key)
    

if(mode=='ECB'):
    cipher = encrypt_ECB(data,random_key)
if(mode=='CBC'):
    cipher = encrypt_CBC(data,random_key)

img=Image.open(io.BytesIO(header+cipher[:length]))
img.save(f'{filename}-{mode}.jpg')


#int('11111111', 2)
#test = '{0:08b}'.format(255)

