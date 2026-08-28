/*
 * 魔法优惠券问题 - C语言实现
 * 
 * 【实现原理】
 * 这是一个贪心算法问题。要最大化优惠券与商品配对的总回报，需要遵循以下策略：
 * 
 * 1. 将优惠券和商品分别按升序排序
 * 2. 使用双指针法：
 *    - 左指针从最小元素开始（可能是负数）
 *    - 右指针从最大元素开始（可能是正数）
 * 3. 比较两端乘积：
 *    - 如果左边两个负数相乘（结果为正数），乘积大于右边两个正数相乘，则取左边配对
 *    - 否则取右边配对
 *    - 当遇到正数与负数相乘（结果为负数）时，停止该方向的配对
 * 4. 累加所有有效配对的乘积，得到最大回报
 * 
 * 【贪心策略证明】
 * - 对于正数：最大的正数应该与最大的正数相乘，才能得到最大的乘积
 * - 对于负数：最小的负数应该与最小的负数相乘，因为负数×负数=正数，且绝对值越大结果越大
 * - 正数与负数相乘会产生负回报，应避免这种配对
 * 
 * 【时间复杂度】
 * O(N log N + M log M)，其中N是优惠券数量，M是商品数量
 * 主要开销来自排序操作
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define BIG_BASE 1000000000U
#define BIG_DIGITS 16

typedef struct {
    uint32_t digit[BIG_DIGITS];
    int size;
} BigInteger;

static void add_u64(BigInteger *value, uint64_t addend) {
    int i = 0;
    uint64_t carry = 0;

    while (addend != 0 || carry != 0) {
        uint64_t part = addend % BIG_BASE;
        uint64_t sum = (uint64_t)value->digit[i] + part + carry;
        value->digit[i] = (uint32_t)(sum % BIG_BASE);
        carry = sum / BIG_BASE;
        addend /= BIG_BASE;
        if (i + 1 > value->size) {
            value->size = i + 1;
        }
        i++;
    }
}

static void print_big_integer(const BigInteger *value) {
    int i;

    if (value->size == 0) {
        puts("0");
        return;
    }
    printf("%u", value->digit[value->size - 1]);
    for (i = value->size - 2; i >= 0; i--) {
        printf("%09u", value->digit[i]);
    }
    putchar('\n');
}

// 比较函数，用于qsort升序排序
int cmp(const void *a, const void *b) {
    long long left = *(const long long *)a;
    long long right = *(const long long *)b;
    return (left > right) - (left < right);
}

int main() {
    // 乘积本身可以放入long long，但所有乘积的总和可能超过64位整数。
    int n, m;
    BigInteger res = {{0}, 0};
    
    // 读取优惠券数量和优惠券数组
    scanf("%d", &n);
    long long *coupons = (long long *)malloc(n * sizeof(long long));
    for (int i = 0; i < n; i++) {
        scanf("%lld", &coupons[i]);
    }
    
    // 读取商品数量和商品数组
    scanf("%d", &m);
    long long *products = (long long *)malloc(m * sizeof(long long));
    for (int i = 0; i < m; i++) {
        scanf("%lld", &products[i]);
    }
    
    // 对优惠券数组和商品数组进行升序排序
    qsort(coupons, n, sizeof(long long), cmp);
    qsort(products, m, sizeof(long long), cmp);
    
    // 初始化双指针：左指针从数组头部开始，右指针从数组尾部开始
    int left_c = 0, left_p = 0;
    int right_c = n - 1, right_p = m - 1;
    
    // 处理正数部分：从右向左配对最大的正数
    while (right_c >= left_c && right_p >= left_p) {
        // 如果两个正数相乘，累加结果并移动指针
        if (coupons[right_c] > 0 && products[right_p] > 0) {
            add_u64(&res, (uint64_t)(coupons[right_c] * products[right_p]));
            right_c--;
            right_p--;
        } else {
            // 如果遇到非正数配对，停止正数部分处理
            break;
        }
    }
    
    // 处理负数部分：从左向右配对最小的负数（负数×负数=正数）
    while (left_c <= right_c && left_p <= right_p) {
        // 如果两个负数相乘（结果为正），累加结果并移动指针
        if (coupons[left_c] < 0 && products[left_p] < 0) {
            add_u64(&res, (uint64_t)(coupons[left_c] * products[left_p]));
            left_c++;
            left_p++;
        } else {
            // 如果遇到非负数配对，停止负数部分处理
            break;
        }
    }
    
    // 输出最大回报
    print_big_integer(&res);
    
    // 释放动态分配的内存
    free(coupons);
    free(products);
    
    return 0;
}
