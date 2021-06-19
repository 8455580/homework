#include <stdio.h>
#include <stdlib.h>
#define NUM 20  //数组容量
#define INFINITY 65535  //象征无穷大
#define VRType int      //权值类型
#define VertexType int  //顶点类型

typedef struct {
    VRType arcs[NUM][NUM];                  //邻接矩阵map存储连通图,map[u][v]表示顶点u到v的权值
    int vexnum,arcnum;                      //记录图的顶点数和边数
}MGraph;

//构造无向网
void CreateUDN(MGraph* G){
    scanf("%d,%d",&(G->vexnum),&(G->arcnum));
	int i,j;
    for(i=0; i<G->vexnum; i++) {
        for (j=0; j<G->vexnum; j++) {
            G->arcs[i][j]=INFINITY;
        }
    }
    for(i=0; i<G->arcnum; i++) {
        int v1,v2,w;
        scanf("%d,%d,%d",&v1,&v2,&w);
        G->arcs[v1][v2]=w;
        G->arcs[v2][v1]=w;
    }
}

//辅助数组，用于每次筛选出权值最小的边的邻接点
typedef struct {
    VertexType adjvex;//记录权值最小的边的起始点
    VRType lowcost;//记录该边的权值
}closedge[NUM];
closedge dist;//创建一个全局数组，因为每个函数中都会使用到
//在dist数组中找出权值最小的边的数组下标，就可以间接找到此边的终点顶点。
int mindist(MGraph G,closedge dist){
    int min=INFINITY;
    int min_index=-1;
	int i;
    for(i=1; i<=G.vexnum; i++) {
        //权值为0，说明顶点已经归入最小生成树中；然后每次和min变量进行比较，最后找出最小的。
        if (dist[i].lowcost>0 && dist[i].lowcost < min) {
            min=dist[i].lowcost;
            min_index=i;
        }
    }
    return min_index;
}
//普里姆算法函数，G为无向网，u为在网中选择的任意顶点作为起始点
void Prim(MGraph G,VertexType start){
	int i,j,k;
    //首先将与该起始点相关的所有边的信息：边的起始点和权值，存入辅助数组中相应的位置，例如（1，2）边，adjvex为1，lowcost为6，存入dist[2]中，辅助数组的下标表示该边的顶点2
	for(i=1; i<=G.vexnum; i++) {
        if (i !=k) {
            dist[i].adjvex=start;
            dist[i].lowcost=G.arcs[start][i];
        }
    }
    //由于起始点已经归为最小生成树，所以辅助数组对应位置的权值为0，这样，遍历时就不会被选中
    dist[start].lowcost=0;
    //选择下一个点，并更新辅助数组中的信息
    for(i=1; i<G.vexnum; i++) {
        //找出权值最小的边所在数组下标
        k=mindist(G, dist);
        //输出选择的路径
        printf("v%d v%d\n",dist[k].adjvex,k);
        //归入最小生成树的顶点的辅助数组中的权值设为0
        dist[k].lowcost=0;
        //信息辅助数组中存储的信息，由于此时树中新加入了一个顶点，需要判断，由此顶点出发，到达其它各顶点的权值是否比之前记录的权值还要小，如果还小，则更新
        for( j=1; j<=G.vexnum; j++) {
            if (G.arcs[k][j]<dist[j].lowcost) {
                dist[j].adjvex=k;
                dist[j].lowcost=G.arcs[k][j];
            }
        }
    }
    printf("\n");
}
/*输入示例
4,5  //4个顶点，5条边 
1,2,3 //顶点1、2，之间的权值为3 
1,3,1
1,4,2
2,4,3
3,4,2
*/ 
int main(){
    MGraph G;
    CreateUDN(&G);
    Prim(G, 1);
}
