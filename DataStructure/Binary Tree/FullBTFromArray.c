#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
typedef struct _tree
{
    double val;
    struct _tree *left;
    struct _tree *right;
}TREE;

TREE *table[64];
TREE *table_new[64];
int create_p = 0;//旧表指针
int create_pn = 0;//新表指针
void create(TREE *r,double val)
{
	r = (TREE *)malloc(sizeof(TREE));
	r->val = val;
	table_new[create_pn] = r->left;
	create_pn++;
	table_new[create_pn] = r->right;
	create_pn++;
}


double scanfu()
{
    double temp;
    scanf("%f",&temp);
    return temp;
}

int main()		//满、规则、二叉树
{
	FILE *fin = freopen("in.dat","r",stdin);
	
	TREE root;

	int len = 0;//元素个数
	for(int temp;scanf("%f",&temp)!=EOF;len++);
	rewind(fin);
	int j = log2(len);//层数

    create(&root,scanfu());
    memcpy(table,table_new,64);
    for(int i=1;i<j;i++)
    {
        for(int k=0;k<=i;k++)
            create(table[k],scanfu());
        memcpy(table,table_new,64);
    }

    fclose(fin);
	return 0;
}