#include "mode.h"


void ECB(){
    readToMemory();
    cipherText = malloc(plainSize+1);
    binCipherText = malloc(plainSize*4);
    cipherText[plainSize] = '\0';
    printf("[+] Test launched, generating cipher\n[+] Writing cipher...\n");
    ECB_Encode();
    FILE *fp =fopen(cipherFile,"w");
    if(fp==NULL) {
        printf("[-] Failed to load the specific file");
        exit(1);
    }
    fputs(cipherText, fp);
    fclose(fp);
    // Timing
    time_t c_start, c_end;
    c_start = clock();
    int count = 1;
    printf("[+] 20 tests launched\n");
    for(; count<=20; count++){
        printf("[+] NO. %d encode and decode\n", count);
        ECB_Encode();
        ECB_Decode();
    }
    // End
    c_end = clock();
    printf("[+] ECB time cost: %lfMS\n", difftime(c_end, c_start));
}


void ECB_Encode(){
    hexToBin(plainText, binPlainText, plainSize);
    int groupNum = plainSize*4/64;
    bool currentPlain[64];
    char final[17];
    final[16] = '\0';
    for(int i=0; i<groupNum; i++){
        for(int j=0; j<64; j++){
            currentPlain[j] = binPlainText[j+i*64];
        }
        En_DES(currentPlain, binKeyText, final);
        for(int j=0; j<16; j++){
            cipherText[i*16+j] = final[j];
        }
    }
    printf("[+] Cipher text: ");
    for(int i=0; i<16; i++) printf("%c", cipherText[i]);
    printf("...\n");
}


void ECB_Decode(){
    hexToBin(cipherText, binCipherText, plainSize);
    int groupNum = plainSize*4/64;
    bool currentCipher[64];
    char final[17];
    final[16] = '\0';
    for(int i=0; i<groupNum; i++) {
        for (int j = 0; j < 64; j++) {
            currentCipher[j] = binCipherText[j + i * 64];
        }
        De_DES(currentCipher, binKeyText, final);
        for (int j = 0; j < 16; j++) {
            plainText[i * 16 + j] = final[j];
        }
    }
    printf("[+] Plain text: ");
    for(int i=0; i<16; i++) printf("%c", plainText[i]);
    printf("...\n");
}


void CBC(){
    readToMemory();
    cipherText = malloc(plainSize+1);
    binCipherText = malloc(plainSize*4);
    cipherText[plainSize] = '\0';
    printf("[+] Test launched, generating cipher\n[+] Writing cipher...\n");
    CBC_Encode();
    FILE* fp = fopen(cipherFile, "w");
    if(fp==NULL) {
        printf("[-] Failed to load the specific file");
        exit(1);
    }
    fputs(cipherText, fp);
    fclose(fp);
    // CBC_Decode();
    printf("[+] 20 tests launched\n");
    // Timing
    time_t c_start, c_end;
    c_start = clock();
    int count = 1;
    for(; count<=20 ;count++){
        printf("[+] NO. %d encode and decode\n", count);
        CBC_Encode();
        CBC_Decode();
    }
    // End
    c_end = clock();
    printf("[+] CBC time cost: %lfMS\n", difftime(c_end, c_start));
}


void CBC_Encode(){
    hexToBin(plainText, binPlainText, plainSize);
    int groupNum = plainSize*4/64;
    bool currentPlain[64];
    char final[16];
    bool binFinal[64];
    for (int i=0; i<16; i++){
        final[i] = ivText[i];
    }
    for(int i=0; i<groupNum; i++){
        for(int j=0; j<64; j++){
            currentPlain[j] = binPlainText[j+i*64];
        }
        hexToBin(final,binFinal,16);
        // XOR
        XOR(currentPlain, binFinal);
        En_DES(currentPlain, binKeyText, final);
        for(int j=0; j<16; j++){
            cipherText[i*16+j] = final[j];
        }
    }
    printf("[+] Cipher text: ");
    for(int i=0; i<16; i++) printf("%c",cipherText[i]);
    printf("...\n");
}


