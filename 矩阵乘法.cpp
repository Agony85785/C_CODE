#include<iostream>
using namespace std;
void MatrixChain(int *p,int n,int**m,int **s)
{
	for (int i = 1; i <= n; i++)
		m[i][i] = 0;
    for(int r=2;r<=n;r++)
	{
		for (int i = 1;i<=n-r+1;i++)
		{
			int j = i + r - 1;
			m[i][j] = m[i + 1][j] + p[i - 1] * p[i] * p[j];
			s[i][j] = i;
			for(int k=i+1;k<j;k++)
			{
				int t = m[i][k]+m[k+1][j] + p[i - 1] * p[k] * p[j];
				if(t<m[i][j])
				{
					m[i][j] = t;
					s[i][j] = k;
				}
			}
			
		}
	}
	
}

void Traceback(int i, int j,int **s)
{
	if (i == j)
	{
		cout << "A[" << i << "]";
		return;
	}
	cout << "(";
	Traceback(i, s[i][j], s);
	Traceback(s[i][j]+1, j, s);
	cout << ")";
}
int main()
{
	int p[11];
	void Traceback(int i, int j,int** s);
	void MatrixChain(int* p, int n, int** m, int** s);
	int**m=new int* [11],**s=new int*[11];
	for (int i = 0; i < 11; i++)
	{
		m[i] = new int[11];
		s[i] = new int[11];
	}
	for (int i = 0; i <= 10; i++)
		p[i] = i + 1;
	MatrixChain(p,10,m ,s);
	cout << "该A[1:10]矩阵连乘的最优计算次序为：";
	Traceback(1, 10, s);
	//for (int i = 1; i <= 10; i++)
	//{
	//	for (int j = 1; j <= 10; j++)
	//	{if(i<=j)
	//		cout << "m["<<i<<"]["<<j<<"]:"<<m[i][j] <<"   ";
	//	}
	//	cout << endl;
	//}
	cout << "\n最小计算量的值为：" << m[1][10];
}