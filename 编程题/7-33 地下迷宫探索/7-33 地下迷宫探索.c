/*
 * 实现原理：
 * 1. 使用邻接表存储图结构，每个节点维护一个邻接节点列表
 * 2. 对每个节点的邻接列表按编号从小到大排序，确保小编号优先访问
 * 3. 使用深度优先搜索(DFS)遍历图，访问节点时将其加入路径
 * 4. DFS回溯时也将节点加入路径，实现"原路返回"的效果
 * 5. 使用visited数组记录已访问的节点，统计访问数量判断是否连通
 * 6. 若访问数量等于总节点数，输出路径；否则路径末尾输出0表示非连通图
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 1001  // 节点最大数量，节点编号从1到N

// 邻接表节点结构体
typedef struct AdjNode {
    int vertex;           // 邻接节点编号
    struct AdjNode *next; // 下一个邻接节点
} AdjNode;

// 邻接表头结构体
typedef struct AdjList {
    AdjNode *head;        // 链表头指针
} AdjList;

// 全局变量
AdjList graph[MAX_NODES]; // 图的邻接表
int visited[MAX_NODES];   // 访问标记数组
int path[MAX_NODES * 2];  // 存储路径，最多2*N个节点（去程+回程）
int path_len;             // 当前路径长度
int visit_count;          // 已访问节点数

// 比较函数，用于qsort排序
int cmp(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}

// 添加边到邻接表
void add_edge(int u, int v) {
    // 创建v节点
    AdjNode *new_node = (AdjNode *)malloc(sizeof(AdjNode));
    new_node->vertex = v;
    new_node->next = NULL;
    
    // 将v插入到u的邻接表头部
    if (graph[u].head == NULL) {
        graph[u].head = new_node;
    } else {
        new_node->next = graph[u].head;
        graph[u].head = new_node;
    }
}

// DFS遍历函数
void dfs(int start) {
    visited[start] = 1;          // 标记为已访问
    visit_count++;               // 访问计数加1
    path[path_len++] = start;    // 将当前节点加入路径
    
    // 收集当前节点的所有邻接节点
    int neighbors[MAX_NODES];
    int neighbor_count = 0;
    AdjNode *p = graph[start].head;
    while (p != NULL) {
        neighbors[neighbor_count++] = p->vertex;
        p = p->next;
    }
    
    // 对邻接节点按编号从小到大排序
    qsort(neighbors, neighbor_count, sizeof(int), cmp);
    
    // 遍历所有邻接节点
    for (int i = 0; i < neighbor_count; i++) {
        int v = neighbors[i];
        if (!visited[v]) {       // 如果邻接节点未被访问
            dfs(v);              // 递归访问
            path[path_len++] = start;  // 回溯时将当前节点加入路径
        }
    }
}

int main() {
    int N, M, S;
    // 读取节点数N、边数M、起始节点S
    scanf("%d %d %d", &N, &M, &S);
    
    // 初始化邻接表
    for (int i = 1; i <= N; i++) {
        graph[i].head = NULL;
        visited[i] = 0;
    }
    
    // 读取M条边并构建邻接表
    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        add_edge(u, v);  // 添加u->v的边
        add_edge(v, u);  // 添加v->u的边（无向图）
    }
    
    // 初始化路径长度和访问计数
    path_len = 0;
    visit_count = 0;
    
    // 从起始节点S开始DFS遍历
    dfs(S);
    
    // 输出路径中的所有节点
    for (int i = 0; i < path_len; i++) {
        if (i > 0) {
            printf(" ");  // 节点之间用空格分隔
        }
        printf("%d", path[i]);
    }
    
    // 如果未访问所有节点，输出0表示非连通图
    if (visit_count != N) {
        printf(" 0");
    }
    printf("\n");
    
    return 0;
}