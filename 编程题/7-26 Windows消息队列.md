## 7-26 Windows消息队列

- **分值：** 25分

## 题目描述

消息队列是 Windows 系统的基础。对于每个进程，系统维护一个消息队列。如果在进程中有特定事件发生，如点击鼠标、文字改变等，系统将把这个消息连同表示此消息优先级高低的正整数（称为优先级值）加到队列当中。同时，如果队列不是空的，这一进程循环地从队列中按照优先级获取消息。请注意优先级值低意味着优先级高。请编辑程序模拟消息队列，将消息加到队列中以及从队列中获取消息。

## 输入格式

输入第 1 行给出正整数 n（\le 10^5），随后 n 行，每行给出一个指令——`GET` 或 `PUT`，分别表示从队列中取出消息或将消息添加到队列中。如果指令是 `PUT`，后面就有一个消息名称、以及一个正整数表示消息的优先级，此数越小表示优先级越高。消息名称是长度不超过 10 个字符且不含空格的字符串；题目保证队列中消息的优先级无重复，且输入至少有一个 `GET`。

## 输出格式

对于每个 `GET` 指令，在一行中输出消息队列中优先级最高的消息的名称和参数。如果消息队列中没有消息，输出 `EMPTY QUEUE!`。对于 `PUT` 指令则没有输出。

## 输入样例
```
9
PUT msg1 5
PUT msg2 4
GET
PUT msg3 2
PUT msg4 4
GET
GET
GET
GET
```

## 输出样例
```
msg2
msg3
msg4
msg1
EMPTY QUEUE!
```

## 解题思路

本题采用优先队列，围绕题目给出的数据结构和约束完成核心计算，并处理边界情况。

## 代码流程说明

1. 读取题目规定的输入数据。
2. 使用优先队列完成主要处理。
3. 处理边界情况并整理结果。
4. 按指定格式输出结果。

## 代码实现


```javascript
const fs = require("fs");
const raw = fs.readFileSync(0, "utf8");
const tokens = raw.trim() ? raw.trim().split(/\s+/) : [];
let at = 0;

// 自定义最小堆按优先级取出消息，GET 只删除堆顶。
const n = Number(tokens[at++]),
  heap = [],
  out = [];
function push(item) {
  heap.push(item);
  let i = heap.length - 1;
  while (i && heap[i].priority < heap[(i - 1) >> 1].priority) {
    [heap[i], heap[(i - 1) >> 1]] = [heap[(i - 1) >> 1], heap[i]];
    i = (i - 1) >> 1;
  }
}
function pop() {
  const top = heap[0],
    last = heap.pop();
  if (heap.length) {
    heap[0] = last;
    for (let i = 0; ; ) {
      let c = i * 2 + 1;
      if (c >= heap.length) break;
      if (c + 1 < heap.length && heap[c + 1].priority < heap[c].priority) c++;
      if (heap[i].priority <= heap[c].priority) break;
      [heap[i], heap[c]] = [heap[c], heap[i]];
      i = c;
    }
  }
  return top;
}
for (let i = 0; i < n; i++) {
  const op = tokens[at++];
  if (op === "PUT")
    push({ name: tokens[at++], priority: Number(tokens[at++]) });
  else out.push(heap.length ? pop().name : "EMPTY QUEUE!");
}
console.log(out.join("\n"));
```

## 代码流程图

```mermaid
flowchart TD
    A[读取输入] --> B[执行优先队列]
    B --> C[处理边界情况]
    C --> D[输出结果]
```

## 解题流程图

```mermaid
flowchart TD
    A[分析题意和约束] --> B[选择数据结构与算法]
    B --> C[完成核心计算]
    C --> D[按题目格式输出]
```
