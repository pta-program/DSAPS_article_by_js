/*
 * ============================================================
 * 实现原理：
 *   1. 读取考点总数 N，遍历每个考点读取该考点的考生数据。
 *   2. 对每个考点内部，按成绩降序、考号升序排序，计算考点内排名
 *      （同分同名次）。
 *   3. 将所有考生合并到一个全局数组中，按成绩降序、考号升序排序，
 *      计算最终排名（同分同名次）。
 *   4. 输出考生总数，然后按最终排名顺序输出每个考生的考号、最终排名、
 *      考点编号、考点内排名。
 *
 * 复杂度：O(M log M)，其中 M 为考生总数（最多 100*300 = 30000）。
 * ============================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 最大考生总数：N <= 100, K <= 300，最多 30000 名考生 */
#define MAX_STUDENTS 30000

/* 考生信息结构体 */
typedef struct {
    char id[14];        /* 考号，13位数字 + 1位结束符 */
    int score;          /* 得分 */
    int site_id;        /* 考点编号（从 1 开始） */
    int site_rank;      /* 在考点内的排名 */
    int final_rank;     /* 最终排名 */
} Student;

/* 全局比较函数：按成绩降序，成绩相同按考号升序 */
int cmp(const void *a, const void *b) {
    const Student *s1 = (const Student *)a;
    const Student *s2 = (const Student *)b;
    if (s1->score != s2->score) {
        return s2->score - s1->score;  /* 成绩高的在前 */
    }
    return strcmp(s1->id, s2->id);     /* 成绩相同，考号小的在前 */
}

int main() {
    Student students[MAX_STUDENTS];    /* 全局考生数组 */
    int total = 0;                     /* 考生总数 */
    int N;                             /* 考点总数 */

    /* 读取考点总数 */
    scanf("%d", &N);

    /* 遍历每个考点 */
    for (int site = 1; site <= N; site++) {
        int K;  /* 当前考点考生数 */
        scanf("%d", &K);

        int start = total;  /* 当前考点考生在全局数组中的起始位置 */

        /* 读取当前考点的 K 名考生 */
        for (int i = 0; i < K; i++) {
            scanf("%s %d", students[total].id, &students[total].score);
            students[total].site_id = site;
            total++;
        }

        /* 对当前考点的考生进行排序（按成绩降序、考号升序） */
        qsort(students + start, K, sizeof(Student), cmp);

        /* 计算考点内排名（同分同名次） */
        for (int i = 0; i < K; i++) {
            int idx = start + i;
            if (i == 0) {
                students[idx].site_rank = 1;  /* 第一名 */
            } else if (students[idx].score == students[idx - 1].score) {
                students[idx].site_rank = students[idx - 1].site_rank;  /* 同分同名次 */
            } else {
                students[idx].site_rank = i + 1;  /* 正常排名 = 位置 + 1 */
            }
        }
    }

    /* 对所有考生进行全局排序（按成绩降序、考号升序） */
    qsort(students, total, sizeof(Student), cmp);

    /* 计算最终排名（同分同名次） */
    for (int i = 0; i < total; i++) {
        if (i == 0) {
            students[i].final_rank = 1;  /* 第一名 */
        } else if (students[i].score == students[i - 1].score) {
            students[i].final_rank = students[i - 1].final_rank;  /* 同分同名次 */
        } else {
            students[i].final_rank = i + 1;  /* 正常排名 = 位置 + 1 */
        }
    }

    /* 输出结果 */
    printf("%d\n", total);  /* 考生总数 */
    for (int i = 0; i < total; i++) {
        printf("%s %d %d %d\n",
               students[i].id,
               students[i].final_rank,
               students[i].site_id,
               students[i].site_rank);
    }

    return 0;
}