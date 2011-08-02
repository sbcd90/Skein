#include<stdio.h>
#include "threefish.h"
#include "ubi.h"
#include "bitbyteoperations.h"
void ubiimplement(void)//function to implement the ubi chaining mode
{
	int originalsize,i1,mini,w,j,tempe[100000],tempe1[128],i,tempe2[127],maxaddvalue,tempe3[128],tweakbyte1[16];
	originalsize=sizeofplaintext;
	while((sizeofplaintext%32)!=0)//making the size of plaintext a multiple of 32 bytes
	{
		plaintext[sizeofplaintext]=0;
		sizeofplaintext=sizeofplaintext+1;
	}
	bytestowords(plaintext,0,sizeofplaintext);//converting from bytes to 64 bit words for use in threefish 
	for(i1=1;i1<=(sizeofplaintext/32);i1++)//the rounds in ubi chaining mode
	{
		mini=originalsize;//implementing the generation of tweak value for each round
		if(mini<(i*32))
		mini=(i*32);
		w=0;
		for(j=mini;j!=0;j=(j/2))//converting to bits
		{
			tempe[w]=(j%2);
			w=w+1;
		}
		for(i=0,j=127;i<128;i++,j--)//inverting input tweak
		{
			tempe1[i]=tweak[j];
		}
		addbyte(tempe1,tempe,128,w);//performing bit addition
		if(w>128)
		maxaddvalue=w;
		else
		maxaddvalue=128;
		if((i1-1)==0)
		{
			for(i=0;i<126;i++)//finding 2^126 
			{
				tempe2[i]=0;
			}
			tempe2[i]=1;
			addbyte(addvalue,tempe2,maxaddvalue,127);//adding bits
			if(maxaddvalue<127)//updating max array size
			maxaddvalue=127;
		}
		if(i1==(sizeofplaintext-1))
		{
			for(i=0;i<127;i++)//finding 2^127
			{
				tempe3[i]=0;
			}
			tempe3[i]=1;
			addbyte(addvalue,tempe3,maxaddvalue,128);//adding bits
			if(maxaddvalue<128)//updating max array size
			maxaddvalue=128;
		}
		changebyte(addvalue,maxaddvalue);//changing to byte format from bits
		for(i=0,j=15;i<16;i++,j--)//changing to lsb first mode
		{
			tweakbyte1[i]=tweakbyte[j];
		}
		bytestowords(blockcipherkey,1,32);//changing from bytes to 64-bit words for threefish
		bytestowords(tweakbyte1,2,16);
		keyschedule();//generating key schedule
		rounds();//performing rounds in threefish
		for(i=0;i<32;i++)//generating block cipher key for next ubi round
		{
			blockcipherkey[i]=ciphertext[i];
			if(move1<originalsize)
			{
				entireciphertext[move1]=ciphertext[i];
				move1=move1+1;
			}
		}
	}
}
