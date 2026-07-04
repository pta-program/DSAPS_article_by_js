/*
 * GetHeight — 返回二叉树的高度
 *
 * 递归定义：
 *   - 空树高度为 0
 *   - 非空树高度 = max(左子树高度, 右子树高度) + 1
 *
 * 时间复杂度 O(n)，空间复杂度 O(h)（h 为树高，递归栈深度）
 */
int GetHeight( BinTree BT )
{
    if (BT == NULL)                       // 空树高度为 0
        return 0;
    int leftHeight = GetHeight(BT->Left);  // 递归求左子树高度
    int rightHeight = GetHeight(BT->Right);// 递归求右子树高度
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}
