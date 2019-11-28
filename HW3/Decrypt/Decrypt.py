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

def decrypt_ECB(data: bytes, key):
    aes = AES.new(key, AES.MODE_ECB)
    blocks=[data[i:i+16]for i in range(0,len(data),16)]
    plainBlocks=[]
    plain=b''
    for n in range(0,len(blocks),1):
        plainBlocks.append(aes.decrypt(blocks[n]))
    
    plain=bytes().join([plainBlock for plainBlock in plainBlocks])

    return plain

def decrypt_CBC(data: bytes, key):
    aes = AES.new(key, AES.MODE_ECB)
    with open(f"IV",'rb') as file:
        IV=file.read()
    
    blocks=[data[i:i+16]for i in range(0,len(data),16)]
    plainBlocks=[]
    plain=b''
    plainBlocks.append(XOR(aes.decrypt(blocks[0]),IV))
    for n in range(1,len(blocks),1):
        tmpBlock=aes.decrypt(blocks[n])
        plainBlocks.append(XOR(tmpBlock,blocks[n-1]))

    plain=bytes().join([plainBlock for plainBlock in plainBlocks])
    return plain
    
def decrypt_OPC(data: bytes,key1):
    aes=AES.new(key1,AES.MODE_ECB)
    with open(f"IV",'rb') as file:
        IV=file.read()
    
    with open(f"key2",'rb') as file:
        key2=file.read()

    blocks=[data[i:i+16]for i in range(0,len(data),16)]
    plainBlocks=[]
    plain=b''
    O=key2
    for n in range(0,len(blocks),1):
        O=aes.encrypt(IV)
        G=(blocks[n])[:16]
        plainBlocks.append(XOR(G,O))
        IV=G
    plain=bytes().join([plainBlock for plainBlock in plainBlocks])
    return plain

mode = sys.argv[1]
filename = sys.argv[2]
with open(f"{filename}.ppm",'rb') as file:
    header = file.readline() + file.readline() + file.readline()
    data = file.read()
    length = len(data)


pad_length = 16 - length % 16
if(pad_length!=16):
    data=padding(data,pad_length)
    
with open('static_key','rb') as f:
    skey=f.read()

if(mode=='ECB_dec'):
    plain = decrypt_ECB(data,skey)
    image= Image.open(io.BytesIO(header + plain[:length]))
    image.save(f'{filename}-{mode}.jpg')
elif(mode=='CBC_dec'):
    plain=decrypt_CBC(data,skey)
    image= Image.open(io.BytesIO(header + plain[:length]))
    image.save(f'{filename}-{mode}.jpg')
elif(mode=='OPC_dec'):
    plain = decrypt_OPC(data,skey)
    img=Image.open(io.BytesIO(header+plain[:length]))
    img.save(f'{filename}-{mode}.jpg')
    