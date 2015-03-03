#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<conio.h>
#include<string.h>

#define M 3
//#define FORMAT "%6d\t%l5s\t%.2f\t%.2f\t%.2f\t%.2f\t%d\n"
#define FORMAT "|%5d|%9s|%5.2f|%5.2f|%5.2f|%6.2f|%6d|\n"
#define DATA  p->snum,p->name,p->score[0].sc,p->score[1].sc,p->score[2].sc,p->sum,p->rank

int flag = 0;

//定义选课先决条件结点[单链表]cnode
typedef struct cnode{
	int num;
	struct cnode *next;
}Cnode;//定义结点数据结构


//定义课程项目
typedef struct{
	int cnum;
	char cname[20];
	int credit;
	int indegree;
	Cnode *first;
}Cour;

typedef struct{
	Cour *cp;
	float sc;
}Score;

typedef Cour Courl[M];
typedef struct{
	Courl cr;
	int n, e;
}Course;

//定义表示学生结点
typedef struct snode{
	int snum;
	char name[20];
	Score score[M];
	float sum;
	float average;
	int rank;
	struct snode *next;
}Student;


//学生管理系统
Student *init_s();

void input_g(Student *, Cour *);			/*成绩录入*/
void ave_g(Student*);			/*成绩总和计算*/
void sort_g(Student*);			/*成绩排序，同时保存排序文件*/
void print_g(Student*);			/*成绩输出*/
void filt_g(Student*);			/*成绩分类搜索*/



void init_c(Course *g);