#include<stdio.h>
#include<math.h>
#include "threefish.h"
void bytestowords(int temp1[],int check,int bytesize)//function to convert bytes to 64-bit words
{
	int i,j,u;
	unsigned long long int s;
	if(check==0)//converting plaintext to plaintext 64-bit words
	{
		check=(bytesize/8);
		for(i=0;i<check;i++)
		{
			s=0;
			u=0;
			for(j=(8*i);j<=(8*i+7);j++,u++)
			{
				s=s+temp1[j]*pow(256,u);
			}
			plaintextword[i]=s;
		}
	}
	else if(check==1)//converting block cipher key to block cipher key 64-bit words
	{
		check=(bytesize/8);
		for(i=0;i<check;i++)
		{
			s=0;
			u=0;
			for(j=(8*i);j<=(8*i+7);j++,u++)
			{
				s=s+temp1[j]*pow(256,u);
			}
			blockcipherkeyword[i]=s;
		}
	}
	else if(check==2)//converting tweak to tweak 64-bit words
	{
		check=(bytesize/8);
		for(i=0;i<check;i++)
		{
			s=0;
			u=0;
			for(j=(8*i);j<=(8*i+7);j++,u++)
			{
				s=s+temp1[j]*pow(256,u);
			}
			tweakword[i]=s;
		}
	}
}
void keyschedule(void)//function to generate the subkeys
{
	unsigned long long int extrakey1,extrakey2;
	unsigned long long int s,w;
	int i,j;
	extrakey1=blockcipherkeyword[0];//first of the two extra keys generation process
	for(i=1;i<4;i++)
	{
		extrakey1=extrakey1^blockcipherkeyword[i];
	}
	extrakey1=extrakey1^0x1BD11BDAA9FC1A22;
	extrakey2=tweakword[0];//second of the two extra keys generation process
	extrakey2=extrakey2^tweakword[1];
	s=1;
	for(i=1;i<=64;i++)//calculating 2^64-1
	{
		if(i==64)
		s=(s<<2)-1;
		else
		s=(s<<2);
	}
	for(i=0;i<19;i++)//loop generating ith subkey,formula taken from pdf
	{
		w=(i%5);
		if(w==4)
		subkeys[i][0]=extrakey1;
		else
		subkeys[i][0]=blockcipherkeyword[w];
		w=((i+1)%5);
		if(w==4)
		subkeys[i][1]=extrakey1;
		else
		subkeys[i][1]=blockcipherkeyword[w];
		w=(i%3);
		if(w==2)
		subkeys[i][1]=((subkeys[i][1]+extrakey2)%s);
		else
		subkeys[i][1]=((subkeys[i][1]+tweakword[w])%s);
		w=((i+2)%5);
		if(w==4)
		subkeys[i][2]=extrakey1;
		else
		subkeys[i][2]=blockcipherkeyword[w];
		w=((i+1)%3);
		if(w==2)
		subkeys[i][2]=((subkeys[i][2]+extrakey2)%s);
		else
		subkeys[i][2]=((subkeys[i][2]+tweakword[w])%s);
		w=((i+3)%5);
		if(w==4)
		subkeys[i][3]=extrakey1;
		else
		subkeys[i][3]=blockcipherkeyword[w];
		w=i;
		subkeys[i][3]=((subkeys[i][3]+w)%s);
	}
}
void rounds(void)//function to complete 72 rounds
{
	unsigned long long int s;
	int i,j;
	s=1;
	for(i=1;i<=64;i++)//calculating 2^64-1
	{
		if(i==64)
		s=(s<<2)-1;
		else 
		s=(s<<2);
	}
	for(i=0;i<72;i++)//loop for each of the 72 rounds
	{
		if((i%4)==0)//adding a subkey if round no. divisible by 4
		{
			for(j=0;j<4;j++)
			{
				plaintextword[j]=((plaintextword[j]+subkeys[i/4][j])%s);
			}
		}
		mix(plaintextword[0],plaintextword[1],i,0);//mix function formula taken from pdf
		mix(plaintextword[2],plaintextword[3],i,1);//mix function formula taken from pdf
		for(j=0;j<4;j++)//permutation of every round formula taken from pdf
		{
			if(j==0)
			plaintextword[j]=temp[0];
			if(j==1)
			plaintextword[j]=temp[3];
			if(j==2)
			plaintextword[j]=temp[2];
			if(j==3)
			plaintextword[j]=temp[1];
		}
	}
	for(j=0;j<4;j++)//generating the final ciphertext in 64-bit words
	{
		plaintextword[j]=((plaintextword[j]+subkeys[18][j])%s);
	}
	wordstobytes();//converting to bytes format
}
void mix(unsigned long long int x6,unsigned long long int x7,int d,int j)//function for MIX
{
	int i,x8[8][2];//this is a formula based function can be best understood in consultation with the pdf
	unsigned long long int s=1,y1,y2;
	for(i=1;i<=64;i++)//calculating 2^64-1
	{
		if(i==64)
		s=(s<<2)-1;
		else
		s=(s<<2);
	}
	y1=((x6+x7)%s);//calculating the 1st output
	for(i=0;i<8;i++)//calculation of 2nd output requires a rotation by a constant which is calculated here.
	{
		if(i==0)
		{
			x8[i][0]=14;
			x8[i][1]=16;
		}
		if(i==1)
		{
			x8[i][0]=52;
			x8[i][1]=57;
		}
		if(i==2)
		{
			x8[i][0]=23;
			x8[i][1]=40;
		}
		if(i==3)
		{
			x8[i][0]=5;
			x8[i][1]=37;
		}
		if(i==4)
		{
			x8[i][0]=25;
			x8[i][1]=33;
		}
		if(i==5)
		{
			x8[i][0]=46;
			x8[i][1]=12;
		}
		if(i==6)
		{
			x8[i][0]=58;
			x8[i][1]=22;
		}
		if(i==7)
		{
			x8[i][0]=32;
			x8[i][1]=32;
		}
	}
	if(j==0)//results after mix happens stored in temp array 
	{
		y2=((x7<<x8[d%8][j])^y1);
		temp[0]=y1;
		temp[1]=y2;
	}
	else if(j==1)
	{
		y2=((x7<<x8[d%8][j])^y1);
		temp[2]=y1;
		temp[3]=y2;
	}
}
void wordstobytes(void)//function to convert 64-bit words to bytes
{
	int i,j=0,u,t,v;
	for(u=0;u<4;u++)//converting to byte mode
	{
		for(i=0;i<8;i++)
		{
			ciphertext[j]=((plaintextword[u]/(unsigned long long int)pow(256,i))%256);
			j=j+1;
		}
	}
	for(i=0;i<j;i++)//converting from lsb first mode to general mode
	{
		for(u=i,v=(i+7);u<(i+8);u++,v--)
		{
			t=ciphertext[u];
			ciphertext[u]=ciphertext[v];
			ciphertext[v]=t;
		}
		i=(u-1);
	}
}
