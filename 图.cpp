#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAXLEN 100
#define QUEUESIZE 100
 //邻接表类型定义
 typedef struct node
 {int adjvex;
 struct node *next;
  } EdgeNode;//边链表结点类型 
  typedef struct
  {int vertex;
  EdgeNode *firstedge;
  }VertexNode;//表头结点类型 
typedef VertexNode AdjList[MAXLEN+1];
typedef struct
{AdjList adjlist;
int n,e;
}ALGraph;//图的邻接表类型 
//邻接表的建立 
void CreatesAdjList(	ALGraph *g,int n,int e)
{
	EdgeNode *ptr;
	int k,v1,v2;
	g->n=n;g->e=e;
	for(k=1;k<=g->n;k++)           //初始化表头数组的指针域为空
		g->adjlist[k].firstedge=NULL;
	for(k=1;k<=g->e;k++)             //建立邻接表
	{
		printf("v1,v2= ");
		scanf("%d%d",&v1,&v2);      //输入一对边的起、终结点的序号值
		ptr=(EdgeNode*)malloc(sizeof(EdgeNode));//动态申请一个边链表结点空间
		ptr->adjvex=v2;      //将该边的终点写入数据域
		ptr->next=g->adjlist[v1].firstedge;//以下两句是将该结点插入到链表头处
		g->adjlist[v1].firstedge=ptr;
		//若为有向图，则以下几句不执行
		ptr=(EdgeNode*)malloc(sizeof(EdgeNode));//动态申请一个边链表结点空间
		ptr->adjvex=v1;      //将该边的终点写入数据域
		ptr->next=g->adjlist[v2].firstedge;//以下两句是将该结点插入到链表头处
		g->adjlist[v2].firstedge=ptr;

	}
}
//邻接矩阵的类型定义
typedef struct vertex
{int num;
 } DataType;
 typedef struct
 {DataType vexs[MAXLEN+1];
 int edges[MAXLEN+1][MAXLEN+1];
 int n,e;
 }MGraph;
//邻接矩阵的创建 
void CreateCost(MGraph *g,int n,int e)
{
	int i,j,k,v1,v2;
	g->n=n;g->e=e;
	for(i=1;i<=g->n;i++)
		g->vexs[i].num=i;
	for(i=1;i<=g->n;i++)
		for(j=1;j<=g->n;j++)
			g->edges[i][j]=0;
	for(k=1;k<=g->e;k++)
	{
		//printf("v1,v2= ");
		scanf("%d%d",&v1,&v2);
		g->edges[v1][v2]=1;//无向图时以下两条都要执行
		g->edges[v2][v1]=1;//有向图时不执行本条语句
	}
	
} 
//深度遍历
int visited[MAXLEN+1];
void  DFS(MGraph  *g , int  i)    //从顶点i开始深度遍历
{  int  j;
   printf("%3d",g->vexs[i].num);   //遍历起始顶点
   visited[i]=1;                  //将被访问顶点的访问标志设置为1，表示已访问
   for(j=1;j<=g->n;j++)
     if((g->edges[i][j]==1)&&!visited[j])
        DFS(g,j);               //对未访问的邻接顶点递归调用
}
void  DFSTraverse(MGraph  *g)  //基于邻接矩阵的深度遍历操作
 {  int  i;
    for(i=1;i<=g->n;i++)
       visited[i]=0;             //初始所有顶点状态是未访问过状态
    for(i=1; i<=g->n; i++)
       if(!visited[i])
          DFS(g,i);            //对未访问过的顶点调用DFS
   }
//队列
typedef struct { int data[QUEUESIZE];  int front,rear; } SeqQueue;
void InitQueue(SeqQueue *q)
{
    q->front=q->rear=0;
}
int EnQueue(SeqQueue *q, int x)
{
    if(q->rear==100)
    {
        printf("队列已满，无法入队\n");
        return 0;
    }
    q->data[q->rear]=x;
    q->rear++;
    return 1;
}
int DeQueue(SeqQueue *q,int*x)
{
    if(q->front==q->rear)
    {
        printf("队列已空，无法出队\n");
        return 0;
    }
    *x=q->data[q->front];
    q->front++;
    return 1;
 } 
