#include <stdio.h>              // 引入标准输入输出头文件

int inStack[1000], outStack[1000];  // 输入栈和输出栈的数组
int inTop = -1, outTop = -1;   // 输入栈和输出栈的栈顶指针，-1表示栈为空
int inCap, outCap;              // 输入栈和输出栈的最大容量

void inPush(int val) { inStack[++inTop] = val; }  // 输入栈入栈：栈顶指针先加1，再存入元素
int inPop() { return inStack[inTop--]; }           // 输入栈出栈：返回栈顶元素，栈顶指针减1
int inFull() { return inTop == inCap - 1; }        // 判断输入栈是否已满
int inEmpty() { return inTop == -1; }              // 判断输入栈是否为空

void outPush(int val) { outStack[++outTop] = val; }  // 输出栈入栈：栈顶指针先加1，再存入元素
int outPop() { return outStack[outTop--]; }           // 输出栈出栈：返回栈顶元素，栈顶指针减1
int outFull() { return outTop == outCap - 1; }        // 判断输出栈是否已满
int outEmpty() { return outTop == -1; }               // 判断输出栈是否为空

void transfer() {               // 转移操作：将输入栈的所有元素依次弹出并压入输出栈
    while (!inEmpty()) {        // 当输入栈不为空时
        outPush(inPop());       // 从输入栈弹出一个元素，压入输出栈（实现顺序反转）
    }
}

void AddQ(int item) {           // 入队操作
    if (!inFull()) {             // 如果输入栈未满
        inPush(item);           // 直接将元素压入输入栈
    } else if (outEmpty()) {    // 如果输入栈已满但输出栈为空
        transfer();             // 将输入栈元素全部转移到输出栈
        inPush(item);           // 转移后输入栈有空位，将元素压入输入栈
    } else {                    // 输入栈满且输出栈非空，无法入队
        printf("ERROR:Full\n"); // 输出队满错误信息
    }
}

void DeleteQ() {                // 出队操作
    if (!outEmpty()) {          // 如果输出栈不为空
        printf("%d\n", outPop()); // 直接从输出栈弹出栈顶元素（即队首元素）
    } else if (!inEmpty()) {    // 如果输出栈为空但输入栈不为空
        transfer();             // 将输入栈元素全部转移到输出栈
        printf("%d\n", outPop()); // 转移后从输出栈弹出队首元素
    } else {                    // 两个栈都为空，队列为空
        printf("ERROR:Empty\n"); // 输出队空错误信息
    }
}

int main() {                    // 主函数入口
    int n1, n2;                 // 两个栈的容量
    scanf("%d %d", &n1, &n2);   // 读取两个栈的容量

    // 较小的栈作为输入栈，较大的栈作为输出栈
    // 原因：转移时输入栈所有元素都要压入输出栈，输出栈必须能容纳
    if (n1 <= n2) {             // 如果n1较小
        inCap = n1; outCap = n2; // n1作为输入栈容量，n2作为输出栈容量
    } else {                    // 如果n2较小
        inCap = n2; outCap = n1; // n2作为输入栈容量，n1作为输出栈容量
    }

    char op;                    // 操作类型字符
    while (scanf(" %c", &op) && op != 'T') {  // 循环读取操作，遇到T结束
        if (op == 'A') {        // A操作：入队
            int item;           // 入队元素
            scanf("%d", &item); // 读取入队元素
            AddQ(item);         // 调用入队函数
        } else if (op == 'D') { // D操作：出队
            DeleteQ();          // 调用出队函数
        }
    }

    return 0;                   // 程序正常结束
}
