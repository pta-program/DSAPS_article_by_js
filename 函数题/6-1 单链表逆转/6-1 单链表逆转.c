/*
 * Reverse — 逆转单链表，返回新表头
 *
 * 算法：经典的三指针迭代反转法
 *   prev  — 指向已反转部分链表的表头
 *   curr  — 指向当前正在处理的结点
 *   next  — 暂存当前结点的下一个结点，防止断链
 *
 * 每轮迭代：
 *   1. 保存 curr->Next 到 next
 *   2. 将 curr->Next 指向 prev（反转指针方向）
 *   3. prev 和 curr 同时前进一步
 *
 * 时间复杂度 O(n)，空间复杂度 O(1)
 */
List Reverse( List L )
{
    List prev = NULL;     // 已反转部分的表头，初始为空
    List curr = L;        // 当前处理的结点，从头开始
    List next = NULL;     // 暂存下一个结点
    while (curr != NULL) {
        next = curr->Next;   // 保存下一个结点
        curr->Next = prev;   // 反转当前结点的指针
        prev = curr;         // prev 前进一步
        curr = next;         // curr 前进一步
    }
    return prev;             // prev 即为反转后的新表头
}
