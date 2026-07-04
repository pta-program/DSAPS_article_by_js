/**
 * ============================================
 * 7-30 目录树 - C语言实现
 * ============================================
 * 
 * 【题目大意】
 * 在ZIP归档文件中，保留着所有压缩文件和目录的相对路径和名称。
 * 当使用WinZIP等GUI软件打开ZIP归档文件时，可以从这些信息中重建目录的树状结构。
 * 请编写程序实现目录的树状结构的重建工作。
 * 
 * 【实现原理】
 * 1. 数据结构设计：
 *    - 使用DirNode结构体表示目录节点
 *    - 每个节点包含：名称(name)、子目录数组(children)、文件数组(files)
 *    - 使用动态数组存储子节点和文件，按需扩容
 * 
 * 2. 算法流程：
 *    - 读取所有路径，解析每条路径
 *    - 使用'\'作为分隔符，逐级构建目录树
 *    - 区分目录（以'\'结尾）和文件（不以'\'结尾）
 *    - 构建完成后，递归排序所有子目录和文件
 *    - 深度优先遍历输出，使用2空格缩进表示层级
 * 
 * 3. 关键技术点：
 *    - 使用strtok进行路径分割
 *    - 使用qsort进行排序（需要自定义比较函数）
 *    - 递归遍历输出树结构
 *    - 使用动态数组避免固定大小限制
 * 
 * 【时间复杂度】O(N * L + N * logN)
 *    - N为路径数量，L为平均路径深度
 *    - 排序复杂度为O(N * logN)
 * 
 * 【空间复杂度】O(N * L)
 *    - 需要存储所有目录和文件节点
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 270      // 最大名称长度（题目规定不超过260字符，加上换行符等）
#define INITIAL_CAPACITY 10 // 初始容量

/**
 * 目录节点结构体
 * 用于存储目录树中的每个节点
 */
typedef struct DirNode {
    char name[MAX_NAME];              // 节点名称（目录名或"root"）
    struct DirNode **children;        // 子目录指针数组（动态分配）
    char **files;                     // 文件名称指针数组（动态分配）
    int child_count;                  // 子目录数量
    int child_capacity;               // 子目录数组容量
    int file_count;                   // 文件数量
    int file_capacity;                // 文件数组容量
} DirNode;

/**
 * 创建新节点
 * @param name 节点名称
 * @return 新创建的节点指针
 */
DirNode *createNode(char *name) {
    DirNode *node = (DirNode *)malloc(sizeof(DirNode)); // 分配内存
    strncpy(node->name, name, MAX_NAME - 1);  // 复制节点名称（安全拷贝）
    node->name[MAX_NAME - 1] = '\0';          // 确保字符串以null结尾
    node->child_count = 0;                    // 初始化子目录数量为0
    node->child_capacity = INITIAL_CAPACITY;  // 初始容量
    node->children = (DirNode **)malloc(INITIAL_CAPACITY * sizeof(DirNode *)); // 分配子目录数组
    node->file_count = 0;                     // 初始化文件数量为0
    node->file_capacity = INITIAL_CAPACITY;   // 初始容量
    node->files = (char **)malloc(INITIAL_CAPACITY * sizeof(char *)); // 分配文件数组
    return node;
}

/**
 * 添加子目录到父节点
 * @param parent 父节点
 * @param child 子目录节点
 */
void addChild(DirNode *parent, DirNode *child) {
    // 如果容量不足，扩容为原来的2倍
    if (parent->child_count == parent->child_capacity) {
        parent->child_capacity *= 2;
        parent->children = (DirNode **)realloc(parent->children, parent->child_capacity * sizeof(DirNode *));
    }
    parent->children[parent->child_count++] = child; // 添加子目录
}

/**
 * 节点比较函数（用于qsort排序）
 * 按节点名称字典序升序排列
 */
int compareNodes(const void *a, const void *b) {
    DirNode *nodeA = *(DirNode **)a; // 获取第一个节点指针
    DirNode *nodeB = *(DirNode **)b; // 获取第二个节点指针
    return strcmp(nodeA->name, nodeB->name); // 比较节点名称
}

/**
 * 字符串比较函数（用于qsort排序）
 * 按字符串字典序升序排列
 */
int compareStrings(const void *a, const void *b) {
    char *strA = *(char **)a; // 获取第一个字符串指针
    char *strB = *(char **)b; // 获取第二个字符串指针
    return strcmp(strA, strB); // 比较字符串
}

/**
 * 查找或创建子目录
 * 如果子目录已存在，返回已有节点；否则创建新节点
 * @param parent 父节点
 * @param name 子目录名称
 * @return 子目录节点指针
 */
