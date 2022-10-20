//BF算法（字符串暴力查找）
#include <stdio.h>
#include <string.h>
#include <stdio.h>
int main(int argc,char **argv)
{
	if(argc!=3)
		return 0;
	char *master = argv[1], *slave  = argv[2];
	int lm = strlen(master), ls = strlen(slave);
	for(int i=0;i<lm-ls;i++)
		for(int j=0;j<ls;j++)
			if(slave[j]!=master[i+j])
				break;
			else if(j==ls-1)
				printf("%d",i);
	return 0;
}
