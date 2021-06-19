#include <stdio.h>
#include <stdlib.h>
#define NUM 20 //最大容量 
#define VertexType int
#define INF 65535
typedef struct Graph {
	VertexType vertex[NUM]; //存放顶点的数组
	int matrix[NUM][NUM] = {}; //邻接矩阵
	int dis[NUM][NUM];			//各个顶点出发到其他顶点的距离
	int p[NUM][NUM];	//前驱表
	int vexnum,arcnum; //vernum为顶点个数，arcnum为边数
} Graph;
//初始化连通图 
void CreateG(Graph &G) {
	int v1=0, v2=0,dis=0;
	//输入顶点数vexnum，边数arcnum
	scanf("%d %d", &G.vexnum, &G.arcnum);
	for (int i = 1; i <= G.vexnum; ++i) {
		scanf("%d",&G.vertex[i]);
	}
	for (int i = 1; i <= G.vexnum; ++i) {
		for (int j = 1; j <= G.vexnum; ++j) {
			if (i != j) {
				G.matrix[i][j] = INF;
			}
			G.p[i][j] = G.vertex[i];
		}
	}
	//输入从v1顶点到v2顶点的距离
	for (int i = 1; i <= G.arcnum; ++i) {
		scanf("%d %d %d", &v1, &v2,&dis);
		G.matrix[v1][v2] = dis;
	}
}
//flod算法
void Floyd(Graph &G) {
	//从中间顶点遍历,k是中间顶点的下标 
	for (int k = 1; k <= G.vexnum; ++k) {
		//从i顶点出发
		for (int i = 1; i <= G.vexnum; ++i) {
			//到达j顶点
			for (int j = 1; j <= G.vexnum; ++j) {
				//如果从i顶点出发，经过k中间顶点，到达j顶点的距离小于从i顶点到j顶点
				if (G.matrix[i][j] > G.matrix[i][k] + G.matrix[k][j]) {
					G.matrix[i][j] = G.matrix[i][k] + G.matrix[k][j]; //更新距离
					G.p[i][j] = G.vertex[k]; //更新前驱
				}

			}
		}
	}
	for (int i = 1; i <= G.vexnum; ++i) {
		for (int j = 1; j <= G.vexnum; ++j) {
			printf("%d ",G.matrix[i][j]);
		}
		printf("\n");
	}
}
int main() {
	Graph G;
	CreateG(G);
	Floyd(G);
	return 0;
}
