#include<stdio.h>
int main()
{
	FILE *fp1;
	int i;
	fp1=fopen("input.txt","w");
	fprintf(fp1,"20\n");//input size of plaintext
	for(i=255;i>=236;i--)//input plaintext.any pseudorandom number generator could be used
	{
		fprintf(fp1,"%d\n",i);
	}
	for(i=127;i>=96;i--)//input block cipher key
	{
		fprintf(fp1,"%d\n",i);
	}
	for(i=0;i<128;i++)//input tweak.any pseudorandom no. generator could be used
	{
		if(((i%4)==0)||((i%5)==0)||((i%7)==0))
		fprintf(fp1,"1\n");
		else
		fprintf(fp1,"0\n");
	}
	fclose(fp1);
	return(0);
}
