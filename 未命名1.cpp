#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAXLEN 100//ͼ����󶥵���
#define MAXCOST 1000//�����ܵ����Ȩֵ
#define MAXVEX 100
typedef struct vertex
{
    int num;
}DataType;
typedef struct
{
    DataType vexs[MAXLEN+1];
    int edges[MAXLEN+1][MAXLEN+1];
    int n,e;
}MGraph;
typedef struct
{
    int  fromvex;  //���
    int  endvex;    //�յ�
    int  weight;    //Ȩֵ
}Edgeset[MAXVEX],Edge;
Edgeset GE ;
Edgeset TE;

void CreatGE(MGraph *G,Edgeset GE)
{
    int i,j;
    Edge temp;
    int k=1;
    for(i=1;i<=G->n;i++){
        for(j=1;j<i;j++){
            if(G->edges[i][j]!=MAXCOST)
            {
                GE[k].weight=G->edges[i][j];
                GE[k].fromvex=i;
                GE[k].endvex=j;
                k++;
            }
        }
    }
    for(i=1;i<=G->e;i++){
        for(j=1;j<=G->e-i;j++){
            if(GE[j].weight>GE[j+1].weight)
            {
                temp=GE[j];
                GE[j]=GE[j+1];
                GE[j+1]=temp;
            }
        }
    }
}

void Print(Edgeset TE)
{
    for(int i=1; i<7; i++)
        printf("(%d,%d,%d)\n", TE[i].fromvex, TE[i].endvex, TE[i].weight);
}

void kruskal(MGraph G, Edgeset GE, Edgeset TE)
{
    CreatGE(&G, GE);
    int vest[MAXVEX], i,j,k,d,m1,m2;
    for(i=1;i<=G.n;i++)     //��ʼ��������������Եķ�����
       vest[i]=i;
           //׼��ȷ���������ĵ�k���� ������GE�е�d����
    for(d=1,k=1;k<G.n&&d<=G.e; d++)
    {
        m1=vest[GE[d].fromvex];
        m2=vest[GE[d].endvex];
        if(m1!=m2)
        {
            TE[k]=GE[d];
            k++;
            for(j=1;j<=G.n;j++)
            {
                if(vest[j]==m2)      //�����������ϲ�Ϊһ��
                    vest[j]=m1;
            }
        }
    }
    Print(TE);
 }

