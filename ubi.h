#ifndef _UBI_H
#define _UBI_H
int plaintext[100000];
int blockcipherkey[32];
int entireciphertext[100000];
int tweak[128];
int sizeofplaintext,move1;
FILE *fp2;
void ubiimplement(void);
#endif
