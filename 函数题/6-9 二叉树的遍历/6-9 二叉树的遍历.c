/*
 * ============================================================================
 * 二叉树的遍历 — C 语言实现
 * ============================================================================
 *
 * 四种遍历方式：
 *   中序 (Inorder):   左 → 根 → 右
 *   先序 (Preorder):  根 → 左 → 右
 *   后序 (Postorder): 左 → 右 → 根
 *   层序 (Levelorder):自上而下、自左而右逐层访问（借助队列）
 *
 * 输出格式：每个访问的 Data 前加一个空格，如 " A B C"
 */

/*
 * InorderTraversal — 中序遍历：左子树 → 根结点 → 右子树
 * 递归实现，时间复杂度 O(n)
 */
void InorderTraversal( BinTree BT )
{
    if (BT == NULL) return;               // 空树直接返回
    InorderTraversal(BT->Left);           // 遍历左子树
    printf(" %c", BT->Data);              // 访问根结点
    InorderTraversal(BT->Right);          // 遍历右子树
}

/*
 * PreorderTraversal — 先序遍历：根结点 → 左子树 → 右子树
 * 递归实现，时间复杂度 O(n)
 */
void PreorderTraversal( BinTree BT )
{
    if (BT == NULL) return;               // 空树直接返回
    printf(" %c", BT->Data);              // 访问根结点
    PreorderTraversal(BT->Left);          // 遍历左子树
    PreorderTraversal(BT->Right);         // 遍历右子树
}

/*
 * PostorderTraversal — 后序遍历：左子树 → 右子树 → 根结点
 * 递归实现，时间复杂度 O(n)
 */
void PostorderTraversal( BinTree BT )
{
    if (BT == NULL) return;               // 空树直接返回
    PostorderTraversal(BT->Left);         // 遍历左子树
    PostorderTraversal(BT->Right);        // 遍历右子树
    printf(" %c", BT->Data);              // 访问根结点
}

/*
 * LevelorderTraversal — 层序遍历
 *
 * 借助队列实现 BFS：
 *   1. 根结点入队
 *   2. 队首出队并访问
 *   3. 将出队结点的左右孩子（若存在）依次入队
 *   4. 重复步骤 2-3 直到队列为空
 *
 * 时间复杂度 O(n)，空间复杂度 O(n)
 */
void LevelorderTraversal( BinTree BT )
{
    if (BT == NULL) return;               // 空树直接返回
    BinTree queue[100];                   // 用数组模拟队列，假设结点数 ≤ 100
    int front = 0, rear = 0;              // 队首和队尾指针
    queue[rear++] = BT;                   // 根结点入队
    while (front < rear) {
        BinTree node = queue[front++];    // 出队一个结点
        printf(" %c", node->Data);        // 访问
        if (node->Left)                   // 左孩子入队
            queue[rear++] = node->Left;
        if (node->Right)                  // 右孩子入队
            queue[rear++] = node->Right;
    }
}
