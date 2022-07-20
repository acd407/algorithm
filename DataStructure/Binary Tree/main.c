#include <stdio.h>
#include <stdlib.h>
struct tree
{
    struct tree *LeftChild;
    int data;
    struct tree *RightChild;
};

int make(struct tree *child,int n)
{
    if(n==0)
    {
        child = NULL;
        return 0;
    }
    child = (struct tree *)malloc(sizeof(struct tree));
    if(!child)
    {
        printf("Error : memory allocate failure.\n");
        exit(-1);
    }
    n--;
    child->data=n;
    make(child->LeftChild,n);
    make(child->RightChild,n);
}

int ClimbAsWidth(struct tree *root)//给出根节点的位置
{
    printf("%d\n",root->data);
    if(root->LeftChild==NULL&&root->RightChild==NULL)
        return 0;
    if(root->LeftChild!=NULL)
        ClimbAsWidth(root->LeftChild);
    if(root->RightChild!=NULL)
        ClimbAsWidth(root->RightChild);
}

int main()
{
    struct tree troot;
    troot.data=5;
    make(troot.LeftChild,5);//加上root共6层
    make(troot.RightChild,5);
    ClimbAsWidth(&troot);
    return 0;
}