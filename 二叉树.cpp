
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#define DataType char
//二叉树的二叉链表结构定义
typedef struct Node
{
    DataType data;
    struct Node *lchild;
    struct Node *rchild;
}BiTreeNode,*BiTree;
 //申请新结点
void Initiate(BiTree *root,DataType x)
{
    *root=(BiTree)malloc(sizeof(BiTreeNode));
    (*root)->data=x;
    (*root)->lchild=NULL;
    (*root)->rchild=NULL;
}
//在结点左孩子处插入新结点
BiTree InsertLeftNode(BiTree curr,DataType x)
{
    BiTree s,t;
    if(curr==NULL)
        return NULL;
    t=curr->lchild;
    s=(BiTree)malloc(sizeof(BiTreeNode));
    s->data=x;
    s->lchild=t;
    s->rchild=NULL;
    curr->lchild=s;
    return curr->lchild;
}
//在结点右孩子处插入新结点
BiTree InsertRightNode(BiTree curr,DataType x)
{
    BiTree s,t;
    if(curr==NULL)
        return NULL;
    t=curr->rchild;
    s=(BiTree)malloc(sizeof(BiTreeNode));
    s->data=x;
    s->rchild=t;
    s->lchild=NULL;
    curr->rchild=s;
    return curr->rchild;
}
//二叉树的建立
void CreatBiTree(BiTree*root)
{
    BiTree p;
    Initiate(root,'A');
    p=InsertLeftNode(*root,'B');
    p=InsertRightNode(p,'D');
    p=InsertRightNode(p,'G');
    p=InsertRightNode(*root,'C');
    InsertLeftNode(p,'E');
    InsertRightNode(p,'F');
    printf("二叉树建立成功 \n");
}
//二叉树的先序遍历统计叶子结点个数
int shu=0;//叶子结点个数
void PreOrder(BiTree root)
{
    if(root)
    {
        if(root->lchild==NULL&&root->rchild==NULL)
            shu++;
        PreOrder(root->lchild);
        PreOrder(root->rchild);
    }
}
//队列定义
typedef struct
{
    BiTree data[100];
    int front;
    int rear;
}SeqQueue;
//顺序队列初始化
void InitQueue(SeqQueue *q)
{
    q->front=q->rear=0;
}
//入队
int EnQueue(SeqQueue *q, BiTree x)
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
//出队
int DeQueue(SeqQueue *q, BiTree *x)
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
//二叉树求深度
int GetTreeDeep(BiTree T)
{
    int a,b;
    if(T==NULL)
        return 0;
    else
    {
        a=GetTreeDeep(T->lchild);
        b=GetTreeDeep(T->rchild);
        return (a>b)? (a+1):(b+1);
    }
 }
 //判定一个二叉树是否是完全二叉树(层级遍历)
void LevelTraverse(BiTree root)
{
    //BiTreeNode k;//若为NULL则k入队
    int flag=0;
    SeqQueue *sq;
    sq = (SeqQueue*)malloc(sizeof(SeqQueue));
    BiTree p=root;
    InitQueue(sq);
    EnQueue(sq, p);
    DeQueue(sq, &p);
    while(p)
    {
        EnQueue(sq, p->lchild);
        EnQueue(sq, p->rchild);
        DeQueue(sq, &p);
    }
    while(sq->front!=sq->rear)
    {
        DeQueue(sq, &p);
        if(p!=NULL)
        {
            printf("非完全二叉树\n");
            flag = 1;
            break;
        }
    }
    if(flag == 0)
        printf("完全二叉树\n");
    /*if(p!=NULL)
    {
        EnQueue(sq, p);
        while(sq->front!=sq->rear)
        {
            DeQueue(sq,p);
            if(p!=NULL)
            {
                if(p->lchild!=NULL)
                    EnQueue(sq,p->lchild);
                else
                    EnQueue(sq,k);
                if(p->rchild!=NULL)
                    EnQueue(sq,p->rchild);
                else
                    EnQueue(sq,k);
            }
            else
                while(sq->front!=sq->rear)
                {
                    DeQueue(sq,p);
                    if(*p==k)
                    {
                        flag=0;
                    }
                    else
                        flag=1;

                }
        if(flag==0)
            printf("该二叉树是完全二叉树\n");
        if(flag==1)
            printf("该二叉树是不完全二叉树\n");
        }
    }*/
	 }
	void menu()
	{
	    printf("\n");
	    printf("1.统计一个二叉树的中叶子结点的个数\n");
	    printf("2.完成计算一个二叉树的高度\n");
	    printf("3.判定一个二叉树是否是完全二叉树\n");
	    printf("4.退出\n");
	    printf("\n");
	}
	int main()
	{
	    int n;
	    BiTree root;
	    CreatBiTree(&root);
	    while(1)
	    {
	        menu();
	        printf("请输入你想选择的功能\n");
	        scanf("%d",&n);
	        switch(n)
	        {
	            case 1:
	                PreOrder(root);
	                printf("二叉树中叶子结点的个数为%d\n",shu);
	                break;
	            case 2:
	                n=GetTreeDeep(root);
	                printf("二叉树深度为%d\n",n);
	                break;
	            case 3:
	                LevelTraverse(root);
	                break;
	            case 4:
	                printf("程序运行结束\n");
	                return 0;
	            default:
	                printf("输入错误\n");
	        }
	    }
	    //return 0;
	}
