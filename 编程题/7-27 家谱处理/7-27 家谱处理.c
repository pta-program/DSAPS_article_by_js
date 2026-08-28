/*
 * 7-27 家谱处理 - C语言实现
 *
 * 实现方式：
 * 1. 数据结构：
 *    - names[]: 存储所有名字（字符串数组）
 *    - depth[]: 存储每个名字的层级深度（缩进空格数/2）
 *    - parent[]: 存储每个名字的父节点索引（-1表示无父节点）
 *
 * 2. 构建家谱：
 *    - 逐行读取名字，计算缩进空格数sp，深度d = sp/2
 *    - 向前回溯找到第一个深度为d-1的节点作为父节点
 *
 * 3. 关系判断：
 *    - child: parent[X] == Y
 *    - parent: parent[Y] == X
 *    - sibling: parent[X] == parent[Y] 且 X != Y
 *    - descendant: 从X向上追溯能找到Y
 *    - ancestor: 从Y向上追溯能找到X
 */

#include <stdio.h>      // 标准输入输出库
#include <string.h>     // 字符串处理库
#include <stdlib.h>     // 标准库

#define MAX_N 105       // 最大名字数量
#define NAME_LEN 15     // 最大名字长度

char names[MAX_N][NAME_LEN];    // 存储所有名字
int depth[MAX_N];               // 存储每个名字的层级深度
int parent[MAX_N];              // 存储每个名字的父节点索引
int n, m;                       // n为名字数量，m为陈述语句数量
int cnt;                        // 当前已处理的名字数量

// 根据名字查找其在names数组中的索引
int findName(const char *name) {
    for (int i = 0; i < cnt; i++) {         // 遍历所有已存储的名字
        if (strcmp(names[i], name) == 0)    // 如果找到匹配的名字
            return i;                       // 返回其索引
    }
    return -1;                              // 未找到返回-1
}

// 判断a是否是b的祖先（从b向上追溯能否找到a）
int isAncestor(int a, int b) {
    int cur = b;                            // 从b开始向上追溯
    while (cur != -1) {                     // 当cur有父节点时继续
        if (cur == a)                       // 如果追溯到a
            return 1;                       // 返回1（是祖先）
        cur = parent[cur];                  // 向上移动到父节点
    }
    return 0;                               // 未追溯到a，返回0
}

int main() {
    char line[100];                         // 存储每行输入
    char buf[100];                          // 存储陈述语句
    int i;                                  // 循环变量

    scanf("%d %d", &n, &m);                 // 读入n和m
    getchar();                              // 吸收换行符

    cnt = 0;                                // 初始化计数器为0
    memset(parent, -1, sizeof(parent));     // 将所有父节点初始化为-1

    // 构建家谱：读取n个名字
    for (i = 0; i < n; i++) {
        fgets(line, sizeof(line), stdin);   // 读取一行
        line[strcspn(line, "\r\n")] = 0;    // 去除换行符
        int sp = 0;                         // 计算缩进空格数
        while (line[sp] == ' ')             // 统计前导空格
            sp++;
        char *nm = line + sp;               // 获取名字（跳过空格）
        strcpy(names[cnt], nm);             // 存储名字
        depth[cnt] = sp / 2;                // 计算层级深度（每2个空格为一层）

        // 如果深度大于0，需要找到父节点
        if (depth[cnt] > 0) {
            for (int j = cnt - 1; j >= 0; j--) {    // 向前回溯
                if (depth[j] == depth[cnt] - 1) {   // 找到深度为d-1的节点
                    parent[cnt] = j;                // 设置父节点索引
                    break;                          // 找到后退出循环
                }
            }
        }
        cnt++;                               // 名字计数增加
    }

    // 处理m个陈述语句
    for (i = 0; i < m; i++) {
        fgets(buf, sizeof(buf), stdin);      // 读取陈述语句
        buf[strcspn(buf, "\r\n")] = 0;       // 去除换行符
        char x[NAME_LEN], y[NAME_LEN], keyword[NAME_LEN];
        /* 关系句式为“X is a/the/an relation of Y”，目标姓名是第6个词。 */
        if (sscanf(buf, "%14s %*s %*s %14s %*s %14s", x, keyword, y) != 3)
            continue;

        int xi = findName(x);                // 查找x的索引
        int yi = findName(y);                // 查找y的索引
        int result = 0;                      // 存储判断结果

        // 根据关键词判断关系
        if (strcmp(keyword, "child") == 0) {
            result = (parent[xi] == yi);     // X是Y的孩子：parent[X]==Y
        } else if (strcmp(keyword, "parent") == 0) {
            result = (parent[yi] == xi);     // X是Y的父母：parent[Y]==X
        } else if (strcmp(keyword, "sibling") == 0) {
            result = (parent[xi] != -1 && parent[xi] == parent[yi]);   // X和Y是兄弟：有相同父节点
        } else if (strcmp(keyword, "descendant") == 0) {
            result = isAncestor(yi, xi) && xi != yi;   // X是Y的后代：Y是X的祖先
        } else if (strcmp(keyword, "ancestor") == 0) {
            result = isAncestor(xi, yi) && xi != yi;   // X是Y的祖先：X是Y的祖先
        }

        printf(result ? "True\n" : "False\n");   // 输出结果
    }
    return 0;                                // 程序结束
}
