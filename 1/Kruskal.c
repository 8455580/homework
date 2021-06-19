#include <stdio.h>
#include <stdlib.h>
#define NUM 20 //最大容量 
#define VertexType int
typedef struct edge{
    VertexType adjvex; //起始点 
    VertexType end;		//终点 
    VertexType arcs;  //权值 
} edge[NUM];
//定义辅助数组
typedef struct {
    VertexType value;//顶点数据
    int sign;//每个顶点所属的集合
}Dist[NUM];
Dist dist;
//qsort排序函数中使用，使edges结构体中的边按照权值大小升序排序
int cmp(const void *a,const void*b){
    return  ((struct edge*)a)->arcs-((struct edge*)b)->arcs;
}
//初始化连通图 
void CreateUDN(edge *edges,int *vexnum,int *arcnum){
    int i;
	scanf("%d,%d",&(*vexnum),&(*arcnum));
	for (i=1; i<(*vexnum); i++) {
        dist[i].sign=i;
    }
    for (i=1 ; i<=(*arcnum); i++) {
        scanf("%d,%d,%d",&(*edges)[i].adjvex,&(*edges)[i].end,&(*edges)[i].arcs);
    }
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
    int arcnum,vexnum,i,j;
    edge edges;
    CreateUDN(&edges,&vexnum,&arcnum);
    //对连通网中的所有边进行升序排序，结果仍保存在edges数组中
    qsort(edges+1, arcnum, sizeof(edges[0]), cmp);
    //创建一个空的结构体数组，用于存放最小生成树
    edge minTree;
    //设置一个用于记录最小生成树中边的数量的常量
    int num=1;
    //遍历所有的边
    for (i=1; i<=arcnum; i++) {
        //找到边的起始顶点和结束顶点在数组dist中的位置
        int initial= edges[i].adjvex;
        int end= edges[i].end;
        //如果顶点位置存在且顶点的标记不同，说明不在一个集合中，不会产生回路
        if (initial!=-1&& end!=-1&&dist[initial].sign!=dist[end].sign) {
            //记录该边，作为最小生成树的组成部分
            minTree[num]=edges[i];
            //计数+1
            num++;
            //将新加入生成树的顶点标记全部更改为一样的
            for (j=1; j<=vexnum; j++) {
                if (dist[j].sign==dist[end].sign) {
                    dist[j].sign=dist[initial].sign;
                }
            }
            //如果选择的边的数量和顶点数相差1，证明最小生成树已经形成，退出循环
            if (num==vexnum) {
                break;
            }
        }
    }
    //输出语句
    for (i=1; i<vexnum; i++) {
        printf("%d,%d\n",minTree[i].adjvex,minTree[i].end);
    }
    return 0;
}

