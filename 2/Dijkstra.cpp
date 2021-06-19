#include <stdio.h>
#include <stdlib.h>
#define NUM 20 //最大容量 
#define VertexType char
#define INF 65535
typedef struct Graph {
	VertexType vertex[NUM]; //存放顶点的数组
	int matrix[NUM][NUM] = {}; //邻接矩阵
	int vexnum,arcnum; //vernum为顶点个数，arcnum为边数
} Graph;
typedef struct VisitedVertex {
	//记录各个顶点是否访问过，1表示访问过，0未访问
	int already_arr[NUM] = {};
	//每个下标对应的值为前一个顶点下标
	int p[NUM];
	//出发顶点到其他所有顶点的距离
	int dis[NUM] = { };
	//更新出发顶点到index顶点的距离
	void updateDis(int index,int len) {
		dis[index] = len;
	}
	//更新pre这个顶点的前驱为index顶点
	void updatePre(int pre, int index) {
		p[pre] = index;
	}
	//返回出发顶点到index顶点的距离
	int getDis(int index) {
		return dis[index];
	}
}VisitedVertex;
//初始化连通图 
void CreateG(Graph &G,VisitedVertex &vx) {
	VertexType v1, v2;
	int m;
	//输入顶点数vexnum，边数arcnum
	scanf("%d %d", &G.vexnum, &G.arcnum);
	getchar();
	for (int i = 1; i <= G.vexnum; ++i) {
		scanf("%c",&G.vertex[i]);
		getchar();
	}
	for (int i = 1; i <= G.arcnum; i++) {
		for (int j = 1; j <= G.arcnum; j++) {
			G.matrix[i][j] = INF;
		}
	}
	//输入从v1顶点到v2顶点的距离
	for (int i = 1; i <= G.arcnum; ++i) {
		scanf("%c %c %d", &v1, &v2,&m);
		getchar();
		G.matrix[(int)v1-96][(int)v2-96] = m;
	}
	for (int i = 1; i<= G.arcnum; i++) {
		vx.dis[i] = INF;
	}
}
//flod算法
void dsj(Graph &G, VisitedVertex &vx) {
	int len = 0;
	VertexType start,end;
	scanf("%c %c", &start,&end);
	int index = start - 96;
	vx.already_arr[index]=1;
	vx.dis[index] = 0;
	//更新出发顶点到其余顶点的距离
	for (int j = 1; j <= G.vexnum; j++) {
		len = vx.getDis(index)+G.matrix[index][j];
		if (vx.already_arr[j] == 0 && len < vx.getDis(j)) {
			vx.updatePre(j, index); //更新前驱为index 
			vx.updateDis(j, len);	//更新出发顶点到j的距离 
		}
	}	
	
	for (int i = 1; i < G.vexnum; i++) {
		int min = INF; 
		for (int i = 1; i <= G.vexnum; i++) {
			if (vx.already_arr[i] == 0 && vx.dis[i] < min) {
				min = vx.dis[i];
				index = i;
			}
		}
		vx.already_arr[index] = 1;
		//更新index下标顶点到周围顶点的距离和周围顶点的前驱顶点 
		for (int j = 1; j <= G.vexnum; j++) {
			//出发顶点到index的距离+从index到j的距离 
			len = vx.getDis(index) + G.matrix[index][j];
			//如果j顶点没有被访问，并且len小于出发顶点到j的距离，就更新 
			if (vx.already_arr[j] == 0 && len < vx.getDis(j)) {
				vx.updatePre(j, index);
				vx.updateDis(j, len);
			}
		}
	}
	printf("%d\n", vx.dis[(int)end-96]);
}
/*输入示例
8 11
a
b
c
d
e
f
g
h
a b 1
b d 2
c a 2
d c 1
d f 8
e d 2
e g 2
f e 2
g f 3
g h 3
h f 2
a h
*/
int main() {
	Graph G;
	VisitedVertex vx;
	CreateG(G,vx);
	dsj(G, vx);
	return 0;
}
