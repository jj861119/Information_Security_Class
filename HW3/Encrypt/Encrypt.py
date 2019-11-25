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


def encrypt_ECB(data: bytes, key):
    aes = AES.new(key, AES.MODE_ECB)
    blocks=[data[i:i+16]for i in range(0,len(data),16)]
    #print(blocks.shape)
    #print(len(blocks))
    # cipherBlocks=[]
    # print(blocks)
    # cipher=b''
    # for n in range(0,len(blocks),1):
    #     cipherBlocks.append(aes.encrypt(blocks[n]))
    # for n in range(0,len(cipherBlocks),1):
    #     cipher+=cipherBlocks[n]
    
    #cipher=b''
    #for block in blocks:
    #    cipher=cipher+aes.encrypt(block)
    
    cipher=bytes().join([aes.encrypt(block)for block in blocks])
       
    return cipher

def encrypt_CBC(data: bytes, key):
    aes = AES.new(key, AES.MODE_ECB)
    blocks=[data[i:i+16]for i in range(0,len(data),16)]
    #print(blocks.shape)
    #print(len(blocks))
    cipherBlocks=[]
    print(blocks)
    cipher=b''
    for n in range(0,len(blocks),1):
        cipherBlocks.append(aes.encrypt(blocks[n]))
    
    cipher = ''.join(cipherBlocks)
    
    #cipher=b''
    #for block in blocks:
    #    cipher=cipher+aes.encrypt(block)
    
    #cipher=bytes().join([aes.encrypt(block)for block in blocks])
       
    return cipher

# def encrypt_ECB(data, key):
#     np_img = numpy.array(img)
#     aes = AES.new(key, AES.MODE_ECB)
#     inputBlock=""
#     count=0
#     outputImg=numpy.zeros((img.height,img.width,3))
#     tmpCipher=""
#     for i in range(0,img.height,1):
#         for j in range(0,img.width,1):
#             for c in range(0,3,1):
#                 if(count!=8):
#                     inputBlock+='{0:08b}'.format(np_img[i][j][c])
#                     count+=1
#                     if(count==8):
#                         tmpCipher=aes.encrypt(inputBlock)
#                         #count=0
#                         print(tmpCipher)
#                         print(b2a_hex(tmpCipher))
#     return ""

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
    print("CBC")

img=Image.open(io.BytesIO(header+cipher[:length]))
img.save(f'{filename}-{mode}.jpg')


#int('11111111', 2)
#test = '{0:08b}'.format(255)

