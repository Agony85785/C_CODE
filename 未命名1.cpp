#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAXLEN 100//图的最大顶点数
#define MAXCOST 1000//不可能的最大权值
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
    int  fromvex;  //起点
    int  endvex;    //终点
    int  weight;    //权值
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
    for(i=1;i<=G.n;i++)     //初始＊各顶点归属各自的分量中
       vest[i]=i;
           //准备确定生成树的第k条边 ＊考查GE中第d条边
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
                if(vest[j]==m2)      //将两个分量合并为一个
                    vest[j]=m1;
            }
        }
    }
    Print(TE);
 }

//邻接矩阵的创建
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
        g->edges[er[i][0]][er[i][1]]=q[i];//无向图时以下两条都要执行
		g->edges[er[i][1]][er[i][0]]=q[i];//有向图时不执行本条语句
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
        q->edges[er[i][0]][er[i][1]]=k[i];//无向图时以下两条都要执行
    }
	

}
void  Dispath(int  dist[],int  path[],int  n,int  v)
{
    int  i,j;
    for(i=1;i<=n;i++)
    {
        if(i!=v){
            if(dist[i]==MAXCOST)
                printf("%d----->%d无最短路径！\n",v,i);
            else
            {
                printf("%d---->%d:  %d\n",v,i,dist[i]);  //输出到顶点i的最短路径长度d[i]
                printf("path:  ");         //这里输出的是路径的逆路径
                j=i;
                while(path[j]!=v)         //通过path数组还原到顶点i的最短路径信息
                {
                    printf("%3d",path[j]);   //顶点的j的前一步路径必经过path[j]这个顶点
                    j=path[j];            //继续向前递推直到遇到顶点v为止
                }
                printf("%3d\n",path[j]);
            }
        }
   }
}
void dijkstra(MGraph *g,int v)
{
    int dist[MAXLEN+1];  //存放最短路径的长度
	int s[MAXLEN+1];     //存放已确定最短路径的顶点的标志
	int path[MAXLEN+1];  //path数组开始全部为0
    int i,j,k,min,w;
	//初始化数组
    for(i=1;i<=g->n;i++)
    {
        dist[i]=g->edges[v][i];
		if(i==v)
            s[i]=1;
        else
            s[i]=0;// 源点v 不再考虑
		if (dist[i]<MAXCOST)	//路径初始化
            path[i]=v;		        //顶点v到i有边时
        else
            path[i]=-1;
	}

//以下循环共执行n-1次，每次都是在所有未确定最短路径的顶点v的dist[v]中找一个最小值以及位置w
//这个w就是本次确定的找到最短路径的顶点
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
        s[w]=1;//修改w的标志，说明它已被确定了最短路径了

       //以下根据dist[w]值以及原dist[i]修正其余顶点i的最短路径长度, 同时修正path数组值
		for(i=1;i<=g->n;i++)
			if(s[i]==0&&w!=0&&(min+g->edges[w][i])<dist[i])
			{
				dist[i]=min+g->edges[w][i];
				//一旦dist[i]被修改，说明到i的路径必经过w这个顶点，因此将w的路径信息复制到i顶点的路径上
				path[i]=w;
			}
	}
    //以下输出单源最短路径和长度及路径信息
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
            printf("图不连通，无生成树！\n");
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
    printf("1.用prime算法完成给出的的最小生成树\n");
    printf("2.用Kruskal算法完成给出的的最小生成树\n");
    printf("3.用dijstra算法求下图从源点3到其余各点的最短路径\n");
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
        printf("请输入你要选择的功能\n");
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

