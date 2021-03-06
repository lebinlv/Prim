/*****************************************
求最小生成树的Prim算法
程序中使用邻接矩阵法创建图
********************************************/

#include "stdafx.h"
#include <stdlib.h>

#define MAXSIZE 20		//图的最大顶点数
#define MAXCOST	233		//图中边的权值最大值

typedef char verType;	//重命名节点类型，方便日后更改


//定义图的邻接矩阵法表示结构
typedef struct graphStruct
{
	verType ver[MAXSIZE];
	int side_weight[MAXSIZE][MAXSIZE];
}Graph;

//定义最小生成树的表示结构
typedef struct primGraph_Struct
{
	verType *ver_left;		//边左端点数组
	verType *ver_right;		//边右端点数组
	int *side_weight;		//边权值数组
}primGraph;


//图的邻接矩阵生成函数，返回图的顶点数
int graphCreat(Graph *pGraph)
{
	int vertex_sum = 0;
	verType temp_Input;

	printf("请输入图的顶点：");
	while ((temp_Input = getchar()) != '\n')
		pGraph->ver[vertex_sum++] = temp_Input;

	printf("\n请输入相应的邻接矩阵：\n");
	for (int i = 0; i < vertex_sum; i++)
		for (int j = 0; j < vertex_sum; j++)
			scanf("%d", &pGraph->side_weight[i][j]);

	return vertex_sum;
}


//使用prim算法求取最小生成树
//*pGraph为原图，*result为最小生成树图
void prim(Graph *pGraph, int vertex_sum, primGraph *result)
{
	int i, j, k;		//控制循环的辅助变量
	int min, min_id;

	//low_cost[i]表示以closest[i]为起点，i为终点的边的权值
	int *low_cost = (int*)malloc(vertex_sum * sizeof(int));
	int *closest = (int*)malloc(vertex_sum * sizeof(int));

	//数组visited用于判定是否已经访问过
	int *visited = (int*)malloc(vertex_sum * sizeof(int));

	//将三个数组初始化（从编号为0的顶点开始执行prim算法）
	for (i = 0; i < vertex_sum; i++)
	{
		if (pGraph->side_weight[0][i] == 0)
			low_cost[i] = MAXCOST + 1;		//为0表示无连接，故将其设置为一个最大数，方便下面比较
		else
			low_cost[i] = pGraph->side_weight[0][i];
		closest[i] = 0;		// 因为从编号为0的顶点开始执行prim算法，所以起点均为0
		visited[i] = 0;		// visited数组初始值均为0，表示均为访问过
	}

	visited[0] = 1;			//因为从编号为0的顶点开始执行prim算法，故将 visited[0] 标记为1，表示已经访问过

	//顶点数为 vertex_sum, 故最小生成树有 vertex_sum-1 条边，于是进行 vertex_sum-1 次循环
	for (i = 0; i < vertex_sum - 1; i++)
	{
		min = MAXCOST + 1;	//给min赋初值为一个最大数，方便比较以寻找权值最小值

		//寻找权值最小值
		for (k = 0; k < vertex_sum; k++)
			if (visited[k] == 0 && low_cost[k] != 0 && low_cost[k] < min)
			{
				min = low_cost[k];
				min_id = k;
			}

		//此时便可通过 min_id 确定这条权值最小边的左右端点，于是更改result
		result->ver_left[i] = pGraph->ver[closest[min_id]];
		result->ver_right[i] = pGraph->ver[min_id];
		result->side_weight[i] = min;

		//顶点min_id已经访问过，故将visited[min_id]标记为1
		visited[min_id] = 1;

		//由于顶点min_id的加入，需要更新low_cost和closest两个数组
		for (k = 0; k < vertex_sum; k++)
			if (visited[k] == 0 && pGraph->side_weight[min_id][k] != 0 && pGraph->side_weight[min_id][k] < low_cost[k])
			{
				low_cost[k] = pGraph->side_weight[min_id][k];
				closest[k] = min_id;
			}
	}
}

//打印最小生成树
void print_primGraph(primGraph *p_primGraph, int vertex_sum)
{
	for (int i = 0; i < vertex_sum - 1; i++)
		printf("\n路径：%c <--> %c;  权值： %d", p_primGraph->ver_left[i], p_primGraph->ver_right[i], p_primGraph->side_weight[i]);
}

int main()
{
	Graph g;
	int vertex_sum = graphCreat(&g);

	//建立并初始化g_prim用于保存最小生成树
	primGraph g_prim;
	g_prim.ver_left = (char*)malloc(vertex_sum * sizeof(char));
	g_prim.ver_right = (char*)malloc(vertex_sum * sizeof(char));
	g_prim.side_weight = (int*)malloc((vertex_sum - 1) * sizeof(int));
	
	//求取最小生成树
	prim(&g, vertex_sum, &g_prim);
	//打印最小生成树
	print_primGraph(&g_prim, vertex_sum);

	printf("\n\n\n");
	system("pause");
    return 0;
}

