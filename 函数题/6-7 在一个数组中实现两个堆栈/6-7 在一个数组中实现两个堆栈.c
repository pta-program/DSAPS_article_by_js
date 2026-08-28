/*
 * ============================================================================
 * 在一个数组中实现两个堆栈 — C 语言实现
 * ============================================================================
 *
 * 核心思路：
 *   用一个数组同时容纳两个堆栈，堆栈 1 从数组左端 (下标 0) 向右增长，
 *   堆栈 2 从数组右端 (下标 MaxSize-1) 向左增长。最大利用数组空间。
 *
 *   [Stack1 → ··· ← Stack2]
 *    ↑                    ↑
 *   Top1                Top2
 *
 *   初始状态：Top1 = -1, Top2 = MaxSize
 *   栈满条件：Top1 + 1 == Top2（两个栈顶碰头）
 */

/*
 * CreateStack — 创建容量为 MaxSize 的双堆栈
 * 分配 SNode 和 Data 数组，初始化 Top1/Top2
 */
Stack CreateStack( int MaxSize )
{
    Stack S = (Stack)malloc(sizeof(struct SNode));          // 分配 SNode
    S->Data = (ElementType *)malloc(sizeof(ElementType) * MaxSize); // 分配数组
    S->Top1 = -1;          // 堆栈 1 初始为空
    S->Top2 = MaxSize;     // 堆栈 2 初始为空（Top2 从数组尾端开始）
    S->MaxSize = MaxSize;  // 记录最大容量
    return S;
}

/*
 * Push — 将 X 压入指定编号的堆栈
 *
 * Tag == 1: 操作堆栈 1（Top1 右移）
 * Tag == 2: 操作堆栈 2（Top2 左移）
 *
 * 先判满：Top1 + 1 == Top2 表示两栈顶相邻，空间用尽
 */
bool Push( Stack S, ElementType X, int Tag )
{
    /* 判满：两个栈顶相邻 */
    if (S->Top1 + 1 == S->Top2) {
        printf("Stack Full\n");
        return false;
    }
    if (Tag == 1) {
        S->Data[++(S->Top1)] = X;   // Top1 右移一位，存入 X
    } else {
        S->Data[--(S->Top2)] = X;   // Top2 左移一位，存入 X
    }
    return true;
}

/*
 * Pop — 从指定编号的堆栈弹出栈顶元素
 *
 * Tag == 1: 堆栈 1，Top1 == -1 为空
 * Tag == 2: 堆栈 2，Top2 == MaxSize 为空
 */
ElementType Pop( Stack S, int Tag )
{
    if (Tag == 1) {
        if (S->Top1 == -1) {
            printf("Stack 1 Empty\n");
            return ERROR;
        }
        return S->Data[(S->Top1)--];
    } else {
        if (S->Top2 == S->MaxSize) {
            printf("Stack 2 Empty\n");
            return ERROR;
        }
        return S->Data[(S->Top2)++];
    }
}