DirNode *findOrCreateChild(DirNode *parent, char *name) {
    // 遍历所有子目录，查找是否已存在
    for (int i = 0; i < parent->child_count; i++) {
        if (strcmp(parent->children[i]->name, name) == 0) {
            return parent->children[i]; // 找到已存在的节点，直接返回
        }
    }
    // 未找到，创建新节点并添加
    DirNode *newChild = createNode(name);
    addChild(parent, newChild);
    return newChild;
}

/**
 * 复制字符串（替代非标准的strdup函数）
 * @param s 源字符串
 * @return 新分配内存的字符串副本
 */
char *dupString(const char *s) {
    char *copy = (char *)malloc(strlen(s) + 1); // 分配内存
    strcpy(copy, s);                            // 复制字符串
    return copy;
}

/**
 * 添加文件到目录节点
 * @param parent 父节点
 * @param filename 文件名称
 */
void addFile(DirNode *parent, char *filename) {
    // 如果容量不足，扩容为原来的2倍
    if (parent->file_count == parent->file_capacity) {
        parent->file_capacity *= 2;
        parent->files = (char **)realloc(parent->files, parent->file_capacity * sizeof(char *));
    }
    parent->files[parent->file_count++] = dupString(filename); // 复制文件名并添加到文件数组
}

/**
 * 解析路径并构建目录树
 * @param root 根节点
 * @param path 路径字符串（如 "a\b\c\" 或 "a\b\file.txt"）
 */
void parseAndBuild(DirNode *root, char *path) {
    DirNode *current = root;    // 从根节点开始
    char *token;                // 用于存储分割后的路径片段
    char pathCopy[MAX_NAME];    // 路径副本（strtok会修改原字符串）
    strcpy(pathCopy, path);     // 复制路径到副本
    
    token = strtok(pathCopy, "\\"); // 使用'\'分割路径，获取第一个片段
    while (token != NULL) {
        char *nextToken = strtok(NULL, "\\"); // 获取下一个片段
        
        if (nextToken == NULL) { // 当前片段是最后一个
            // 判断是目录还是文件
            if (path[strlen(path) - 1] == '\\') {
                // 以'\'结尾，是目录
                current = findOrCreateChild(current, token);
            } else {
                // 不以'\'结尾，是文件
                addFile(current, token);
            }
        } else {
            // 不是最后一个片段，必然是目录
            current = findOrCreateChild(current, token);
        }
        token = nextToken; // 移动到下一个片段
    }
}

/**
 * 递归排序所有子目录和文件
 * @param node 当前节点
 */
void sortChildren(DirNode *node) {
    // 对子目录数组按名称排序
    qsort(node->children, node->child_count, sizeof(DirNode *), compareNodes);
    // 对文件数组按名称排序
    qsort(node->files, node->file_count, sizeof(char *), compareStrings);
    
    // 递归排序所有子目录
    for (int i = 0; i < node->child_count; i++) {
        sortChildren(node->children[i]);
    }
}

/**
 * 递归打印目录树
 * @param node 当前节点
 * @param depth 当前深度（用于控制缩进）
 */
void printTree(DirNode *node, int depth) {
    // 打印当前节点的缩进和名称
    for (int i = 0; i < depth; i++) {
        printf("  "); // 每层缩进2个空格
    }
    printf("%s\n", node->name); // 打印节点名称
    
    // 递归打印所有子目录
    for (int i = 0; i < node->child_count; i++) {
        printTree(node->children[i], depth + 1); // 深度+1
    }
    
    // 打印所有文件
    for (int i = 0; i < node->file_count; i++) {
        for (int j = 0; j < depth + 1; j++) {
            printf("  "); // 文件比父目录多一层缩进
        }
        printf("%s\n", node->files[i]); // 打印文件名
    }
}

/**
 * 主函数
 */
int main() {
    int n;               // 路径数量
    if (scanf("%d", &n) != 1) { // 读取路径数量
        return 0;                // 读取失败直接退出
    }
    getchar();           // 消耗换行符
    
    DirNode *root = createNode("root"); // 创建根节点
    
    // 读取并解析每条路径
    for (int i = 0; i < n; i++) {
        char path[MAX_NAME];
        if (fgets(path, MAX_NAME, stdin) == NULL) { // 读取路径
            break;                                  // 读取失败退出循环
        }
        path[strcspn(path, "\n")] = 0; // 去除换行符
        parseAndBuild(root, path);      // 解析路径并构建目录树
    }
    
    sortChildren(root);    // 排序所有子目录和文件
    printTree(root, 0);   // 从根节点开始打印目录树
    
    return 0;
}
