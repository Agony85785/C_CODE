#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAXLEN 100
#define QUEUESIZE 100
 //�ڽӱ����Ͷ���
 typedef struct node
 {int adjvex;
 struct node *next;
  } EdgeNode;//������������ 
  typedef struct
  {int vertex;
  EdgeNode *firstedge;
  }VertexNode;//��ͷ������� 
typedef VertexNode AdjList[MAXLEN+1];
typedef struct
{AdjList adjlist;
int n,e;
}ALGraph;//ͼ���ڽӱ����� 
//�ڽӱ�Ľ��� 
void CreatesAdjList(	ALGraph *g,int n,int e)
{
	EdgeNode *ptr;
	int k,v1,v2;
	g->n=n;g->e=e;
	for(k=1;k<=g->n;k++)           //��ʼ����ͷ�����ָ����Ϊ��
		g->adjlist[k].firstedge=NULL;
	for(k=1;k<=g->e;k++)             //�����ڽӱ�
	{
		printf("v1,v2= ");
		scanf("%d%d",&v1,&v2);      //����һ�Աߵ����ս������ֵ
		ptr=(EdgeNode*)malloc(sizeof(EdgeNode));//��̬����һ����������ռ�
		ptr->adjvex=v2;      //���ñߵ��յ�д��������
		ptr->next=g->adjlist[v1].firstedge;//���������ǽ��ý����뵽����ͷ��
		g->adjlist[v1].firstedge=ptr;
		//��Ϊ����ͼ�������¼��䲻ִ��
		ptr=(EdgeNode*)malloc(sizeof(EdgeNode));//��̬����һ����������ռ�
		ptr->adjvex=v1;      //���ñߵ��յ�д��������
		ptr->next=g->adjlist[v2].firstedge;//���������ǽ��ý����뵽����ͷ��
		g->adjlist[v2].firstedge=ptr;

	}
}
//�ڽӾ�������Ͷ���
typedef struct vertex
{int num;
 } DataType;
 typedef struct
 {DataType vexs[MAXLEN+1];
 int edges[MAXLEN+1][MAXLEN+1];
 int n,e;
 }MGraph;
//�ڽӾ���Ĵ��� 
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
		g->edges[v1][v2]=1;//����ͼʱ����������Ҫִ��
		g->edges[v2][v1]=1;//����ͼʱ��ִ�б������
	}
	
} 
//��ȱ���
int visited[MAXLEN+1];
void  DFS(MGraph  *g , int  i)    //�Ӷ���i��ʼ��ȱ���
{  int  j;
   printf("%3d",g->vexs[i].num);   //������ʼ����
   visited[i]=1;                  //�������ʶ���ķ��ʱ�־����Ϊ1����ʾ�ѷ���
   for(j=1;j<=g->n;j++)
     if((g->edges[i][j]==1)&&!visited[j])
        DFS(g,j);               //��δ���ʵ��ڽӶ���ݹ����
}
void  DFSTraverse(MGraph  *g)  //�����ڽӾ������ȱ�������
 {  int  i;
    for(i=1;i<=g->n;i++)
       visited[i]=0;             //��ʼ���ж���״̬��δ���ʹ�״̬
    for(i=1; i<=g->n; i++)
       if(!visited[i])
          DFS(g,i);            //��δ���ʹ��Ķ������DFS
   }
//����
typedef struct { int data[QUEUESIZE];  int front,rear; } SeqQueue;
void InitQueue(SeqQueue *q)
{
    q->front=q->rear=0;
}
int EnQueue(SeqQueue *q, int x)
{
    if(q->rear==100)
    {
        printf("�����������޷����\n");
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
        printf("�����ѿգ��޷�����\n");
        return 0;
    }
    *x=q->data[q->front];
    q->front++;
    return 1;
 } 
//��ȱ���

 void visit(int v)
 {printf("%3d",v);
 }
 int QueueEmpty(SeqQueue*q)
 {if(q->rear==q->front) return 1;
 else return 0;
 }
void  BFS(MGraph  *g, int  v)  //�Ӷ���v��ʼ��ȱ����㷨
{  int  i,j;
    for(i=1;i<=g->n;i++)
       visited[i]=0; 
    SeqQueue  q;      //qΪ˳����б���
    InitQueue(&q);     //����q��ʼ��
    visit(v);            //���ú������ʶ���v��ͨ������������䶥����Ϣ
    visited[v]=1;        //�÷��ʱ�־Ϊ1����ʾ�˵��ѷ��ʹ�
    EnQueue(&q, v);                 //����v������
    while (!QueueEmpty(&q))           //������q�ǿ�
      {  DeQueue(&q, &v);            //����q�ǿ�ʱ������v����
          for(j=1;j<=g->n;j++)        //�ڶ���v��Ӧ���н���������Щ��δ�����Ķ��� 
              if(g->edges[v][j]==1 && !visited[j])//�����±��0��ʼ���������1��ŵ�
	             {  visit(j);  visited[j]=1;  //����j���޸ı��ʱ�־
	                 EnQueue(&q, j);      //����j���
	             }
    }
}
void  BFSTraverse(MGraph  *g)  //�����ڽӾ������ȱ�������
 {  int  i;
    for(i=1;i<=g->n;i++)
       visited[i]=0;             //��ʼ���ж���״̬��δ���ʹ�״̬
    for(i=1; i<=g->n; i++)
       if(!visited[i])
          BFS(g,i);            //��δ���ʹ��Ķ������DFS
   }
void menu()
{printf("\n1.�ڽӱ�Ľ���\n");
printf("2.�ڽӾ���Ĵ���\n");
printf("3.�����ڽӾ������ȱ���\n");
printf("4.�����ڽӾ���Ĺ�ȱ���\n");
printf("5.��д��ͼ�в���ĳһָ��������㷨�����ҵ���������ö�������ڽӶ��㣬������ʾ���޴˽��\n");
printf("6.�˳�ϵͳ\n");
 } 
 int main()
 {int flag=1,k,n,e,flag1=0,i,j;
 ALGraph *g;
 MGraph *a;
 a=(MGraph *)malloc(sizeof(MGraph));
 g=(ALGraph *)malloc(sizeof(ALGraph));
 while(flag)
 {menu();
 printf("����������ѡ��Ĺ���\n");
 scanf("%d",&k);
 switch(k)
 {case 1:printf("��ֱ����붥������ͱߵĸ���\n");
         scanf("%d%d",&n,&e);
         CreatesAdjList(g,n, e);break;
 case 2:printf("��ֱ����붥������ͱߵĸ���\n");//7 12
        scanf("%d%d",&n,&e);                     //3 1 3 6 1 6 1 2 6 7 1 4 6 4 4 2 4 7 2 7 2 5 5 7
        CreateCost(a,n,e);break;
 case 3:DFSTraverse(a);break;
 case 4:BFSTraverse(a) ;break;
 case 5://��д��ͼ�в���ĳһָ��������㷨�����ҵ���������ö�������ڽӶ��㣬������ʾ���޴˽��
        printf("��������Ҫ���ҵĶ���\n");
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
		  printf("���޴˽��\n");
 break;
 case 6:flag=0;break;
 }
 }
 return 0;
 }
