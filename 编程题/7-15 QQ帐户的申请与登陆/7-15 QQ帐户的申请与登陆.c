/*
 * 实现过程：
 * 本题要求实现QQ帐户的申请（N）与登陆（L）功能，根据不同情况输出对应提示。
 *
 * 算法：哈希表（拉链法）模拟帐户管理。
 *
 * 数据结构：
 * - table[MOD]：哈希表桶数组，MOD取大于N的质数。
 * - Node链表：每个节点存储QQ号码、密码、next指针，拉链法解决冲突。
 *
 * 步骤：
 * 1. 读入指令条数n。
 * 2. 对每条指令（命令符cmd、号码qq、密码pw）：
 *    a. 若cmd=='N'（新申请）：
 *       - 在哈希表中查找qq，若已存在输出"ERROR: Exist"。
 *       - 若不存在则插入(qq, pw)，输出"New: OK"。
 *    b. 若cmd=='L'（登陆）：
 *       - 在哈希表中查找qq，若不存在输出"ERROR: Not Exist"。
 *       - 若存在但密码不匹配输出"ERROR: Wrong PW"。
 *       - 若存在且密码匹配输出"Login: OK"。
 * 3. 哈希函数采用BKDR字符串哈希（基数131）。
 *
 * 时间复杂度：O(N)（平均），空间复杂度：O(N)。
 */

#include <stdio.h>    // 引入标准输入输出库，用于 scanf、printf
#include <stdlib.h>   // 引入标准库，用于 malloc、free
#include <string.h>   // 引入字符串库，用于 strcpy、strcmp

#define MOD 199999    // 哈希表桶数，选用大于 10^5 的质数

// 哈希表链表节点：存储 QQ号码 和 密码
typedef struct Node {
    char qq[12];       // QQ号码字符串（最多 10 位 + '\0'）
    char pw[20];       // 密码字符串（最多 16 位 + '\0'）
    struct Node *next; // 链表指针，拉链法解决哈希冲突
} Node;

Node *table[MOD];     // 哈希表数组，每个元素是对应桶的链表头

// BKDR 字符串哈希函数
unsigned long long hash_func(const char *s) {
    unsigned long long h = 0;           // 初始化哈希值
    for (int i = 0; s[i]; i++) {        // 遍历字符串每个字符
        h = h * 131 + s[i];             // 经典 BKDR 哈希算法
    }
    return h % MOD;                      // 对表长取模得到桶索引
}

// 在哈希表中查找 QQ号码，返回节点指针；不存在返回 NULL
Node *find(const char *qq) {
    unsigned long long idx = hash_func(qq);  // 计算哈希索引
    Node *p = table[idx];                     // 取该桶的链表头
    while (p) {                               // 遍历链表查找
        if (strcmp(p->qq, qq) == 0) {         // 找到相同号码
            return p;                         // 返回节点指针
        }
        p = p->next;                          // 继续下一个节点
    }
    return NULL;                              // 未找到，返回 NULL
}

// 向哈希表中插入新的（QQ号码, 密码）对
void insert(const char *qq, const char *pw) {
    unsigned long long idx = hash_func(qq);  // 计算哈希索引
    Node *node = (Node *)malloc(sizeof(Node));  // 分配新节点内存
    strcpy(node->qq, qq);                      // 复制 QQ号码
    strcpy(node->pw, pw);                      // 复制密码
    node->next = table[idx];                   // 新节点 next 指向原链表头
    table[idx] = node;                         // 将新节点设为链表头
}

int main() {
    int n;                     // 指令条数
    scanf("%d", &n);           // 读取 n

    char cmd[2];               // 命令符（N 或 L）
    char qq[12];               // QQ号码
    char pw[20];               // 密码

    // 处理每条指令
    for (int i = 0; i < n; i++) {
        scanf("%s %s %s", cmd, qq, pw);  // 读取命令符、号码、密码

        if (cmd[0] == 'N') {            // 新申请帐户指令
            Node *p = find(qq);          // 在哈希表中查找该号码
            if (p != NULL) {             // 号码已存在
                printf("ERROR: Exist\n");
            } else {                     // 号码不存在，创建新帐户
                insert(qq, pw);          // 插入哈希表
                printf("New: OK\n");
            }
        } else if (cmd[0] == 'L') {     // 登陆指令
            Node *p = find(qq);          // 在哈希表中查找该号码
            if (p == NULL) {             // 号码不存在
                printf("ERROR: Not Exist\n");
            } else if (strcmp(p->pw, pw) == 0) {  // 号码存在且密码正确
                printf("Login: OK\n");
            } else {                     // 号码存在但密码错误
                printf("ERROR: Wrong PW\n");
            }
        }
    }

    // 释放哈希表内存（OJ 上可省略，良好编程习惯）
    for (int i = 0; i < MOD; i++) {
        Node *p = table[i];
        while (p) {
            Node *next = p->next;
            free(p);
            p = next;
        }
    }

    return 0;   // 程序正常结束
}
