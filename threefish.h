#ifndef _THREEFISH_H
#define _THREEFISH_H
unsigned long long int plaintextword[4],blockcipherkeyword[4],tweakword[2],temp[4],ciphertext[32];
unsigned long long int subkeys[19][4];
void bytestowords(int *,int,int);
void keyschedule(void);
void rounds(void);
void mix(unsigned long long int,unsigned long long int,int,int);
void wordstobytes(void);
#endif
