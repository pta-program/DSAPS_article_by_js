/*
 * 实现原理：
 *   1. 学生姓名编码：姓名由3个大写字母+1位数字组成，共26^3*10=175760种可能。
 *      将姓名映射为整数索引：idx = (s[0]-'A')*6760 + (s[1]-'A')*260 + (s[2]-'A')*10 + (s[3]-'0')
 *   2. 将所有选课记录存储在一个扁平数组中，每条记录包含(学生编码, 课程编号)。
 *      总选课记录数 ≤ 2500*200 = 500000。
 *   3. 对选课记录数组按学生编码排序（次关键字为课程编号），使用qsort。
 *   4. 查询时，对每个学生编码做两次二分查找，确定该生在排序数组中的起止位置，
 *      直接输出对应范围内的课程编号（已按课程编号递增排列）。
 */

#include <stdio.h>   /* 标准输入输出 */
#include <stdlib.h>  /* qsort */

#define MAX_ENROLL 500000  /* 最大选课记录数：2500门课 * 200人/课 */
#define MAX_STU    175760  /* 最大学生编码数：26^3 * 10 */

/* 选课记录结构体 */
typedef struct {
    int stu_id;    /* 学生编码 */
    int course_id; /* 课程编号 */
} Enroll;

Enroll enrolls[MAX_ENROLL]; /* 全局选课记录数组 */
int enroll_cnt = 0;          /* 当前选课记录总数 */

/*
 * 将学生姓名编码为整数索引
 * 姓名格式：3个大写字母 + 1位数字，如 ANN0
 * 编码：26进制字母部分 + 10进制数字部分
 */
int encode(const char *name) {
    return (name[0] - 'A') * 6760 +   /* 第1位字母，权重 26*26*10 = 6760 */
           (name[1] - 'A') * 260 +    /* 第2位字母，权重 26*10 = 260     */
           (name[2] - 'A') * 10 +     /* 第3位字母，权重 10              */
           (name[3] - '0');           /* 第4位数字，权重 1               */
}

/* qsort 比较函数：先按学生编码排序，再按课程编号排序 */
int cmp(const void *a, const void *b) {
    const Enroll *ea = (const Enroll *)a; /* 类型转换 */
    const Enroll *eb = (const Enroll *)b;
    if (ea->stu_id != eb->stu_id)             /* 学生编码不同 */
        return ea->stu_id - eb->stu_id;       /* 按学生编码升序 */
    return ea->course_id - eb->course_id;     /* 按课程编号升序 */
}

int main() {
    int N, K;                          /* N:查询学生数, K:课程总数 */
    scanf("%d %d", &N, &K);            /* 读取N和K */

    /* 读取每门课的选课名单 */
    for (int i = 0; i < K; i++) {      /* 遍历K门课程 */
        int cid, cnt;                  /* cid:课程编号, cnt:选课人数 */
        scanf("%d %d", &cid, &cnt);    /* 读取课程编号和选课人数 */
        for (int j = 0; j < cnt; j++) {/* 读取该课程的学生名单 */
            char name[5];              /* 学生姓名缓冲区（4字符+结束符） */
            scanf("%s", name);         /* 读取一个学生姓名 */
            enrolls[enroll_cnt].stu_id = encode(name);    /* 编码学生姓名 */
            enrolls[enroll_cnt].course_id = cid;           /* 记录课程编号 */
            enroll_cnt++;              /* 选课记录计数加1 */
        }
    }

    /* 对选课记录排序：按学生编码为主键，课程编号为次键 */
    qsort(enrolls, enroll_cnt, sizeof(Enroll), cmp);

    /* 处理每个查询 */
    for (int i = 0; i < N; i++) {      /* 遍历N个查询学生 */
        char name[5];                  /* 学生姓名缓冲区 */
        scanf("%s", name);             /* 读取查询的学生姓名 */
        int sid = encode(name);        /* 编码学生姓名 */

        /* 二分查找第一个stu_id >= sid的位置（下界） */
        int left = 0, right = enroll_cnt;
        while (left < right) {
            int mid = (left + right) / 2;          /* 取中点 */
            if (enrolls[mid].stu_id < sid)         /* 中点学生编码小于目标 */
                left = mid + 1;                    /* 收缩左边界 */
            else
                right = mid;                       /* 收缩右边界 */
        }
        int start = left;              /* 起始位置 */

        /* 二分查找第一个stu_id > sid的位置（上界） */
        left = 0; right = enroll_cnt;
        while (left < right) {
            int mid = (left + right) / 2;          /* 取中点 */
            if (enrolls[mid].stu_id <= sid)        /* 中点学生编码 ≤ 目标 */
                left = mid + 1;                    /* 收缩左边界 */
            else
                right = mid;                       /* 收缩右边界 */
        }
        int end = left;                /* 结束位置（不包含） */

        int cnt = end - start;         /* 该生选课门数 */
        printf("%s %d", name, cnt);    /* 输出姓名和选课门数 */
        for (int j = start; j < end; j++) {        /* 遍历该生的每门课 */
            printf(" %d", enrolls[j].course_id);   /* 输出课程编号 */
        }
        printf("\n");                  /* 换行 */
    }

    return 0;                          /* 程序正常结束 */
}