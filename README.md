# DES

## Tip

Initial vector(des\_iv\.txt) and key(des\_key\.txt) should be placed in the folder "file" in the same directory with the \.exe\.

## Commands

```
eldes -p ./file/des_plain.txt -k ./file/des_key.txt -m ECB -v ./file/des_iv.txt -c ./file/des_cipher_ECB.txt
eldes -p ./file/des_plain.txt -k ./file/des_key.txt -m CBC -v ./file/des_iv.txt -c ./file/des_cipher_CBC.txt
eldes -p ./file/des_plain.txt -k ./file/des_key.txt -m CFB -v ./file/des_iv.txt -c ./file/des_cipher_CFB.txt
eldes -p ./file/des_plain.txt -k ./file/des_key.txt -m OFB -v ./file/des_iv.txt -c ./file/des_cipher_OFB.txt
```

