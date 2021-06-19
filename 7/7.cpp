#include <stdio.h>
#include <stdlib.h>
#include<math.h>
int main() {
	//有n个项目，分配m万元 
	int n = 4, m = 5;
	//f[3][2]表示第3个项目投资2万元能够获得多少利润 
	int f[5][6] = { {0}, {0,11,12,13,14,15},{0,0,5,10,15,20},{0,2,10,30,32,40},{0,20,21,22,23,24} };
	//F[3][2]表示2万元投资3个项目获得的最大利润 
	int F[5][6] = { {0} };
	//x[3][2]表示总共分配2万元，在获得最大利润时，对第3个项目分配的金额 
	int x[5][6] = { {0} };
	//num用来存储投资m万元，每个项目分配的金额 
	int num[5] = { 0 };
	//max存储最大利润 
	int max;
	//只有1个项目时，最大利润就是投资多少，获得多少利润 
	for (int i = 0; i < 6; i++) {
		F[1][i] = f[1][i];
		x[1][i] = i;
	}
	//从2个项目开始 
	for (int k = 2; k <= n; k++) {
		for (int i = 1; i <= m; i++) {
			max = -1;
			for (int j = 0; j <= i; j++) {
				if (max <= F[k - 1][i - j]+f[k][j]) {
					max=F[k - 1][i - j] + f[k][j];
					x[k][i] = j;
				}
			}
			F[k][i] = max;
		}
	}
	for (int i = n; i > 0; i--) {
		num[i]= x[i][m];
		m = m - x[i][m];
	}
	//输出结果 
	for (int i = 1; i <= n; i++) {
		printf("第%d个项目%d万元 ",i, num[i]);
	}
	printf("\n最大利润：%d", max);
	return 0;
}
