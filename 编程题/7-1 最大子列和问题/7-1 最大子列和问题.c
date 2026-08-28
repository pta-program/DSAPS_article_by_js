/*
 * 实现过程：
 * 本题采用"在线处理"算法（Kadane算法），时间复杂度 O(K)，空间复杂度 O(1)。
 *
 * 核心思路：
 * 1. 用 ThisSum 记录当前子列和，MaxSum 记录历史最大子列和。
 * 2. 逐个读取元素，将每个元素累加到 ThisSum 中。
 * 3. 若 ThisSum < 0，说明当前前缀对后续子列和只有负贡献，果断抛弃（重置为0）。
 * 4. 若 ThisSum > MaxSum，则更新 MaxSum。
 * 5. 最终 MaxSum 即为最大子列和。若所有元素均为负数，MaxSum 保持为0。
 *
 * 为什么可以"在线处理"：
 * - 当 ThisSum 变为负数时，无论后面接什么正数，加上负前缀只会更小，
 *   因此不如从0重新开始累加，这就是"抛弃负前缀"的贪心策略。
 */

#include <stdio.h> // 引入标准输入输出库，用于 scanf 和 printf 函数

int main( void ) // 主函数，程序入口；void 表示不接收命令行参数
{
    int K, i, N; // 声明三个整型变量：K 为元素个数，i 为循环计数器，N 为当前读入的整数
    long long ThisSum = 0, MaxSum = 0; // 声明两个长整型变量：ThisSum 记录当前子列和，MaxSum 记录已知最大子列和，均初始化为 0

    scanf( "%d", &K ); // 从标准输入读取一个整数存入 K，表示序列中元素的个数
    for ( i = 0; i < K; i++ ) { // 循环 K 次，依次处理每个元素；i 从 0 开始，小于 K 时继续循环
        scanf( "%d", &N ); // 读取当前元素的值并存入 N
        ThisSum += N; // 将当前元素 N 累加到当前子列和 ThisSum 中
        if ( ThisSum < 0 ) // 判断当前子列和是否为负数
            ThisSum = 0; // 如果为负数，则重置当前子列和为 0（放弃该段前缀，重新开始累加）
        else if ( ThisSum > MaxSum ) // 否则判断当前子列和是否大于已知最大子列和
            MaxSum = ThisSum; // 如果更大，则更新最大子列和为当前子列和
    }
    printf( "%lld\n", MaxSum ); // 以 long long 格式输出最大子列和，并换行

    return 0; // 主函数正常结束，返回 0 表示程序执行成功
}
