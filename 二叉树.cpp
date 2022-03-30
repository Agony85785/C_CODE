
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#define DataType char
//�������Ķ�������ṹ����
typedef struct Node
{
    DataType data;
    struct Node *lchild;
    struct Node *rchild;
}BiTreeNode,*BiTree;
 //�����½��
void Initiate(BiTree *root,DataType x)
{
    *root=(BiTree)malloc(sizeof(BiTreeNode));
    (*root)->data=x;
    (*root)->lchild=NULL;
    (*root)->rchild=NULL;
}
//�ڽ�����Ӵ������½��
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
//�ڽ���Һ��Ӵ������½��
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
//�������Ľ���
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
    printf("�����������ɹ� \n");
}
//���������������ͳ��Ҷ�ӽ�����
int shu=0;//Ҷ�ӽ�����
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
//���ж���
typedef struct
{
    BiTree data[100];
    int front;
    int rear;
}SeqQueue;
//˳����г�ʼ��
void InitQueue(SeqQueue *q)
{
    q->front=q->rear=0;
}
//���
int EnQueue(SeqQueue *q, BiTree x)
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
//����
int DeQueue(SeqQueue *q, BiTree *x)
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
//�����������
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
 //�ж�һ���������Ƿ�����ȫ������(�㼶����)
void LevelTraverse(BiTree root)
{
    //BiTreeNode k;//��ΪNULL��k���
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
            printf("����ȫ������\n");
            flag = 1;
            break;
        }
    }
    if(flag == 0)
        printf("��ȫ������\n");
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
            printf("�ö���������ȫ������\n");
        if(flag==1)
            printf("�ö������ǲ���ȫ������\n");
        }
    }*/
	 }
	void menu()
	{
	    printf("\n");
	    printf("1.ͳ��һ������������Ҷ�ӽ��ĸ���\n");
	    printf("2.��ɼ���һ���������ĸ߶�\n");
	    printf("3.�ж�һ���������Ƿ�����ȫ������\n");
	    printf("4.�˳�\n");
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
	        printf("����������ѡ��Ĺ���\n");
	        scanf("%d",&n);
	        switch(n)
	        {
	            case 1:
	                PreOrder(root);
	                printf("��������Ҷ�ӽ��ĸ���Ϊ%d\n",shu);
	                break;
	            case 2:
	                n=GetTreeDeep(root);
	                printf("���������Ϊ%d\n",n);
	                break;
	            case 3:
	                LevelTraverse(root);
	                break;
	            case 4:
	                printf("�������н���\n");
	                return 0;
	            default:
	                printf("�������\n");
	        }
	    }
	    //return 0;
	}
