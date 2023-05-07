#include<stdio.h>
#include<stdlib.h>
#define maxsize 10
#define queuesize 100
typedef struct edgenode
{
	int adjvex;//存放邻接的点在顶点表的下标，邻接点/.7
	struct edgenode *next;//指向Vi下一个邻接点的边结点
	int weight;/*权值*/
}edgenode;
typedef struct vexnode
{
	char data; //存储顶点的名称或其相关信息
	edgenode *firstedge;//边表头指针
}vexnode;
typedef struct{
	vexnode vexlist[maxsize];//顶点表
	int n,e;
}graph;
//在图g中查找顶点v,存在顶点数组中的下标，不存在返回-1
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
	printf("图的邻接表表示：");
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
		g->vexlist[i].data=getchar(); //构造顶点信息
		g->vexlist[i].firstedge=NULL;
		x=getchar();
	}
	scanf("%d",&g->e);getchar();
	for(k=0;k<g->e;k++)
	{
		v1=getchar();//输入一条边的两个顶点
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
int visited[maxsize];/* 访问标志数组*/
/*从第i个顶点出发递归地深度优先遍历图G*/


void DFS(graph g,int i)
{
	edgenode *p;
	printf("%c ",g.vexlist[i].data);/*访问第i个项点*/
	visited[i]=1;
	p=g.vexlist[i].firstedge;
	while(p!=NULL)  
	{
		if(visited[p->adjvex]==0)
			DFS(g,p->adjvex);/*对i的尚未访问的邻接顶点j递归调用DFS*/
		p=p->next;
	}
}

void DFStraverse(graph  g) /*对图G进行深度优先遍历*/
{
	int v;
	for (v=0; v<g.n;v++)visited[v]=0; /*初始化标志数组*/
	for  (v=0; v<g.n;v++) /*保证非连通图的遍历*/
		/*从第v个顶点出发递归地深度优先遍历图G*/
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
	if (q->front == q->rear)  return 0; //队列为空
	*e = q->data[q->front];
	q->front = (q->front+1) %queuesize; //队头后移一位
	return 1;
}

int getfront(cirqueue q,char *e)
{
	if (q.front == q.rear)  return 0; //队列为空
	*e=q.data[q.front];
	return  1;
}
int queueempty(cirqueue q)//栈非空
{ 
	if(q.front == q.rear)return 1; //队列为空
	else return 0;
}

int queuelength(cirqueue q)
{ 
	return (q.rear-q.front+queuesize) % queuesize;
}

int BFSvisited[maxsize];
cirqueue q;
/*从第k个顶点出发广度优先遍历图G,G以邻接矩阵表示。*/
void BFS(graph g,int k){
	int i;
	edgenode *p;
	initqueue(&q);/*初始化队列*/
	//printf("%c ",g.vexlist[k].data);/*访问第k个项点*/
	//visited[k]=1;    
	enqueue(&q,k);/*第k个顶点进队*/
	while(queueempty(q)==0) {/*队列非空*/
		dequeue(&q,&i);
		
		if(visited[i]==0){
		printf("%c ",g.vexlist[i].data);/*访问第k个项点*/
		visited[i]=1;
		}
		p=g.vexlist[i].firstedge;/*获取第1个邻接点*/
		while(p!=NULL){
			if(visited[p->adjvex]==0){
				/*访问第i个顶点的末曾访问的顶点*/
				printf("%c ",g.vexlist[p->adjvex].data);
				visited[p->adjvex]=1;
				enqueue(&q,p->adjvex);/*第k个顶点进队*/
			}
			p=p->next;
		}        
	}
}
void BFStraverse(graph  g) //对图G进行广度优先遍历
{
	int v;
	for (v=0; v<g.n;v++) //初始化标志数组
		visited[v]=0; 
	for  (v=0; v<g.n;v++) //保证非连通图的遍历
		if (!visited[v])BFS(g,v); 
	//从第v个顶点出发递归地深度优先遍历图G
}
int main()
{
	graph g;
	creategraph(&g);
	//print(g);
	//printf("\n");
	//printf("图的深度优先遍历序列：\n");
	DFStraverse(g);
	printf("\n");
	//printf("图的广度优先遍历序列：\n");
	BFStraverse(g);
	printf("\n");
	return 0;
}
