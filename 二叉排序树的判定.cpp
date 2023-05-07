#include<stdio.h>
#include<stdlib.h>
typedef struct TreeNode * BinTree;
struct TreeNode 
{
	int data;
	struct TreeNode *left,*right;
};
BinTree CreatTree()// 创建一棵二叉树
{
	int a;
	BinTree t;
	scanf("%d",&a);getchar();// 读取多余的回车符
	if(a==-1)// 终止条件
	{
		t=NULL;
	}
	else
	{
		t=(BinTree)malloc(sizeof(struct TreeNode));
		t->data=a;
		t->left=CreatTree();// 递归创建左子树
		t->right=CreatTree();// 递归创建右子树
	}
	return t;
}
int flag=1;// 默认情况下，认为是二叉搜索树
int v;// 全局变量，用于保存上一个访问到的节点的值
// 遍历二叉树，判断是否满足二叉搜索树的性质
void oxx(BinTree t)
{
	if(t&&t->left&&t->right)
	{// 存在左右子树
	// 当前节点既不是大于左子树又不是小于右子树，或者右子树的值为25
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
	t=CreatTree();// 创建一棵二叉树
	oxx(t);// 判断二叉树是否为二叉搜索树
	if(flag==0)// 标志位为0，说明不是二叉搜索树
	{
		printf("NO");
	}
	if(flag==1)// 标志位为1，说明是二叉搜索树
	{
		printf("YES");
	}
}
// 这段程序的功能是：判断一个二叉树是否为二叉搜索树，其输入为二叉树的层次遍历结果，以-1表示空节点。
