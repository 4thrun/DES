# DES

## Tips

- Initial vector(des\_iv\.txt) and key(des\_key\.txt) should be placed in the folder "file" in the same directory with the \.exe\.

- If the teaching assistant in your course just care about the result, you should wait for those who do well in programming to finish their homework first. Then, copy their source code instead of wasting time searching online\.
- Spending plenty of time on Word and PowerPoint makes your marks higher\.

## Commands

```
eldes -p ./file/des_plain.txt -k ./file/des_key.txt -m ECB -v ./file/des_iv.txt -c ./file/des_cipher_ECB.txt
eldes -p ./file/des_plain.txt -k ./file/des_key.txt -m CBC -v ./file/des_iv.txt -c ./file/des_cipher_CBC.txt
eldes -p ./file/des_plain.txt -k ./file/des_key.txt -m CFB -v ./file/des_iv.txt -c ./file/des_cipher_CFB.txt
eldes -p ./file/des_plain.txt -k ./file/des_key.txt -m OFB -v ./file/des_iv.txt -c ./file/des_cipher_OFB.txt
```

