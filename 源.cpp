#include<iostream>
using namespace std;
int flag = true,i=1;
int BSearch(int a[],int x,int m,int n)
{
	int left = m, right = n;
	if(left>=right&&x!=a[left])
	{
		cout << "抱歉，没有这个数" << endl;
		return 0;
	}
	if (flag = true)
	{
		flag = false;
		if (x == a[0])
		{
			cout << "找到了,该数在数组中的下标为：0" << endl;
			return 0;
		}
	}
	while(left<=right)
	{
		int middle = (left + right) / 2;
		if (x == a[middle])
			return middle;
		if (x > a[middle])
		{
			cout << "子问题划分为[" << i << "]:在数组arr[" << middle + 1 << "]-arr[" << right << "]中继续查找" << endl; i++;
			return BSearch(a, x, middle + 1, right);
		}
		if (x < a[middle])
		{
			cout << "子问题划分为[" << i << "]:在数组arr[" << left << "]-arr[" << middle - 1 << "]中继续查找" << endl; i++;
			return BSearch(a, x, left, middle - 1);
		}
	}
}

int main()
{
	int a, b, res, arr[200];
	for (a = 0; a < 200; a++)
		arr[a] = a;
	int sz = sizeof(arr) / sizeof(arr[0]);
	cout << "请输入你要查找的数：" << endl;
	cin >> b;
	res = BSearch(arr, b, 0, sz - 1);
	if (res != 0)
		cout << "找到了,该数在数组中的下标为："<<res << endl;
}