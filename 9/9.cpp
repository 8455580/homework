#include<stdio.h>
#define MAX 100
int c[MAX][MAX], b[MAX][MAX],d[MAX];
void LongChain(int x[],int y[],int m,int n){
	c[0][0] = { 0 };
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			if (x[i-1] == y[j-1]) {
				c[i][j] = c[i - 1][j - 1] + 1;
				b[i][j] = 2;	//2表示删除两个
			}
			else if (c[i][j - 1] >= c[i - 1][j]) {
				c[i][j] = c[i][j - 1];
				b[i][j] = 1;	//1表示删除y
			}
			else {
				c[i][j] = c[i - 1][j];
				b[i][j] = 0;	//0表示删除x
			}
		}
	}
}
void f(int x[],int i,int j) {
	if (i == 0 || j == 0)
		return;
	if (b[i][j] == 2) {
		f(x, i - 1, j - 1);
		printf("%d ", x[i - 1]);	//当b[i][j]==2时，表示该元素为两个序列的公共元素，则输出该元素
	}
	else if (b[i][j] == 0) {
		f(x, i - 1, j);
	}
	else
	{
		f(x, i, j - 1);
	}
}
/*
当x= 1,2,3,4,2,5 ,y= 2,4,1,3,5时
输出最长子序列为2 4 5
*/
int main()
{
	int x[] = { 1,2,3,4,2,5 };
	int y[] = { 2,4,1,3,5 };
	LongChain(x, y, 6, 5);
	f(x, 6, 5);
	return 0;
}