//�ڽӾ���Ĵ���
void CreateCost(MGraph *g)
{
	int i,j,n=7,e=12;
	int er[12][2]={{3,1},{3,6},{1,6},{1,2},{6,7},{1,4},{6,4},{4,2},{4,7},{2,7},{2,5},{5,7}} ;
	int q[12]={6,7,4,18,20,23,25,12,15,8,5,10};
	g->n=n;
	g->e=e;
	for(i=1;i<=g->n;i++)
		g->vexs[i].num=i;
	for(i=1;i<=g->n;i++)
		for(j=1;j<=g->n;j++)
			g->edges[i][j]=MAXCOST;
	
    for(i=0;i<12;i++)
    {
        g->edges[er[i][0]][er[i][1]]=q[i];//����ͼʱ����������Ҫִ��
		g->edges[er[i][1]][er[i][0]]=q[i];//����ͼʱ��ִ�б������
    }
	

}
void CreateCost2(MGraph *q)
{
	int i,j,n=6,e=10;
	int er[10][2]={1,3,3,1,1,2,1,5,2,5,2,3,3,4,4,2,4,5,6,4} ;
	int k[10]={10,20,50,45,10,15,15,20,35,3};
	q->n=n;
	q->e=e;
	for(i=1;i<=q->n;i++)
		q->vexs[i].num=i;
	for(i=1;i<=q->n;i++)
		for(j=1;j<=q->n;j++)
			q->edges[i][j]=MAXCOST;
	
    for(i=0;i<10;i++)
    {
        q->edges[er[i][0]][er[i][1]]=k[i];//����ͼʱ����������Ҫִ��
    }
	

}
void  Dispath(int  dist[],int  path[],int  n,int  v)
{
    int  i,j;
    for(i=1;i<=n;i++)
    {
        if(i!=v){
            if(dist[i]==MAXCOST)
                printf("%d----->%d�����·����\n",v,i);
            else
            {
                printf("%d---->%d:  %d\n",v,i,dist[i]);  //���������i�����·������d[i]
                printf("path:  ");         //�����������·������·��
                j=i;
                while(path[j]!=v)         //ͨ��path���黹ԭ������i�����·����Ϣ
                {
                    printf("%3d",path[j]);   //�����j��ǰһ��·���ؾ���path[j]�������
                    j=path[j];            //������ǰ����ֱ����������vΪֹ
                }
                printf("%3d\n",path[j]);
            }
        }
   }
}
void dijkstra(MGraph *g,int v)
{
    int dist[MAXLEN+1];  //������·���ĳ���
	int s[MAXLEN+1];     //�����ȷ�����·���Ķ���ı�־
	int path[MAXLEN+1];  //path���鿪ʼȫ��Ϊ0
    int i,j,k,min,w;
	//��ʼ������
    for(i=1;i<=g->n;i++)
    {
        dist[i]=g->edges[v][i];
		if(i==v)
            s[i]=1;
        else
            s[i]=0;// Դ��v ���ٿ���
		if (dist[i]<MAXCOST)	//·����ʼ��
            path[i]=v;		        //����v��i�б�ʱ
        else
            path[i]=-1;
	}

//����ѭ����ִ��n-1�Σ�ÿ�ζ���������δȷ�����·���Ķ���v��dist[v]����һ����Сֵ�Լ�λ��w
//���w���Ǳ���ȷ�����ҵ����·���Ķ���
    for(k=1;k<g->n;k++)
    {
        min=MAXCOST;
        w=0;
        for(j=1;j<=g->n;j++)
            if(s[j]==0 && dist[j]<min)
    		{   min=dist[j];
        		w=j;
    		}
        printf("w=%d,min=%d\n",w,min);
        s[w]=1;//�޸�w�ı�־��˵�����ѱ�ȷ�������·����

       //���¸���dist[w]ֵ�Լ�ԭdist[i]�������ඥ��i�����·������, ͬʱ����path����ֵ
		for(i=1;i<=g->n;i++)
			if(s[i]==0&&w!=0&&(min+g->edges[w][i])<dist[i])
			{
				dist[i]=min+g->edges[w][i];
				//һ��dist[i]���޸ģ�˵����i��·���ؾ���w������㣬��˽�w��·����Ϣ���Ƶ�i�����·����
				path[i]=w;
			}
	}
    //���������Դ���·���ͳ��ȼ�·����Ϣ
    printf("\n");
    Dispath(dist,path,g->n,1);
}

void Prim(MGraph *G,int closevertex[])
{
    int lowcost[MAXLEN],i,j,k,mincost;
    for(i=1;i<=G->n;i++)
    {
        if(i==1)
            lowcost[i]=0;
        else
            lowcost[i]=G->edges[1][i];
        closevertex[i]=1;
    }
    for(i=1;i<G->n;i++)
    {
        mincost=MAXCOST;
        k=0;
        for(j=1;j<=G->n;j++)
            if(lowcost[j]!=0 && lowcost[j]<mincost)
            {
                mincost=lowcost[j];
                k=j;
            }
        if(mincost==MAXCOST)
        {
            printf("ͼ����ͨ������������\n");
            return ;
        }
    printf("(%d,%d,%d)\n",closevertex[k],k,lowcost[k]);
    lowcost[k]=0;
        for(j=1;j<=G->n;j++)
        {
            if( lowcost[j]!=0 && G->edges[k][j]<lowcost[j] )
            {
                closevertex[j]=k;
                lowcost[j]=G->edges[k][j];
            }
        }
    }
}
void menu()
{
    printf("1.��prime�㷨��ɸ����ĵ���С������\n");
    printf("2.��Kruskal�㷨��ɸ����ĵ���С������\n");
    printf("3.��dijstra�㷨����ͼ��Դ��3�������������·��\n");
}
int main()
{
    int closevertex[MAXLEN+1],n;
    MGraph *g,*q;
    g=(MGraph *)malloc(sizeof(MGraph));
    q=(MGraph *)malloc(sizeof(MGraph));
    CreateCost(g);
    CreateCost2(q);
    while(1)
    {
        menu();
        printf("��������Ҫѡ��Ĺ���\n");
        scanf("%d",&n);
        switch(n)
        {
            case 1:
                Prim(g,closevertex);
                break;
            case 2:
                kruskal(*g,GE,TE) ;
                break;
            case 3:
                dijkstra(q,3);
                break;
        }
    }
    return 0;
}

