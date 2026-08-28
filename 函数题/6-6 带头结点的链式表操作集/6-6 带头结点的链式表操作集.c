/*
 * ============================================================================
 * 带头结点的链式表操作集 — C 语言实现
 * ============================================================================
 *
 * 带头结点链表的特点：
 *   - 头结点不存储有效数据，其 Next 指向第一个实际结点
 *   - 空表：头结点存在，但其 Next = NULL
 *   - 插入/删除时不需要特殊处理表头情况（因为有头结点）
 *   - P = NULL 表示插入在表尾
 *
 * 操作：MakeEmpty、Find、Insert、Delete
 */

/*
 * MakeEmpty — 创建并返回一个空的带头结点的线性表
 * 分配头结点，设置 Next = NULL
 */
List MakeEmpty()
{
    List L = (List)malloc(sizeof(struct LNode));  // 创建头结点
    L->Next = NULL;                                // 空表：头结点 Next 为空
    return L;
}

/*
 * Find — 查找值为 X 的第一个结点，返回其指针
 * 从头结点的下一个开始遍历（跳过头结点）
 */
Position Find( List L, ElementType X )
{
    Position p = L->Next;
    while (p != NULL) {
        if (p->Data == X)
            return p;
        p = p->Next;
    }
    return ERROR;
}

bool Insert( List L, ElementType X, Position P )
{
    Position prev = L;              // prev 从头结点开始

    if (P != NULL) {
        /* 指定位置插入：找到 P 的前驱 prev */
        while (prev != NULL && prev->Next != P)
            prev = prev->Next;
        if (prev == NULL) {         // P 不在链表中
            printf("Wrong Position for Insertion\n");
            return false;
        }
    } else {
        /* P = NULL 表示插入在表尾 */
        while (prev->Next != NULL)
            prev = prev->Next;      // prev 移动到最后一个结点
    }

    /* 创建新结点，将其插入 prev 之后 */
    Position newNode = (Position)malloc(sizeof(struct LNode));
    newNode->Data = X;
    newNode->Next = P;              // 新结点指向原来的 P 位置
    prev->Next = newNode;           // prev 的 Next 指向新结点
    return true;
}

/*
 * Delete — 删除位置 P 的结点
 * 找到 P 的前驱 prev，将 prev->Next 跳过 P，释放 P
 */
bool Delete( List L, Position P )
{
    Position prev = L;
    while (prev != NULL && prev->Next != P)
        prev = prev->Next;

    if (prev == NULL || P == NULL) {
        printf("Wrong Position for Deletion\n");
        return false;
    }

    prev->Next = P->Next;
    free(P);
    return true;
}
