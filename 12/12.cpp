#include <iostream>
#include <cmath>
#include <cstdio>
#include <algorithm>

using namespace std;

int N;//图的顶点数
int M;//色彩数
class Color
{
	friend int mColoring(int, int, int **);
private:
	bool Ok(int k);
	void Backtrack(int t);
	int n;		//图的顶点数
	int	m;		//可用的颜色数
	int	**a;	//图的邻接矩阵
	int	*x;		//当前解
	long sum;	//当前已找到的可m着色方案数
};
int mColoring(int n, int m, int **a);
/*
输入示例：
4 3
0 1 1 1
1 0 0 1
1 0 0 1
1 1 1 0
*/ 
int main()
{
	cout << "请输入图G的顶点数和彩色数:" << endl;
	cin>>N>>M; 
	int **a = new int *[N + 1];
	for (int i = 1; i <= N; i++)
	{
		a[i] = new int[N + 1];
	}
	cout << "请输入图G的邻接矩阵:" << endl;
	for (int i = 1; i <= N; i++)
	{
		for (int j = 1; j <= N; j++)
		{
			cin >> a[i][j];
		}
		cout << endl;
	}
	int sum=mColoring(N, M, a);
	if(sum>0) 
	{
		cout << "图G的着色方案如下：" << endl;
		cout << "当m=" << M << "时，图G的可行着色方案数目为：" << sum << endl;
	}
	else
		cout<<"NO"<<endl;
	for (int i = 1; i <= N; i++)
	{
		delete[] a[i];
	}
	delete[]a;
}


void Color::Backtrack(int t)
{
	if (t > n)
	{
		//当最后一个点被着色后，此时i大于n，即所有点已染色完成
		sum++;
		//打印出此种方案的结果
		for (int i = 1; i <= n; i++)
			cout << x[i] << " ";
		cout << endl;
	}
	else
	{
		//开始给一个点添加颜色，同时判断其可行性，
		for (int i = 1; i <= m; i++)
		{
			//给改点图上m号颜色
			x[t] = i;
			//若此种颜色可行，即执行进行深层次的着色
			if (Ok(t)) Backtrack(t + 1);
			//将该点恢复到原来的状态
			x[t] = 0;
		}
	}
}


bool Color::Ok(int k)// 检查颜色可用性
{
	for (int j = 1; j <= n; j++)
	{
		if ((a[k][j] == 1) && (x[j] == x[k])) //相邻且颜色相同
		{
			return false;
		}
	}
	return true;
}


int mColoring(int n, int m, int **a)
{
	Color X;
	//初始化X
	X.n = n;
	X.m = m;
	X.a = a;
	X.sum = 0;
	int *p = new int[n + 1];
	for (int i = 0; i <= n; i++)
	{
		p[i] = 0;
	}
	X.x = p;
	X.Backtrack(1);
	delete[]p;
	return X.sum;
}

