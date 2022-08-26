import hashlib
import os
import scipy.io


def sha512(filename):
    """
    :param filename: 文件名
    :return: SHA-512码
    """
    if not os.path.isfile(filename):
        return
    myHash = hashlib.sha512()  # change the generation method of the message digests here
    f = open(filename, 'rb')
    while True:
        b = f.read(8096)
        if not b:
            break
        myHash.update(b)
    f.close()
    return myHash.hexdigest()


def uint8Format(hexstring):
    res = []
    i = 0
    while(1):
        temp = hexstring[i:i+2]
        i += 2
        res.append(int(temp, 16))
        if i >= len(hexstring):
            break
    return res


SHA512 = uint8Format(sha512('house.tiff'))
Changed1SHA512 = uint8Format(sha512('house_changed_1.tiff'))
print(SHA512)
print(Changed1SHA512)

scipy.io.savemat('SHA512.mat', mdict={'SHA512': SHA512})
scipy.io.savemat('Changed1SHA512', mdict={'Changed1SHA512': Changed1SHA512})
