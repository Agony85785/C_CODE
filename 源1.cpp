#include<iostream>
using namespace std;
void LCSLength(int m,int n,char*x,char*y,int **c,int **b)
{
	int i, j;
	for (i = 0; i <= m; i++)
		c[i][0] = 0;
	for (i = 0; i <= n; i++)
		c[0][i] = 0;
	for(i=1;i<=m;i++)
	{
		for (j = 1; j <= n; j++)
		{if (x[i]==y[j])
		{
			c[i][j] = c[i - 1][j - 1] + 1;
			b[i][j] = 1;
		}
		else if(c[i-1][j] >= c[i][j - 1])
		{
			c[i][j] = c[i - 1][j];
			b[i][j] = 2;
		}
		else
		{
			c[i][j] = c[i][j-1];
			b[i][j] = 3;
		}
		}
	}
		
}
void  LCS(int i, int j, char* x, int** b)
{
	if (i == 0 || j == 0)
		return;
	if (b[i][j] == 1)
	{
		LCS(i - 1, j - 1, x, b);
		cout << x[i];
	}
	else if (b[i][j] == 2)
		LCS(i - 1, j, x, b);
	else
		LCS(i, j - 1, x, b);
}
int main()
{
	char x[11] = { '*', 'A','R','S','B','A','C','E','B','E','Y'};
	char y[9] = { '*','A','B','C','A','E','Q','E','I'};
	int** c = new int* [11], ** b = new int* [11];
	for (int i = 0; i < 11; i++)
	{
		c[i] = new int[9];
		b[i] = new int[9];
	}
	void  LCS(int i, int j, char* x, int** b);
	void LCSLength(int m, int n, char* x, char* y, int** c, int** b);
	LCSLength(10, 8, x, y, c, b);
	cout << "该问题的最长公共子序列为：";
	LCS(10, 8, x, b);
}