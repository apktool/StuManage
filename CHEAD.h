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

//����ѡ���Ⱦ��������[������]cnode
typedef struct cnode{
	int num;
	struct cnode *next;
}Cnode;//���������ݽṹ


//����γ���Ŀ
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

//�����ʾѧ�����
typedef struct snode{
	int snum;
	char name[20];
	Score score[M];
	float sum;
	float average;
	int rank;
	struct snode *next;
}Student;


//ѧ������ϵͳ
Student *init_s();

void input_g(Student *, Cour *);			/*�ɼ�¼��*/
void ave_g(Student*);			/*�ɼ��ܺͼ���*/
void sort_g(Student*);			/*�ɼ�����ͬʱ���������ļ�*/
void print_g(Student*);			/*�ɼ����*/
void filt_g(Student*);			/*�ɼ���������*/



void init_c(Course *g);