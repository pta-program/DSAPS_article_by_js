/*
 * 实现原理：
 * 给定二叉树的前序遍历和中序遍历序列，求二叉树的高度。
 * 核心思路：前序遍历的第一个元素即为根节点，在中序遍历中找到该根节点的位置 k，
 * 则中序遍历中 k 左侧为左子树（k 个节点），右侧为右子树（n-1-k 个节点）。
 * 前序遍历中，根节点之后的前 k 个为左子树的前序，再之后为右子树的前序。
 * 递归计算左右子树的高度，取较大值加 1 即为当前树的高度。
 * 递归终止条件：节点数为 0 时高度为 0。
 */

#include <stdio.h>   // 标准输入输出
#include <string.h>  // 字符串操作

// 在字符串 s 的前 len 个字符中查找字符 c 的位置
int find(char *s, char c, int len) {
    for (int i = 0; i < len; i++)  // 遍历前 len 个字符
        if (s[i] == c) return i;   // 找到则返回下标
    return -1;                     // 未找到返回 -1
}

// 递归计算二叉树高度：pre 为前序序列，in 为中序序列，n 为节点数
int height(char *pre, char *in, int n) {
    if (n == 0) return 0;                          // 空树高度为 0
    int k = find(in, pre[0], n);                   // 在中序中找到根节点位置，划分左右子树
    int left = height(pre + 1, in, k);             // 递归计算左子树高度（前序跳过根，中序取前 k 个）
    int right = height(pre + 1 + k, in + 1 + k, n - 1 - k); // 递归计算右子树高度（前序和中序都跳过根和左子树部分）
    return 1 + (left > right ? left : right);      // 当前树高度 = 1 + max(左子树高度, 右子树高度)
}

int main() {
    int n;                       // 节点总数
    char pre[55], in[55];        // 前序和中序遍历序列
    scanf("%d", &n);             // 读入节点数
    scanf("%s %s", pre, in);     // 读入前序和中序序列
    printf("%d\n", height(pre, in, n)); // 输出二叉树高度
    return 0;                    // 程序正常结束
}
