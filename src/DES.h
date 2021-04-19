#ifndef DES_DES_H
#define DES_DES_H

#include "utils.h"


// IP table
void IP(bool M[64]);
// Inverse IP table
void Inverse_IP(bool M[64]);
// F function
void F(const bool R1[32], const bool K[48], bool result[32]);
// DES encode
void En_DES(const bool M[64], bool K[64], char final[16]);
// DES decode
void De_DES(const bool M[64], bool K[64], char final[16]);
// 16 loops
void CreateKeyOfLoop(const bool K[64], bool Key[16][48]);

#endif //DES_DES_H
