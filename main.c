#include<stdio.h>
#include "threefish.h"
#include "ubi.h"
#include "bitbyteoperations.h"
int main()
{
	FILE *fp1;
	int i,j,u,t,v;
	fp1=fopen("input.txt","r");
	fp2=fopen("output2.txt","w");
	v=fscanf(fp1,"%d",&sizeofplaintext);
	for(i=0;i<sizeofplaintext;i++) //plaintext input
	{
		v=fscanf(fp1,"%d",&plaintext[i]);
	}
	for(i=0;i<32;i++) //block cipher key input
	{
		v=fscanf(fp1,"%d",&blockcipherkey[i]);
	}
	for(i=0;i<128;i++) //tweak input in bits format
	{
		v=fscanf(fp1,"%d",&tweak[i]);
	}
	for(i=0;i<sizeofplaintext;i++) //converting to least significant byte first mode
	{
		for(j=i,u=(i+7);j<(i+8);j++,u--)
		{
			t=plaintext[j];
			plaintext[j]=plaintext[u];
			plaintext[u]=t;
		}
		if(i<32)
		{
			for(j=i,u=(i+7);j<(i+8);j++,u--)//converting to lsb first mode
			{
				t=blockcipherkey[j];
				blockcipherkey[j]=blockcipherkey[u];
				blockcipherkey[u]=t;
			}
			i=j-1;
		}
	}
	move1=0;
	ubiimplement();//ubi implementation
	for(i=0;i<move1;i++)//output generation
	{
		fprintf(fp2,"%d\n",entireciphertext[i]);
	}
	fclose(fp1);
    fclose(fp2); 
	return(0);
}
