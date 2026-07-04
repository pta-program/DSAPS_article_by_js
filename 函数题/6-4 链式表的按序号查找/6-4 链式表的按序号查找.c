/*
 * FindKth — 返回链式表的第 K 个元素（K 从 1 开始）
 *
 * 算法：从头遍历链表，用计数器 i 记录当前是第几个结点。
 * 当 i == K 时返回该结点的 Data；遍历完未找到则返回 ERROR。
 *
 * 时间复杂度 O(n)，空间复杂度 O(1)
 */
ElementType FindKth( List L, int K )
{
    int i = 1;                // 结点序号，从 1 开始
    while (L != NULL) {
        if (i == K)           // 找到第 K 个结点
            return L->Data;
        i++;                  // 序号 +1
        L = L->Next;          // 移向下一个结点
    }
    return ERROR;             // 链表长度不足 K，返回 ERROR
}
