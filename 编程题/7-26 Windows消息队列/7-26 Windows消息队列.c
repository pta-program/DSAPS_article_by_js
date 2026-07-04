/*
 * 实现方式：
 * 使用数组模拟最小堆（1-based索引），手动实现push和pop操作。
 * 堆节点存储消息的优先级和名称。push时新元素从堆底上浮，pop时堆顶元素下沉。
 * 使用scanf读取输入，printf输出结果，时间复杂度O(n log n)。
 */
#include <stdio.h>      // 标准输入输出库
#include <stdlib.h>     // 标准库（malloc等）
#include <string.h>     // 字符串处理库

#define MAXN 100005     // 队列最大容量，对应题目n≤10^5

// 消息结构体，存储优先级和名称
typedef struct {
    int priority;       // 优先级值（越小优先级越高）
    char name[16];      // 消息名称（最大10字符，留冗余）
} Msg;

static Msg heap[MAXN];  // 堆数组，1-based索引
static int heap_size;   // 当前堆大小

// 交换两个Msg结构体的值
void swap(Msg *a, Msg *b) {
    Msg t = *a;         // 临时变量保存a的值
    *a = *b;            // 将b的值赋给a
    *b = t;             // 将临时变量的值赋给b
}

// 向堆中插入元素（最小堆上浮操作）
void push(int priority, const char *name) {
    heap_size++;                    // 堆大小加1
    heap[heap_size].priority = priority;  // 设置新节点的优先级
    strcpy(heap[heap_size].name, name);   // 复制消息名称到堆节点
    int i = heap_size;              // 当前节点索引
    // 向上调整：如果当前节点优先级小于父节点，则交换
    while (i > 1 && heap[i].priority < heap[i / 2].priority) {
        swap(&heap[i], &heap[i / 2]);    // 与父节点交换
        i /= 2;                     // 移动到父节点位置
    }
}

// 删除堆顶元素（最小堆下沉操作）
void pop(void) {
    if (heap_size == 0) return;     // 堆为空，直接返回
    heap[1] = heap[heap_size];      // 将最后一个元素移到堆顶
    heap_size--;                    // 堆大小减1
    int i = 1;                      // 当前节点索引（从堆顶开始）
    // 向下调整：找到更小的子节点进行交换
    while (2 * i <= heap_size) {
        int child = 2 * i;          // 左子节点索引
        // 如果右子节点存在且优先级更小，选择右子节点
        if (child + 1 <= heap_size && heap[child + 1].priority < heap[child].priority)
            child++;
        // 如果当前节点优先级不大于子节点，调整结束
        if (heap[i].priority <= heap[child].priority) break;
        swap(&heap[i], &heap[child]);    // 与子节点交换
        i = child;                  // 移动到子节点位置
    }
}

int main(void) {
    int n;                          // 指令数量
    scanf("%d", &n);                // 读取指令数量
    heap_size = 0;                  // 初始化堆为空
    char op[8];                     // 存储操作指令（GET或PUT）
    while (n--) {                   // 循环处理每条指令
        scanf("%s", op);            // 读取操作指令
        if (op[0] == 'P') {         // 判断是否为PUT操作
            char name[16];          // 存储消息名称
            int p;                  // 存储消息优先级
            scanf("%s %d", name, &p);   // 读取消息名称和优先级
            push(p, name);          // 将消息插入堆中
        } else {                    // GET操作
            if (heap_size == 0)     // 判断堆是否为空
                printf("EMPTY QUEUE!\n");  // 堆空输出提示
            else {
                printf("%s\n", heap[1].name);  // 输出堆顶元素（优先级最高）
                pop();              // 删除堆顶元素
            }
        }
    }
    return 0;                       // 程序正常结束
}
