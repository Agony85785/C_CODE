#include<stdio.h>
#include<string.h>
#include<malloc.h>
#define MAX 1000
#define N 4
#define M 2*N 
typedef struct  
{  float weight ; // 结点权值  
int parent, lchild, rchild ; //双亲及左右孩子的下标值  
} HafuNode , *HafuTree ;  
HafuTree tree[M] ; 
 void HuffMan(HafuNode tree[],char w[],int n) 
 { int i,j,p1,p2;  
 float small1,small2;  
 for(i=1;i<=n;i++)  
 { tree[i].weight=w[i]; 
 tree[i].parent=0; 
 tree[i].lchild=0; 
 tree[i].rchild=0; }  
 for(;i<2*n;i++)  
   { tree[i].weight=MAX; 
   tree[i].parent=0; 
   tree[i].lchild=0; 
   tree[i].rchild=0; 
   }  
for(i=n+1;i<2*n;i++)  
   { p1=0; p2=0; 
   small1=small2=MAX; //给一个足够大的初值  
   for(j=1;j<=i;j++)  
     { if(tree[j].parent==0)  
	     if(tree[j].weight<small1)  
		   { small2=small1; 
		   small1=tree[j].weight; 
		   p2=p1; p1=j; 
		   }  
		 else if(tree[j].weight<small2)  
		   { small2=tree[j].weight; 
		   p2=j; 
		   }  
	   }  
	   tree[p1].parent=i;
	    tree[p2].parent=i; 
		tree[i].lchild=p1; 
		tree[i].rchild=p2;  
		tree[i].weight=tree[p1].weight+tree[p2].weight;  
	} 
} 
typedef struct
{int weight;
int lchild,rchild,parent;
char data;
 } HFNODE, *HUFFMANTREE; 
typedef char HUFFMANCODE[M][M];
HUFFMANCODE hc; 
//生成各字符对应的哈夫曼编码的C语言函数 
huffmancoding(int n, HUFFMANCODE hc,HUFFMANTREE ht, char ch[]) 
{ int i,start,child,father; 
char *cd; cd=(char*)malloc(n*sizeof(char)); //动态申请n个字符空间 
cd[n-1]='\0'; //先设置字符串的结束标志位 
for(i=1;i<=n;i++) 
{  start=n-1;  
for(child=i,father=ht[i].parent;father!=0;child=father,father=ht[father].parent)  
{  if(ht[father].lchild==child) //该结点是其双亲结点的左孩子，则该位为0,否则为1  
cd[--start]='0';  
else  cd[--start]='1';   }  
strcpy(hc[i],&cd[start]); //将第i个哈夫码编码复制到哈夫曼编码数组中。 
}  
free(cd); 
for(i=1;i<=n;i++) //输出n个哈夫曼编码  
   printf("%s %c\n",hc[i],ch[i]);  
} 
void menu()
{printf("1.输入一段文字，统计其中不同字符出现频度，按此频度创建哈夫曼树\n");
printf("2.给出各个字符的哈夫曼编码，将上述文字按编码译为密码文字输出\n");
printf("3.退出程序\n");
}
int main()
{int n,o,i=0,j=0,lv,flag=0,flag2=1;
HafuNode tree1[20];
HUFFMANTREE ht;
char m[20],w[20],chu='1',shu[20],a;
while(flag2)
{menu();
printf("请输入你想选择的功能\n");
scanf("%d",&o);
switch(o)
{case 1:printf("请输入一段文字\n");
scanf("%s",m);
for(i=0;m[i]!='\0';i++)
 {if(m[i]==chu)
    {
	flag++;
    continue;}
 else
  shu[i-flag]=m[i];
  m[i]=chu;
 
 for(j=0;m[j]!='\0';j++)
   {
   if(shu[i-flag]==m[j])
    w[i]++;
   }
   for(j=0;m[j]!='\0';j++)
   {if(shu[i-flag]==m[j])
    m[j]=chu;
   }
}
for(n=0,i=0;shu[i]!='\0';i++)
{printf("%c",shu[i]);
n++;
}
printf("\n%d\n",n);
HuffMan(tree1,w,n);
printf("建立成功 \n");
break;
case 2:huffmancoding(n,hc,ht,shu);break;
case 3:flag2=0;break;
}
}
return 0;
}