//广度遍历

 void visit(int v)
 {printf("%3d",v);
 }
 int QueueEmpty(SeqQueue*q)
 {if(q->rear==q->front) return 1;
 else return 0;
 }
void  BFS(MGraph  *g, int  v)  //从顶点v开始广度遍历算法
{  int  i,j;
    for(i=1;i<=g->n;i++)
       visited[i]=0; 
    SeqQueue  q;      //q为顺序队列变量
    InitQueue(&q);     //队列q初始化
    visit(v);            //调用函数访问顶点v，通常功能是输出其顶点信息
    visited[v]=1;        //置访问标志为1，表示此点已访问过
    EnQueue(&q, v);                 //顶点v进队列
    while (!QueueEmpty(&q))           //当队列q非空
      {  DeQueue(&q, &v);            //队列q非空时，顶点v出队
          for(j=1;j<=g->n;j++)        //在顶点v对应行中进行搜索那些还未遍历的顶点 
              if(g->edges[v][j]==1 && !visited[j])//矩阵下标从0开始，而顶点从1编号的
	             {  visit(j);  visited[j]=1;  //访问j并修改被问标志
	                 EnQueue(&q, j);      //顶点j入队
	             }
    }
}
void  BFSTraverse(MGraph  *g)  //基于邻接矩阵的深度遍历操作
 {  int  i;
    for(i=1;i<=g->n;i++)
       visited[i]=0;             //初始所有顶点状态是未访问过状态
    for(i=1; i<=g->n; i++)
       if(!visited[i])
          BFS(g,i);            //对未访问过的顶点调用DFS
   }
void menu()
{printf("\n1.邻接表的建立\n");
printf("2.邻接矩阵的创建\n");
printf("3.基于邻接矩阵的深度遍历\n");
printf("4.基于邻接矩阵的广度遍历\n");
printf("5.编写在图中查找某一指定顶点的算法。若找到，则输出该顶点的有邻接顶点，否则显示查无此结点\n");
printf("6.退出系统\n");
 } 
 int main()
 {int flag=1,k,n,e,flag1=0,i,j;
 ALGraph *g;
 MGraph *a;
 a=(MGraph *)malloc(sizeof(MGraph));
 g=(ALGraph *)malloc(sizeof(ALGraph));
 while(flag)
 {menu();
 printf("请输入你想选择的功能\n");
 scanf("%d",&k);
 switch(k)
 {case 1:printf("请分别输入顶点个数和边的个数\n");
         scanf("%d%d",&n,&e);
         CreatesAdjList(g,n, e);break;
 case 2:printf("请分别输入顶点个数和边的个数\n");//7 12
        scanf("%d%d",&n,&e);                     //3 1 3 6 1 6 1 2 6 7 1 4 6 4 4 2 4 7 2 7 2 5 5 7
        CreateCost(a,n,e);break;
 case 3:DFSTraverse(a);break;
 case 4:BFSTraverse(a) ;break;
 case 5://编写在图中查找某一指定顶点的算法。若找到，则输出该顶点的有邻接顶点，否则显示查无此结点
        printf("请输入你要查找的顶点\n");
        scanf("%d",&n);
        flag1=0;
        for(i=1;i<a->n+1;i++)
        {if(n==a->vexs[i].num)
         {
		 flag1=1;break;}
		}
		if(flag1==1)
	    	for(j=1;j<a->n+1;j++)
		   {if(a->edges[i][j]==1)
		    visit(a->vexs[j].num);		  
		   }
		else
		  printf("查无此结点\n");
 break;
 case 6:flag=0;break;
 }
 }
 return 0;
 }
