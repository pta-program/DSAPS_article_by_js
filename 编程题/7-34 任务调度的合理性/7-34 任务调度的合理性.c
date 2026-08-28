/*
 * 实现原理：
 * 1. 问题本质：判断有向图中是否存在环。任务依赖关系构成有向图，若存在环则任务调度不可行
 * 2. 算法选择：采用拓扑排序(Kahn算法)判断有向图是否存在环
 * 3. Kahn算法步骤：
 *    a. 计算每个节点的入度
 *    b. 将入度为0的节点加入队列
 *    c. 从队列取出节点，将其邻接节点的入度减1，若入度变为0则加入队列
 *    d. 重复直到队列为空
 *    e. 若处理的节点数等于总节点数，则无环(可行)；否则有环(不可行)
 * 4. 输入处理：第i行表示任务i的依赖集合，即存在从依赖任务指向任务i的边
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 101  // 子任务数最多100，编号从1到100

// 邻接表节点结构体
typedef struct AdjNode {
    int vertex;           // 邻接节点编号
    struct AdjNode *next; // 下一个邻接节点
} AdjNode;

// 邻接表头结构体
typedef struct AdjList {
    AdjNode *head;        // 链表头指针
} AdjList;

// 队列结构体（用于Kahn算法）
typedef struct Queue {
    int data[MAX_NODES];  // 队列数据
    int front;            // 队头指针
    int rear;             // 队尾指针
} Queue;

// 初始化队列
void init_queue(Queue *q) {
    q->front = 0;
    q->rear = 0;
}

// 判断队列是否为空
int is_empty(Queue *q) {
    return q->front == q->rear;
}

// 入队
void enqueue(Queue *q, int val) {
    q->data[q->rear++] = val;
}

// 出队
int dequeue(Queue *q) {
    return q->data[q->front++];
}

// 添加边到邻接表（u -> v，表示任务v依赖任务u）
void add_edge(AdjList *graph, int u, int v) {
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

void free_graph(AdjList *graph, int n) {
    for (int i = 1; i <= n; i++) {
        AdjNode *p = graph[i].head;
        while (p != NULL) {
            AdjNode *next = p->next;
            free(p);
            p = next;
        }
    }
}

int main() {
    int n;  // 子任务数
    scanf("%d", &n);
    
    AdjList graph[MAX_NODES];  // 邻接表存储图
    int in_degree[MAX_NODES] = {0};  // 入度数组
    Queue q;  // 队列
    
    // 初始化邻接表
    for (int i = 1; i <= n; i++) {
        graph[i].head = NULL;
    }
    
    // 读取每个任务的依赖关系
    for (int i = 1; i <= n; i++) {
        int k;  // 依赖的任务数
        scanf("%d", &k);
        
        for (int j = 0; j < k; j++) {
            int dep;  // 依赖的任务编号
            scanf("%d", &dep);
            // 添加边 dep -> i（任务i依赖任务dep）
            add_edge(graph, dep, i);
            in_degree[i]++;  // 任务i的入度加1
        }
    }
    
    // 初始化队列
    init_queue(&q);
    
    // 将所有入度为0的节点加入队列
    for (int i = 1; i <= n; i++) {
        if (in_degree[i] == 0) {
            enqueue(&q, i);
        }
    }
    
    int count = 0;  // 记录处理的节点数
    
    // Kahn算法主循环
    while (!is_empty(&q)) {
        int u = dequeue(&q);  // 取出队头节点
        count++;  // 处理节点数加1
        
        // 遍历u的所有邻接节点
        AdjNode *p = graph[u].head;
        while (p != NULL) {
            int v = p->vertex;
            in_degree[v]--;  // 邻接节点v的入度减1
            
            if (in_degree[v] == 0) {  // 如果v的入度变为0
                enqueue(&q, v);  // 将v加入队列
            }
            p = p->next;
        }
    }
    
    // 如果处理的节点数等于总节点数，说明无环，任务调度可行
    if (count == n) {
        printf("1\n");
    } else {  // 否则存在环，任务调度不可行
        printf("0\n");
    }

    free_graph(graph, n);
    return 0;
}
