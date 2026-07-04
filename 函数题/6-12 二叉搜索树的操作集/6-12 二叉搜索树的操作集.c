/*
 * ============================================================================
 * 二叉搜索树（BST）操作集 — C 语言实现
 * ============================================================================
 *
 * 二叉搜索树性质：
 *   - 左子树所有结点的值 < 根结点的值
 *   - 右子树所有结点的值 > 根结点的值
 *   - 左右子树也都是二叉搜索树
 *
 * 操作：Find（查找）、FindMin（找最小值）、FindMax（找最大值）、
 *       Insert（插入）、Delete（删除）
 */

/*
 * Find — 在二叉搜索树中查找值为 X 的结点，返回其指针
 *
 * 算法原理：
 *   利用 BST 性质，每次比较缩小一半范围：
 *     - X < BST->Data：递归查找左子树
 *     - X > BST->Data：递归查找右子树
 *     - X == BST->Data：找到，返回当前结点
 *     - BST == NULL：未找到，返回 NULL
 *
 * 平均时间复杂度 O(log n)，最坏 O(n)（退化成链表）
 */
Position Find( BinTree BST, ElementType X )
{
    if ( BST == NULL )                         // 树为空，未找到
        return NULL;
    if ( X < BST->Data )                       // X 小于根，查找左子树
        return Find( BST->Left, X );
    else if ( X > BST->Data )                  // X 大于根，查找右子树
        return Find( BST->Right, X );
    else                                       // X 等于根，找到
        return BST;
}

/*
 * FindMin — 返回二叉搜索树中值最小的结点
 *
 * 算法原理：BST 的最小值在最左路径的末端（左子树为空的结点）
 */
Position FindMin( BinTree BST )
{
    if ( BST == NULL )                         // 树为空
        return NULL;
    if ( BST->Left == NULL )                   // 左子树为空，当前即为最小值
        return BST;
    return FindMin( BST->Left );               // 递归查找左子树
}

/*
 * FindMax — 返回二叉搜索树中值最大的结点
 *
 * 算法原理：BST 的最大值在最右路径的末端（右子树为空的结点）
 */
Position FindMax( BinTree BST )
{
    if ( BST == NULL )                         // 树为空
        return NULL;
    if ( BST->Right == NULL )                  // 右子树为空，当前即为最大值
        return BST;
    return FindMax( BST->Right );              // 递归查找右子树
}

/*
 * Insert — 将值 X 插入二叉搜索树
 *
 * 算法原理：
 *   1. 如果树为空，创建新结点作为根
 *   2. 如果 X < 当前结点值，递归插入左子树
 *   3. 如果 X > 当前结点值，递归插入右子树
 *   4. 如果 X == 当前结点值，不做操作（BST 不允许重复值）
 *
 * 注意：递归返回时需要将子树的根重新赋值给父结点的 Left/Right
 */
BinTree Insert( BinTree BST, ElementType X )
{
    if ( BST == NULL ) {                       // 树为空，创建新结点
        BST = (BinTree)malloc( sizeof( struct TNode ) );
        BST->Data = X;
        BST->Left = BST->Right = NULL;
    } else if ( X < BST->Data ) {              // X 小于根，插入左子树
        BST->Left = Insert( BST->Left, X );
    } else if ( X > BST->Data ) {              // X 大于根，插入右子树
        BST->Right = Insert( BST->Right, X );
    }
    return BST;                                // 返回修改后的树
}

/*
 * Delete — 删除二叉搜索树中值为 X 的结点
 *
 * 算法原理（分三种情况）：
 *
 *   情况 1：被删除结点是叶结点（左右子树均为空）
 *     直接释放该结点，父结点指针置空
 *
 *   情况 2：被删除结点只有一个子树（左或右）
 *     将子树直接连接到父结点，释放被删除结点
 *
 *   情况 3：被删除结点有两个子树
 *     用其右子树的最小值（后继）替换被删除结点的值，
 *     然后删除右子树中的这个最小值结点（该结点最多只有一个右子树）
 *     或者用左子树的最大值（前驱）替换。
 *
 * 本题采用「右子树最小值」替换方案。
 */
BinTree Delete( BinTree BST, ElementType X )
{
    Position Tmp;                              // 临时指针，用于保存要释放的结点
    if ( BST == NULL ) {                       // 未找到目标结点
        printf( "Not Found\n" );
        return NULL;
    }
    if ( X < BST->Data ) {                     // X 小于根，递归删除左子树
        BST->Left = Delete( BST->Left, X );
    } else if ( X > BST->Data ) {              // X 大于根，递归删除右子树
        BST->Right = Delete( BST->Right, X );
    } else {                                   // 找到要删除的结点
        if ( BST->Left != NULL && BST->Right != NULL ) {
            /* 情况 3：左右子树都存在 */
            Tmp = FindMin( BST->Right );       // 找到右子树最小值结点
            BST->Data = Tmp->Data;             // 用最小值替换当前结点值
            BST->Right = Delete( BST->Right, Tmp->Data ); // 删除右子树中的最小值结点
        } else {
            /* 情况 1 或 2：只有一个子树或无子树 */
            Tmp = BST;                         // 保存要释放的结点
            if ( BST->Left == NULL )           // 只有右子树或无子树
                BST = BST->Right;              // 右子树顶上
            else                               // 只有左子树
                BST = BST->Left;               // 左子树顶上
            free( Tmp );                       // 释放被删除的结点
        }
    }
    return BST;                                // 返回修改后的树
}