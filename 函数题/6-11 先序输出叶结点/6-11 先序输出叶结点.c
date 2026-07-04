/*
 * PreorderPrintLeaves — 先序遍历二叉树并输出所有叶结点
 *
 * 算法原理：
 *   先序遍历顺序：根 → 左 → 右
 *   叶结点定义：左右子树均为空（Left == NULL && Right == NULL）
 *
 *   递归过程：
 *     1. 如果当前结点为空，直接返回
 *     2. 如果当前结点是叶结点，输出其数据
 *     3. 递归遍历左子树
 *     4. 递归遍历右子树
 *
 *   输出格式：每个叶结点数据前加一个空格，如 " A B C"
 *
 * 时间复杂度 O(n)，空间复杂度 O(h)（h 为树高，递归栈深度）
 */
void PreorderPrintLeaves( BinTree BT )
{
    if ( BT == NULL )                          // 空树，直接返回
        return;
    if ( BT->Left == NULL && BT->Right == NULL )  // 当前结点是叶结点
        printf(" %c", BT->Data);               // 输出叶结点数据
    PreorderPrintLeaves( BT->Left );           // 递归遍历左子树
    PreorderPrintLeaves( BT->Right );          // 递归遍历右子树
}