void CBC_Decode(){
    hexToBin(cipherText, binCipherText, plainSize);
    // Number of groups(blocks)
    int groupNum = plainSize*4/64;
    bool currentCipher[64];
    char final[16];
    bool binFinal[64];
    bool IV[64];
    for (int i=0; i<64; i++){
        IV[i] = binIvText[i];
    }
    for(int i=0; i<groupNum; i++){
        for(int j=0; j<64; j++){
            currentCipher[j] = binCipherText[j+i*64];
        }
        // Decode first, then XOR
        De_DES(currentCipher, binKeyText, final);
        hexToBin(final, binFinal, 16);
        XOR(binFinal,IV);
        // Binary to hex
        for(int j=0; j<16; j++){
            final[j] = to_ascii(8*binFinal[j*4] + 4*binFinal[j*4+1] + 2*binFinal[j*4+2] + binFinal[j*4+3]);
            if(final[j]>=10){
                final[j] = to_ascii(final[j] -10 + 'A');
            }
            else{
                final[j] = to_ascii(final[j] + '0');
            }
        }
        // Iteration IV
        for(int j=0; j<64; j++){
            IV[j] = binCipherText[j+i*64];
        }
        for(int j=0; j<16; j++){
            plainText[i*16+j] = final[j];
        }
    }
    printf("[+] Plain text: ");
    for(int i=0; i<16; i++) printf("%c",plainText[i]);
    printf("...\n");
}


void OFB(){
    readToMemory();
    cipherText = malloc(plainSize+1);
    binCipherText = malloc(plainSize*4);
    cipherText[plainSize] = '\0';
    printf("[+] Test launched, generating cipher\n[+] Writing cipher...\n");
    OFB_Encode();
    FILE *fp = fopen(cipherFile, "w");
    if(fp==NULL){
        printf("[-] Failed to load the specific file");
        exit(1);
    }
    fputs(cipherText, fp);
    fclose(fp);
    printf("[+] 20 tests launched\n");
    time_t c_start, c_end;
    c_start = clock();
    for(int i=0; i<20; i++){
        printf("[+] NO. %d encode and decode\n", i+1);
        OFB_Encode();
        OFB_Decode();
    }
    c_end = clock();
    printf("[+] OFB time cost: %lfMS\n", difftime(c_end, c_start));
}


void OFB_Encode(){
    hexToBin(plainText, binPlainText, plainSize);
    bool binZ[64];
    int groupNum = plainSize*4/64;
    char final[17];
    bool binFinal[64];
    // bool end[64];
    for(int i=0; i<64; i++) binZ[i] = binIvText[i];
    for(int i=0; i<groupNum*8; i++){
        bool tem[8];
        bool current[8];    // Current plain text group
        En_DES(binZ, binKeyText, final);
        hexToBin(final, binFinal, 16);
        move(binZ, binFinal);
        for(int j=0; j<8; j++) tem[j] = binFinal[j];
        for(int j=0; j<8; j++) current[j] = binPlainText[i*8+j];
        XOR_8(tem, current);
        // To hex, write cipher text
        for(int j=0; j<2; j++){
            char sum = to_ascii(tem[j*4]*8 + tem[j*4+1]*4 + tem[j*4+2]*2 + tem[j*4+3]);
            if(sum>=10) sum = to_ascii(sum) - 10 + to_ascii('A');
            else sum = to_ascii(sum) + to_ascii('0');
            cipherText[i*2+j] = sum;
        }
    }
    printf("[+] Cipher text: ");
    for(int i=0; i<16; i++) printf("%c", cipherText[i]);
    printf("...\n");
}


