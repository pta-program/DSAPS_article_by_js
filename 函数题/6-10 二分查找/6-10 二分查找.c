/*
 * BinarySearch — 在有序顺序表中二分查找元素 X
 *
 * 算法原理：
 *   利用有序数组的特性，每次将查找范围缩小一半。
 *   取中间位置 mid，比较 L->Data[mid] 与 X：
 *     - 相等：找到，返回 mid
 *     - L->Data[mid] < X：X 在右半区间，left = mid + 1
 *     - L->Data[mid] > X：X 在左半区间，right = mid - 1
 *
 *   循环条件：left <= right（区间非空）
 *   退出条件：left > right（未找到）
 *
 * 注意：本题数组下标从 1 开始（left 初始为 1），
 *       right = L->Last 表示最后一个有效元素的下标。
 *
 * 时间复杂度 O(log n)，空间复杂度 O(1)
 */
Position BinarySearch( List L, ElementType X )
{
    int left = 1;                              // 查找区间左边界，从下标 1 开始
    int right = L->Last;                       // 查找区间右边界，最后一个有效元素
    int mid;                                   // 中间位置

    while (left <= right) {                    // 区间非空时继续查找
        mid = left + (right - left) / 2;       // 计算中间位置，避免溢出
        if (L->Data[mid] == X) {               // 找到目标元素
            return mid;                        // 返回其下标
        } else if (L->Data[mid] < X) {         // X 在右半区间
            left = mid + 1;                    // 调整左边界
        } else {                               // X 在左半区间
            right = mid - 1;                   // 调整右边界
        }
    }

    return NotFound;                           // 未找到，返回 NotFound
}