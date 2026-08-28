/*
 * 实现原理：
 * 1. 问题本质：多关键字排序问题，根据指定列号对学生记录进行排序
 * 2. 排序规则：
 *    - c=1：按学号递增排序（学号唯一）
 *    - c=2：按姓名非递减字典序排序，姓名相同时按学号递增排序
 *    - c=3：按成绩非递减排序，成绩相同时按学号递增排序
 * 3. 数据结构：使用结构体存储学生记录（学号、姓名、成绩）
 * 4. 算法选择：使用qsort函数进行排序，自定义比较函数实现多级排序
 * 5. 输入输出：使用scanf/printf进行高效的输入输出，适合大规模数据
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_N 100001  // 最大记录条数（10^5 + 1）

// 学生记录结构体
typedef struct Student {
    char id[7];      // 学号，6位数字，加1位结束符
    char name[9];    // 姓名，最多8位字符，加1位结束符
    int score;       // 成绩，0-100的整数
} Student;

Student students[MAX_N];  // 存储所有学生记录
int sort_column;          // 全局变量，存储当前排序的列号

// 比较函数，用于qsort
int cmp(const void *a, const void *b) {
    Student *sa = (Student *)a;
    Student *sb = (Student *)b;
    
    switch (sort_column) {
        case 1:
            // c=1：按学号递增排序
            return strcmp(sa->id, sb->id);
        case 2:
            // c=2：按姓名排序，姓名相同时按学号排序
            {
                int name_cmp = strcmp(sa->name, sb->name);
                if (name_cmp != 0) {
                    return name_cmp;
                }
            }
            // 姓名相同，按学号递增排序
            return strcmp(sa->id, sb->id);
        case 3:
            // c=3：按成绩排序，成绩相同时按学号排序
            if (sa->score != sb->score) {
                return sa->score - sb->score;
            }
            // 成绩相同，按学号递增排序
            return strcmp(sa->id, sb->id);
        default:
            return 0;
    }
}

int main() {
    int n, c;
    // 读取记录条数n和排序列号c
    scanf("%d %d", &n, &c);
    
    sort_column = c;  // 设置全局排序列号
    
    // 读取n条学生记录
    for (int i = 0; i < n; i++) {
        scanf("%s %s %d", students[i].id, students[i].name, &students[i].score);
    }
    
    // 使用qsort进行排序
    qsort(students, n, sizeof(Student), cmp);
    
    // 输出排序后的结果
    for (int i = 0; i < n; i++) {
        printf("%s %s %d\n", students[i].id, students[i].name, students[i].score);
    }
    
    return 0;
}
