/**
 * 两个有序序列的中位数 - C语言实现
 * 
 * 实现原理：
 * 1. 题目要求：已知两个等长的非降序序列S1、S2，求它们并集的中位数
 * 2. 中位数定义：对于长度为M的有序序列A₀, A₁, ⋯, A_{M-1}，中位数指A_{(M-1)/2}的值
 *    即第⌊(M+1)/2⌋个数（从1开始计数）
 * 3. 由于两个序列长度均为N，合并后总长度为2N，中位数位置为第N个数（从1开始计数）
 *    对应索引为N-1（从0开始计数）
 * 4. 使用双指针法，遍历两个序列，找到第N小的元素即为中位数
 * 
 * 算法复杂度：
 * - 时间复杂度：O(N) - 只需遍历两个序列各一次
 * - 空间复杂度：O(1) - 只需常数额外空间
 */

#include <stdio.h>
#include <stdlib.h>

int main() {
    // 定义变量
    int N;              // 序列长度
    int i = 0, j = 0;   // 两个序列的遍历指针
    int count = 0;      // 计数器，记录当前找到的元素个数
    int median;         // 存储中位数
    
    // 读取序列长度
    scanf("%d", &N);
    
    // 分配内存存储两个序列
    int *s1 = (int *)malloc(N * sizeof(int));
    int *s2 = (int *)malloc(N * sizeof(int));
    
    // 读取第一个序列
    for (int k = 0; k < N; k++) {
        scanf("%d", &s1[k]);
    }
    
    // 读取第二个序列
    for (int k = 0; k < N; k++) {
        scanf("%d", &s2[k]);
    }
    
    // 双指针遍历，找到中位数
    // 合并后总长度为2N，中位数是第N个元素（从1开始计数）
    // 即遍历到第N-1个索引（从0开始计数）
    while (i < N && j < N) {
        // 如果已经找到第N个元素，立即停止
        if (count == N - 1) {
            median = (s1[i] < s2[j]) ? s1[i] : s2[j];
            count++;
            break;
        }
        
        if (s1[i] <= s2[j]) {
            // 如果s1当前元素较小，取s1[i]
            median = s1[i];
            i++;
        } else {
            // 如果s2当前元素较小，取s2[j]
            median = s2[j];
            j++;
        }
        count++;
    }
    
    // 如果s1还有剩余元素，继续取
    while (count < N && i < N) {
        median = s1[i];
        i++;
        count++;
    }
    
    // 如果s2还有剩余元素，继续取
    while (count < N && j < N) {
        median = s2[j];
        j++;
        count++;
    }
    
    // 输出中位数
    printf("%d\n", median);
    
    // 释放内存
    free(s1);
    free(s2);
    
    return 0;
}