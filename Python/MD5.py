import fromInternetMD
import hashlib

str = "nie podoba mi sie ten przedmiot"
result = hashlib.md5(str.encode())
print("Coś tu mam napisać: ", end='')
print(result.hexdigest())
fromInternetMD.useMeOutside(str.encode())
