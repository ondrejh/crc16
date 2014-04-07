import struct #converting int to bytes

def addCRC16(data,pol):

    ''' add 2byte CRC16 at the end of input data
    arguments:
        data .. bytes array (input data)
        pol .. generator polynomial
    return:
        data + 2byte CRC16 '''

    if type(data)!=bytes:
        print('addCRC16 error: bytes input expected !!!')
        return None

    reg = 0

    for b in data:
        reg |= b

        for i in range(8):
            reg <<= 1
            if (reg&0x01000000)!=0:
                reg ^= pol

    for i in range(16):
        reg <<= 1
        if (reg&0x01000000)!=0:
            reg ^= pol

    reg >>= 8
    j = reg&0xFF
    reg >>= 8
    k = reg&0xFF

    data = data+struct.pack('>L',k)[-1:]+struct.pack('>L',j)[-1:]

    return data

def testCRC16(data,pol):

    ''' test CRC16 in data (bytes array) using generator polinomial pol
    return: True .. if CRC fits (results 0)
            False .. if CRC doesn't fit '''

    reg = 0

    for b in data:
        reg |= b
        for i in range(8):
            reg <<= 1
            if (reg&0x01000000)!=0:
                reg ^= pol

    if (reg&0x00FFFFFF)!=0:
        return False
    
    return True

if __name__ == "__main__":

    ''' test program '''

    data = b'\xB4\x01\x6F'
    pol = 0x800500

    for b in data:
        print('0x{:02X} '.format(b),end="")
    print(testCRC16(data,pol))

    data = addCRC16(data,pol)

    for b in data:
        print('0x{:02X} '.format(b),end="")
    print(testCRC16(data,pol))
