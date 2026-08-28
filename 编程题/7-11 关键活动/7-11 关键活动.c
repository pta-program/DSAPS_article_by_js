/*
 * 实现过程：
 * 本题要求在AOE网中求关键活动，即整个工程的最短工期及所有不可延误的活动。
 *
 * 算法：拓扑排序 + 最早/最晚开始时间（AOE网关键路径）。
 *
 * 数据结构：
 * - graph[N][N]：邻接矩阵，存储任务依赖关系和耗时。
 * - u_arr/v_arr/w_arr[]：按输入顺序保存所有边，用于最终按规则输出关键活动。
 * - ve[i]：事件（节点）i的最早发生时间。
 * - vl[i]：事件（节点）i的最晚发生时间。
 * - indegree[i]：节点i的入度，用于拓扑排序。
 * - topo_order[]：拓扑排序结果，用于逆序计算vl。
 *
 * 步骤：
 * 1. 读入节点数N、边数M，构建邻接矩阵，记录入度，保存边信息。
 * 2. 正向拓扑排序（BFS），计算ve[]：
 *    a. 入度为0的节点入队。
 *    b. 出队节点u，遍历其后继v，更新ve[v] = max(ve[v], ve[u] + graph[u][v])。
 *    c. v的入度减1，若为0则入队。
 *    d. 若拓扑排序访问节点数 < N，说明有环，输出0并结束。
 * 3. 反向计算vl[]：
 *    a. 总工期 = max(ve[])，所有vl初始化为总工期。
 *    b. 逆拓扑序遍历节点u，对每条边u->v，更新vl[u] = min(vl[u], vl[v] - graph[u][v])。
 * 4. 输出关键活动：
 *    a. 第一行输出总工期。
 *    b. 对每条边u->v权重w，若ve[u] + w == vl[v]则为关键活动。
 *    c. 输出顺序：起点编号小优先，起点相同时与输入顺序相反。
 *
 * 时间复杂度：O(N^2 + M)，空间复杂度：O(N^2 + M)。
 */

#include <stdio.h>   // 标准输入输出（scanf, printf）
#include <stdlib.h>  // 标准库
#include <string.h>  // 字符串和内存操作（memset）

#define MAXN 105        // 最大节点数（N ≤ 100，多留余量）
#define INF 0x3f3f3f3f  // 无穷大常量（约1e9，安全不溢出）

int main() {
    int N, M;                                // N: 交接点数量, M: 子任务数量
    scanf("%d %d", &N, &M);                  // 读入N和M

    int u_arr[M], v_arr[M], w_arr[M];        // 保存所有边的起点、终点、权重（按输入顺序）
    int graph[MAXN][MAXN];                   // 邻接矩阵，graph[u][v] = 从u到v的任务耗时
    memset(graph, 0, sizeof(graph));         // 初始化邻接矩阵为0（0表示无边）

    int indegree[MAXN] = {0};                // 各节点的入度（有多少条边指向该节点）
    int outdegree[MAXN] = {0};               // 各节点的出度（有多少条边从该节点出发）

    for (int i = 0; i < M; i++) {            // 读入M条边
        int u, v, w;                         // 起点u, 终点v, 耗时w
        scanf("%d %d %d", &u, &v, &w);       // 读入一条边的信息
        u_arr[i] = u;                        // 保存起点（用于后续按输入顺序输出）
        v_arr[i] = v;                        // 保存终点
        w_arr[i] = w;                        // 保存权重/耗时
        graph[u][v] = w;                     // 填充邻接矩阵
        indegree[v]++;                       // 终点v的入度+1
        outdegree[u]++;                      // 起点u的出度+1
    }

    // ===== 正向拓扑排序，计算 ve[]（最早开始时间）=====
    int ve[MAXN] = {0};                      // ve[i]: 节点i的最早开始时间，初始为0
    int queue[MAXN];                         // 用数组模拟队列（BFS拓扑排序用）
    int front = 0, rear = 0;                 // 队列的头尾指针
    int topo_order[MAXN];                    // 保存拓扑排序的结果顺序
    int topo_cnt = 0;                        // 拓扑排序已输出的节点数量

    for (int i = 1; i <= N; i++) {           // 遍历所有节点（编号1~N）
        if (indegree[i] == 0) {              // 入度为0的节点可作为起点
            queue[rear++] = i;               // 入队
        }
    }

    while (front < rear) {                   // 队列非空时继续
        int u = queue[front++];              // 出队一个节点u
        topo_order[topo_cnt++] = u;          // 记录拓扑序
        for (int v = 1; v <= N; v++) {       // 遍历u的所有邻接节点v
            if (graph[u][v] > 0) {           // 存在边 u->v
                indegree[v]--;               // v的入度-1（移除边u->v）
                if (ve[u] + graph[u][v] > ve[v]) { // 若通过u到达v的时间更晚
                    ve[v] = ve[u] + graph[u][v];   // 更新v的最早开始时间
                }
                if (indegree[v] == 0) {      // v的入度变为0
                    queue[rear++] = v;       // v入队等待处理
                }
            }
        }
    }

    // 有环，调度不可行：拓扑排序未能处理全部N个节点
    if (topo_cnt < N) {
        printf("0\n");                       // 输出0表示方案不可行
        return 0;
    }

    // ===== 反向计算 vl[]（最晚开始时间）=====
    int vl[MAXN];                            // vl[i]: 节点i的最晚开始时间
    int max_ve = 0;                          // 整个工程的最早完成时间（ve数组最大值）
    for (int i = 1; i <= N; i++) {           // 遍历所有节点
        if (ve[i] > max_ve) max_ve = ve[i];  // 找ve[]的最大值作为工期
    }
    for (int i = 1; i <= N; i++) {           // 初始化所有节点的vl为总工期
        vl[i] = max_ve;                      // 最晚开始时间初始化为总工期
    }

    for (int i = topo_cnt - 1; i >= 0; i--) { // 逆拓扑序处理（从汇点回推到源点）
        int u = topo_order[i];               // 当前处理的节点u
        for (int v = 1; v <= N; v++) {       // 遍历u的所有后继节点v
            if (graph[u][v] > 0) {           // 存在边 u->v
                if (vl[v] - graph[u][v] < vl[u]) { // 若v的最晚时间-边权比当前u更早
                    vl[u] = vl[v] - graph[u][v];   // 更新u的最晚开始时间
                }
            }
        }
    }

    // ===== 输出结果 =====
    printf("%d\n", max_ve);                  // 第一行输出整个工程的最短工期

    // 关键活动判定条件：ve[u] + w == vl[v]（最早=最晚，无时间余量）
    // 输出顺序规则：
    //   1. 起点编号小者优先
    //   2. 起点编号相同时，与输入顺序相反（后输入的边先输出）
    for (int start = 1; start <= N; start++) {        // 按起点编号从小到大遍历
        for (int i = M - 1; i >= 0; i--) {            // 从后往前遍历输入边（实现"相反顺序"）
            int u = u_arr[i], v = v_arr[i], w = w_arr[i]; // 取出边u->v权重w
            if (u == start && ve[u] + w == vl[v]) {   // 起点匹配且满足关键活动条件
                printf("%d->%d\n", u, v);              // 输出关键活动
            }
        }
    }

    return 0;
}
