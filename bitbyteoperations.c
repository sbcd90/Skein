#include<stdio.h>
#include<math.h>
#include "bitbyteoperations.h"
void addbyte(int temp1[],int temp2[],int u,int v)//adding two nos. in bits format
{//this algorithm is quite simple
	int carry=0;
	int i,j,t,f=0,t1[100000];
	if(u<v)
	{
		t=u;
		u=v;
		v=t;
		for(i=0;i<u;i++)
		{
			t1[i]=temp1[i];
		}
		for(i=0;i<v;i++)
		{
			temp1[i]=temp2[i];
		}
		for(i=0;i<u;i++)
		{
			temp2[i]=t1[i];
		}
	}
	if(f==0)
	{
		for(i=0,j=0;i<u;i++,j++)
	    {
			if(j<v)
			{
				if((temp1[i]==0)&&(temp2[j]==0))
				{
					if(carry=0)
					addvalue[i]=0;
					else
					{
						addvalue[i]=1;
						carry=0;
					}
				}
				if((temp1[i]==0)&&(temp2[j]==1))
				{
					if(carry==0)
					addvalue[i]=1;
					else
					addvalue[i]=0;
				}
				if((temp1[i]==1)&&(temp2[j]==0))
				{
					if(carry==0)
					addvalue[i]=1;
					else
					addvalue[i]=0;
				}
				if((temp1[i]==1)&&(temp2[j]==1))
				{
					if(carry==0)
					{
						addvalue[i]=0;
						carry=1;
					}
					else
					addvalue[i]=1;
				}
			}
			if((carry!=0)&&(j>=u))
			{
				if(temp1[i]==0)
				{
					addvalue[i]=1;
					carry=0;
				}
				else
				addvalue[i]=0;
			}
			if((carry==0)&&(j>=u))
			addvalue[i]=temp1[i];
		}
	}
}
void changebyte(int temp4[],int u)//changing from bits to bytes format
{
	int i,s,w=0,v=0;
	s=0;
	for(i=0;i<u;i++)
	{
		if((i%8)==7)
		{
			tweakbyte[w]=s;
			s=0;
			v=0;
			w=w+1;
		}
		s=s+pow(2,v)*temp4[i];
	}
}
