#include<stdio.h>
#include<stdlib.h>
typedef struct TreeNode * BinTree;
struct TreeNode 
{
	int data;
	struct TreeNode *left,*right;
};
BinTree CreatTree()// ����һ�ö�����
{
	int a;
	BinTree t;
	scanf("%d",&a);getchar();// ��ȡ����Ļس���
	if(a==-1)// ��ֹ����
	{
		t=NULL;
	}
	else
	{
		t=(BinTree)malloc(sizeof(struct TreeNode));
		t->data=a;
		t->left=CreatTree();// �ݹ鴴��������
		t->right=CreatTree();// �ݹ鴴��������
	}
	return t;
}
int flag=1;// Ĭ������£���Ϊ�Ƕ���������
int v;// ȫ�ֱ��������ڱ�����һ�����ʵ��Ľڵ��ֵ
// �������������ж��Ƿ��������������������
void oxx(BinTree t)
{
	if(t&&t->left&&t->right)
	{// ������������
	// ��ǰ�ڵ�Ȳ��Ǵ����������ֲ���С����������������������ֵΪ25
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
	t=CreatTree();// ����һ�ö�����
	oxx(t);// �ж϶������Ƿ�Ϊ����������
	if(flag==0)// ��־λΪ0��˵�����Ƕ���������
	{
		printf("NO");
	}
	if(flag==1)// ��־λΪ1��˵���Ƕ���������
	{
		printf("YES");
	}
}
// ��γ���Ĺ����ǣ��ж�һ���������Ƿ�Ϊ������������������Ϊ�������Ĳ�α����������-1��ʾ�սڵ㡣
