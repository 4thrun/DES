#ifndef DES_MODE_H
#define DES_MODE_H

#include "DES.h"
// ECB
void ECB();
void ECB_Encode();
void ECB_Decode();
// CBC
void CBC();
void CBC_Encode();
void CBC_Decode();
// CFB
void CFB();
void CFB_Encode();
void CFB_Decode();
// OFB
void OFB();
void OFB_Decode();
void OFB_Encode();

#endif //DES_MODE_H
