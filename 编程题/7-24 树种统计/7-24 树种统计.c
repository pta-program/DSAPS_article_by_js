/*
 * 实现原理：
 * 将 n 个树种名称存入数组，使用 qsort 按字典序排序，
 * 排序后相同树种连续相邻，只需一次扫描即可统计每种出现次数，
 * 然后按字典序输出树种名称及其百分比（次数 * 100.0 / n，保留 4 位小数）。
 * 时间复杂度 O(n log n)，空间复杂度 O(n)。
 */

#include <stdio.h>   // 标准输入输出
#include <stdlib.h>  // malloc/free/qsort
#include <string.h>  // 字符串操作

#define MAX_LEN 32   // 每个树种名称最大字符数

int main() {
    int n;                        // 树的总数
    scanf("%d", &n);              // 读入 n
    getchar();                    // 消耗 n 后面的换行符

    // 动态分配二维字符数组，存储所有树种名称
    char (*arr)[MAX_LEN] = malloc(sizeof(char) * MAX_LEN * n);

    // 逐行读入 n 个树种名称
    for (int i = 0; i < n; i++) {
        fgets(arr[i], MAX_LEN, stdin);            // 读取一行（可能含空格）
        arr[i][strcspn(arr[i], "\r\n")] = '\0';   // 去掉尾部的换行符
    }

    // 使用标准库 qsort 对数组按字典序排序
    qsort(arr, n, MAX_LEN,
          (int (*)(const void *, const void *))strcmp);

    // 一次扫描：排序后相同名称相邻，统计每种的数量并输出
    int i = 0;                     // 当前扫描位置
    while (i < n) {                // 遍历所有树种
        int j = i;                 // 从当前位置向后查找相同名称
        while (j < n && strcmp(arr[j], arr[i]) == 0) j++; // 找到相同名称的下边界
        int cnt = j - i;           // 当前树种的出现次数
        // 输出：树种名称 + 百分比（保留 4 位小数）
        printf("%s %.4f%%\n", arr[i], (double)cnt * 100.0 / n);
        i = j;                     // 跳到下一种树种
    }

    free(arr);                    // 释放动态分配的内存
    return 0;                     // 程序正常结束
}
