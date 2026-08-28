/*
 * 实现原理：
 * 使用并查集（Union-Find / DSU）数据结构维护朋友圈的连通关系。
 * 1. 初始化 N 个学生，每个学生独立为一个朋友圈（自己为根，大小为 1）。
 * 2. 对每个俱乐部，将该俱乐部的第一个学生与其他所有学生依次进行 union 操作，
 *    使得整个俱乐部的学生归入同一朋友圈。
 * 3. path compression（路径压缩）在 find 时将节点直接挂到根节点，
 *    union by size（按大小合并）将较小集合挂到较大集合的根上，
 *    两者结合使并查集接近 O(1) 的操作复杂度。
 * 4. 最后遍历 size 数组，找出最大值即为最大朋友圈的人数。
 */

#include <stdio.h>   // 标准输入输出
#include <stdlib.h>  // malloc/free

#define MAX_N 30005  // 学生总数上限（N ≤ 30000）

int parent[MAX_N];   // parent[i] 表示第 i 个学生的父节点
int sz[MAX_N];       // sz[i] 表示以 i 为根的集合的大小（仅根节点有效）

// 查找 x 所在集合的根，并进行路径压缩
int find(int x) {
    if (parent[x] != x)           // 如果 x 不是根节点
        parent[x] = find(parent[x]); // 递归查找根，并将 x 直接挂到根下
    return parent[x];              // 返回根节点
}

// 合并 a 和 b 所在的集合（按大小合并，小树挂到大树上）
void unite(int a, int b) {
    int ra = find(a);              // 找 a 的根
    int rb = find(b);              // 找 b 的根
    if (ra == rb) return;          // 已在同一集合，无需合并
    if (sz[ra] < sz[rb]) {         // 保证 ra 所在的树更大
        int t = ra; ra = rb; rb = t; // 交换 ra 和 rb
    }
    parent[rb] = ra;               // 将小树 rb 挂到大树 ra 下
    sz[ra] += sz[rb];              // 更新 ra 集合的大小
}

int main() {
    int N, M;                      // N：学生总数，M：俱乐部个数
    scanf("%d %d", &N, &M);        // 读入 N 和 M

    // 并查集初始化：每个学生自己为一个集合
    for (int i = 1; i <= N; i++) {
        parent[i] = i;             // 父节点是自己
        sz[i] = 1;                 // 集合大小为 1
    }

    // 处理 M 个俱乐部
    for (int i = 0; i < M; i++) {
        int Mi;                    // 第 i 个俱乐部的人数
        scanf("%d", &Mi);          // 读入俱乐部人数
        int first;                 // 俱乐部第一个学生编号（作为合并基准）
        scanf("%d", &first);       // 读入第一个学生
        // 将其余 Mi-1 个学生依次与第一个学生合并
        for (int j = 1; j < Mi; j++) {
            int x;                 // 俱乐部中其他学生的编号
            scanf("%d", &x);       // 读入该学生
            unite(first, x);       // 将其与第一个学生合并
        }
    }

    // 遍历所有学生的根集合大小，找出最大值
    int ans = 0;                   // 最大朋友圈人数
    for (int i = 1; i <= N; i++) {
        if (parent[i] == i) {      // 仅检查根节点（集合代表）
            if (sz[i] > ans)       // 如果该集合更大
                ans = sz[i];       // 更新答案
        }
    }

    printf("%d\n", ans);           // 输出最大朋友圈人数
    return 0;                      // 程序正常结束
}
