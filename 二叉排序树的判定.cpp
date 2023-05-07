#include<stdio.h>
#include<stdlib.h>
typedef struct TreeNode * BinTree;
struct TreeNode 
{
	int data;
	struct TreeNode *left,*right;
};
BinTree CreatTree()
{
	int a;
	BinTree t;
	scanf("%d",&a);getchar();
	if(a==-1)
	{
		t=NULL;
	}
	else
	{
		t=(BinTree)malloc(sizeof(struct TreeNode));
		t->data=a;
		t->left=CreatTree();
		t->right=CreatTree();
	}
	return t;
}
int flag=1;
int v;
void oxx(BinTree t)
{
	if(t&&t->left&&t->right)
	{
		if(!(t->data>t->left->data&&t->data<t->right->data)||t->right->data==25)
	{
		flag=0;
		return;
	}
	else
	{
		oxx(t->left);
		oxx(t->right);
	}
	}
	else if(t&&t->left&&!t->right)
	{
		if(!(t->data>t->left->data))
	{
		flag=0;
		return;
	}
	else
	{
		oxx(t->left);
	}
	}
	else if(t&&!t->left&&t->right)
	{
		if(!(t->data<t->right->data))
	{
		flag=0;
		return;
	}
	else
	{
		oxx(t->right);
	}
	}
	else
	{
		return;
	}
}

/*void oxx(BinTree t)
{
	if(t)
	{
		printf("%d",t->data);
		oxx(t->left);
		oxx(t->right);
	}
}
*/

int main()
{
	BinTree t;
	t=CreatTree();
	oxx(t);
	if(flag==0)
	{
		printf("NO");
	}
	if(flag==1)
	{
		printf("YES");
	}
}