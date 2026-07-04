/*
 * ============================================================================
 * 链式表操作集 — C 语言实现（不带头结点）
 * ============================================================================
 *
 * 操作：Find（查找）、Insert（插入）、Delete（删除）
 *
 * 约定：
 *   - List / Position 均为指向结点的指针
 *   - P = NULL 表示插入在表尾；P = L 表示插入在表头
 *   - ERROR = NULL，表示非法操作返回值
 *
 * 不带头结点链表的特点：
 *   - 表头即第一个实际结点，删除/插入表头时需要特殊处理
 *   - 空表：L == NULL
 */

/*
 * Find — 找到值为 X 的第一个结点，返回其位置指针
 *
 * 算法原理：从头遍历链表，逐个比较 Data，命中则返回结点指针，未命中返回 ERROR
 * 时间复杂度 O(n)，空间复杂度 O(1)
 */
Position Find( List L, ElementType X )
{
    while (L != NULL) {                        // 遍历链表直到末尾
        if (L->Data == X)                      // 找到目标值
            return L;                          // 返回结点指针
        L = L->Next;                           // 移动到下一个结点
    }
    return ERROR;                              // 遍历完未找到，返回 ERROR
}

/*
 * Insert — 将元素 X 插入到位置 P 之前
 *
 * 算法原理（分三种情况）：
 *
 *   情况 1：P == NULL，插入到表尾
 *     - 如果原表为空（L == NULL），新结点成为表头
 *     - 如果原表非空，遍历到最后一个结点，将新结点链入
 *
 *   情况 2：P == L，插入到表头
 *     - 新结点的 Next 指向原表头 L，返回新结点作为新表头
 *
 *   情况 3：P 为链表中间某个结点
 *     - 先找到 P 的前驱结点 prev（prev->Next == P）
 *     - 将新结点插入 prev 和 P 之间
 *     - 如果 prev == NULL，说明 P 不在链表中
 *
 * 返回值：成功返回新的表头指针；失败返回 ERROR
 */
List Insert( List L, ElementType X, Position P )
{
    /* 创建新结点，初始化数据域和指针域 */
    Position newNode = (Position)malloc(sizeof(struct LNode));
    newNode->Data = X;
    newNode->Next = NULL;

    /* 情况 1：P == NULL，插入到表尾 */
    if (P == NULL) {
        if (L == NULL)                         // 原表为空，新结点即为表头
            return newNode;
        Position tail = L;                     // 从表头开始遍历找表尾
        while (tail->Next != NULL)             // 找到最后一个结点（Next 为 NULL）
            tail = tail->Next;
        tail->Next = newNode;                  // 将新结点链入表尾
        return L;                              // 表头不变，返回原表头
    }

    /* 情况 2：P == L，插入到表头 */
    if (P == L) {
        newNode->Next = L;                     // 新结点指向原表头
        return newNode;                        // 返回新结点作为新表头
    }

    /* 情况 3：P 为链表中间结点，寻找 P 的前驱 prev */
    Position prev = L;
    while (prev != NULL && prev->Next != P)    // 遍历直到找到 P 的前驱或到达链表末尾
        prev = prev->Next;
    if (prev != NULL) {                        // 找到了 P 的前驱 prev
        newNode->Next = P;                     // 新结点指向 P
        prev->Next = newNode;                  // prev 指向新结点
        return L;                              // 表头不变，返回原表头
    }

    /* P 不在链表中，插入失败 */
    free(newNode);                             // 释放已分配的新结点
    printf("Wrong Position for Insertion\n");
    return ERROR;                              // 返回 ERROR
}

/*
 * Delete — 删除位置 P 的结点
 *
 * 算法原理（分三种情况）：
 *
 *   情况 1：表为空（L == NULL）或 P == NULL，直接返回错误
 *
 *   情况 2：P == L，删除表头
 *     - 保存表头指针，将表头后移一位（L->Next）
 *     - 释放被删除结点，返回新表头
 *
 *   情况 3：P 为链表中间某个结点
 *     - 先找到 P 的前驱结点 prev（prev->Next == P）
 *     - 将 prev->Next 跳过 P，指向 P->Next
 *     - 释放 P，返回原表头
 *     - 如果 prev == NULL，说明 P 不在链表中
 *
 * 返回值：成功返回新的表头指针；失败返回 ERROR
 */
List Delete( List L, Position P )
{
    /* 情况 1：表为空或 P 为空，删除失败 */
    if (L == NULL || P == NULL) {
        printf("Wrong Position for Deletion\n");
        return ERROR;
    }

    /* 情况 2：P == L，删除表头 */
    if (P == L) {
        List newHead = L->Next;                // 保存新表头（原表头的下一个结点）
        free(P);                               // 释放被删除的表头结点
        return newHead;                        // 返回新表头
    }

    /* 情况 3：P 为链表中间结点，寻找 P 的前驱 prev */
    Position prev = L;
    while (prev != NULL && prev->Next != P)    // 遍历直到找到 P 的前驱或到达链表末尾
        prev = prev->Next;
    if (prev != NULL) {                        // 找到了 P 的前驱 prev
        prev->Next = P->Next;                  // prev 跳过 P，直接指向 P 的下一个结点
        free(P);                               // 释放被删除的结点
        return L;                              // 表头不变，返回原表头
    }

    /* P 不在链表中，删除失败 */
    printf("Wrong Position for Deletion\n");
    return ERROR;                              // 返回 ERROR
}