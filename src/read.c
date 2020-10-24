#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void main()
{
	FILE *fp;
	int n,s,c;
	char str1[5],str2[5],str3[5],str4[10];
	fp=fopen("text.txt","r");
	fscanf(fp,"%s\n",str1);
	fscanf(fp,"%s\n",str2);
	fscanf(fp,"%s\n",str3);
	fscanf(fp,"%s\n",str4);
	n=atoi(str1);
	s=atoi(str2);
	c=atoi(str3);

	printf("%d %d %d %s",n,s,c,str4);
	fclose(fp);
}
