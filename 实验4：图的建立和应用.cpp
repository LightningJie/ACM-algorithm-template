#include<stdio.h>
#include<stdlib.h>
#define maxsize 10
#define queuesize 100
typedef struct edgenode
{
	int adjvex;//����ڽӵĵ��ڶ������±꣬�ڽӵ�/.7
	struct edgenode *next;//ָ��Vi��һ���ڽӵ�ı߽��
	int weight;/*Ȩֵ*/
}edgenode;
typedef struct vexnode
{
	char data; //�洢��������ƻ��������Ϣ
	edgenode *firstedge;//�߱�ͷָ��
}vexnode;
typedef struct{
	vexnode vexlist[maxsize];//�����
	int n,e;
}graph;
//��ͼg�в��Ҷ���v,���ڶ��������е��±꣬�����ڷ���-1
int locatevex(graph g,char v)
{
	int i;
	for(i=0;i<g.n;i++)
		if(g.vexlist[i].data==v)return i;
	return -1;
}
void print(graph g)
{
	int i;
	edgenode *p;
	printf("ͼ���ڽӱ��ʾ��");
	for(i=0;i<g.n;i++){
		printf("\n%c ",g.vexlist[i].data);
		p=g.vexlist[i].firstedge;
		while(p!=NULL){
			printf("-->%d",p->adjvex);
			p=p->next;
		}
	}
	printf("\n");
}
void creategraph(graph *g)
{
	int i,j,k;
	char v1,v2;
	edgenode *s;
	char x;
	scanf("%d",&g->n);getchar();
	for(i=0;i<g->n;i++)
	{
		g->vexlist[i].data=getchar(); //���춥����Ϣ
		g->vexlist[i].firstedge=NULL;
		x=getchar();
	}
	scanf("%d",&g->e);getchar();
	for(k=0;k<g->e;k++)
	{
		v1=getchar();//����һ���ߵ���������
		getchar();
		v2=getchar();
		getchar();
		i=locatevex(*g,v1);
		j=locatevex(*g,v2);
		if(i>=0&&j>=0){
			s=(edgenode *)malloc(sizeof(edgenode));
			s->adjvex=j;
			s->next=g->vexlist[i].firstedge;
			g->vexlist[i].firstedge=s;
		}
	}
}
int visited[maxsize];/* ���ʱ�־����*/
/*�ӵ�i����������ݹ��������ȱ���ͼG*/


void DFS(graph g,int i)
{
	edgenode *p;
	printf("%c ",g.vexlist[i].data);/*���ʵ�i�����*/
	visited[i]=1;
	p=g.vexlist[i].firstedge;
	while(p!=NULL)  
	{
		if(visited[p->adjvex]==0)
			DFS(g,p->adjvex);/*��i����δ���ʵ��ڽӶ���j�ݹ����DFS*/
		p=p->next;
	}
}

void DFStraverse(graph  g) /*��ͼG����������ȱ���*/
{
	int v;
	for (v=0; v<g.n;v++)visited[v]=0; /*��ʼ����־����*/
	for  (v=0; v<g.n;v++) /*��֤����ͨͼ�ı���*/
		/*�ӵ�v����������ݹ��������ȱ���ͼG*/
		if (!visited[v])DFS(g,v);        
}

typedef struct  cirqueue
{
	char  *data;    
	int front;        
	int rear;    
}cirqueue;            

int initqueue(cirqueue *q)
{
	q->data=(char *)malloc(queuesize*sizeof(cirqueue));
	if (q->data==NULL)return 0; 
	q->front=q->rear=0;    
	return 1;
}

int enqueue (cirqueue *q,char e)
{ 
	if ((q->rear+1) % queuesize == q->front) 
		return 0; 
	q->data[q->rear] = e;
	q->rear = (q->rear+1) % queuesize; 
	return 1;
}

int dequeue (cirqueue *q,int *e) 
{
	if (q->front == q->rear)  return 0; //����Ϊ��
	*e = q->data[q->front];
	q->front = (q->front+1) %queuesize; //��ͷ����һλ
	return 1;
}

int getfront(cirqueue q,char *e)
{
	if (q.front == q.rear)  return 0; //����Ϊ��
	*e=q.data[q.front];
	return  1;
}
int queueempty(cirqueue q)//ջ�ǿ�
{ 
	if(q.front == q.rear)return 1; //����Ϊ��
	else return 0;
}

int queuelength(cirqueue q)
{ 
	return (q.rear-q.front+queuesize) % queuesize;
}

int BFSvisited[maxsize];
cirqueue q;
/*�ӵ�k���������������ȱ���ͼG,G���ڽӾ����ʾ��*/
void BFS(graph g,int k){
	int i;
	edgenode *p;
	initqueue(&q);/*��ʼ������*/
	//printf("%c ",g.vexlist[k].data);/*���ʵ�k�����*/
	//visited[k]=1;    
	enqueue(&q,k);/*��k���������*/
	while(queueempty(q)==0) {/*���зǿ�*/
		dequeue(&q,&i);
		
		if(visited[i]==0){
		printf("%c ",g.vexlist[i].data);/*���ʵ�k�����*/
		visited[i]=1;
		}
		p=g.vexlist[i].firstedge;/*��ȡ��1���ڽӵ�*/
		while(p!=NULL){
			if(visited[p->adjvex]==0){
				/*���ʵ�i�������ĩ�����ʵĶ���*/
				printf("%c ",g.vexlist[p->adjvex].data);
				visited[p->adjvex]=1;
				enqueue(&q,p->adjvex);/*��k���������*/
			}
			p=p->next;
		}        
	}
}
void BFStraverse(graph  g) //��ͼG���й�����ȱ���
{
	int v;
	for (v=0; v<g.n;v++) //��ʼ����־����
		visited[v]=0; 
	for  (v=0; v<g.n;v++) //��֤����ͨͼ�ı���
		if (!visited[v])BFS(g,v); 
	//�ӵ�v����������ݹ��������ȱ���ͼG
}
int main()
{
	graph g;
	creategraph(&g);
	//print(g);
	//printf("\n");
	//printf("ͼ��������ȱ������У�\n");
	DFStraverse(g);
	printf("\n");
	//printf("ͼ�Ĺ�����ȱ������У�\n");
	BFStraverse(g);
	printf("\n");
	return 0;
}