void OFB_Decode(){
    hexToBin(cipherText, binCipherText, plainSize);
    bool binZ[64];
    int groupNum = plainSize*4/64;
    char final[17];
    bool binFinal[64];
    // bool end[64];
    for(int i=0; i<64; i++) binZ[i] = binIvText[i];
    for(int i=0; i<groupNum*8; i++){
        bool tem[8];
        bool current[8];
        En_DES(binZ,binKeyText,final);
        hexToBin(final,binFinal,16);
        move(binZ,binFinal);
        for(int j=0; j<8; j++) tem[j] = binFinal[j];
        for(int j=0; j<8; j++) current[j] = binCipherText[i*8+j];
        XOR_8(tem, current);
        for(int j=0; j<2; j++){
            char sum = to_ascii(tem[j*4]*8 + tem[j*4+1]*4 + tem[j*4+2]*2 + tem[j*4+3]);
            if(sum>=10) sum = to_ascii(sum - 10 +'A');
            else sum = to_ascii(sum + '0');
            plainText[i*2+j] = sum;
        }
    }
    printf("[+] Plain text: ");
    for(int i=0; i<16; i++) printf("%c",plainText[i]);
    printf("...\n");
}


void CFB(){
    readToMemory();
    cipherText = malloc(plainSize+1);
    binCipherText = malloc(plainSize*4);
    cipherText[plainSize] = '\0';
    printf("[+] Test launched, generating cipher\n[+] Writing cipher...\n");
    CFB_Encode();
    FILE *fp =fopen(cipherFile,"w");
    if(fp==NULL){
        printf("[-] Failed to load the specific file");
        exit(1);
    }
    fputs(cipherText, fp);
    fclose(fp);
    printf("[+] 20 tests launched\n");
    time_t c_start, c_end;
    c_start = clock();
    for(int i=0; i<20; i++){
        printf("[+] NO. %d encode and decode\n", i+1);
        CFB_Encode();
        CFB_Decode();
    }
    c_end = clock();
    printf("[+] CFB time cost: %lfMS\n", difftime(c_end, c_start));
}


void CFB_Encode(){
    hexToBin(plainText, binPlainText, plainSize);
    bool binZ[64];
    int groupNum = plainSize*4/64;
    char final[17];
    bool binFinal[64];
    // bool end[64];
    for(int i=0; i<64; i++) binZ[i] = binIvText[i];
    for(int i=0; i<groupNum*8; i++){
        bool tem[8];
        bool current[8];
        En_DES(binZ,binKeyText,final);
        hexToBin(final, binFinal, 16);
        for(int j=0; j<8; j++) tem[j] = binFinal[j];
        for(int j=0; j<8; j++) current[j] = binPlainText[i*8+j];
        XOR_8(tem, current);
        move(binZ, tem);
        for(int j=0; j<2; j++){
            char sum = to_ascii(tem[j*4]*8 + tem[j*4+1]*4 + tem[j*4+2]*2 + tem[j*4+3]);
            if(sum>=10) sum = to_ascii(sum - 10 +'A');
            else sum = to_ascii(sum + '0');
            cipherText[i*2+j] = sum;
        }
    }
    printf("[+] Cipher text: ");
    for(int i=0; i<16; i++) printf("%c",cipherText[i]);
    printf("...\n");
}


void CFB_Decode(){
    hexToBin(cipherText, binCipherText, plainSize);
    bool binZ[64];
    int groupNum = plainSize*4/64;
    char final[17];
    bool binFinal[64];
    // bool end[64];
    for(int i=0; i<64; i++) binZ[i] = binIvText[i];
    for(int i=0; i<groupNum*8; i++){
        bool tem[8];
        bool current[8];
        En_DES(binZ,binKeyText,final);
        hexToBin(final,binFinal,16);
        for(int j=0; j<8; j++) tem[j]=binFinal[j];
        for(int j=0; j<8; j++) current[j] = binCipherText[i*8+j];
        XOR_8(tem, current);
        move(binZ,current);
        // To hex, write plain text
        for(int j=0; j<2; j++){
            char sum = to_ascii(tem[j*4]*8 + tem[j*4+1]*4 + tem[j*4+2]*2 + tem[j*4+3]);
            if(sum>=10) sum = to_ascii(sum - 10 +'A');
            else sum = to_ascii(sum + '0');
            plainText[i*2+j] = sum;
        }
    }
    printf("[+] Plain text: ");
    for(int i=0; i<16; i++) printf("%c",plainText[i]);
    printf("...\n");
}
