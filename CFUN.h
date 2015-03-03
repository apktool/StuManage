#include"CHEAD.h"

int print()
{
	int n;
	printf("\n");
	system("CLS");
	printf("\n-------------------------------------------------------");
	printf("\n\t\tWELCOME TO ACADEMIC SYSTEM");
	printf("\n                1. Student management");
	printf("\n                2. Course management");
	printf("\n                0. Exit management");
	printf("\n-------------------------------------------------------");
	printf("\t\nNow please select 1,2 or 0: ");
	scanf_s("%d", &n);
	getchar();
	return n;
}

int menu(char *m[], int n){
	int select;
	system("CLS");
	for (int i = 0; i < n; i++){
		printf_s("%s\n", m[i]);
	}
	do{
		printf_s("\n\tEnter your choice ( 0 - %d ) to continue ...", n - 2);
		scanf_s("%d", &select);
		getchar();
	} while (select<0 || select>n);
	return select;
}




//学生管理系统的实现
Student *init_s(){
	Student *head, *p, *last;
	Student s;
	char c;
	FILE *fp;
	errno_t err;
	char fname[20];
	int i;

	printf_s("Do you creat new file (Y/N)? :");
	c = getchar();
	getchar();
	if (c == 'Y' || c == 'y'){
		printf_s("Input new student filename: ");
		gets_s(fname, 20);
		err = fopen_s(&fp, fname, "wb");
		if (err){
			printf("Can't Open file.\n");
			return NULL;
		}
		do{
			printf_s("Input the student number: ");
			scanf_s("%d", &s.snum);
			getchar();
			if (s.snum != -1){
				printf_s("Input the name: ");
				gets_s(s.name, 20);
				for (i = 0; i < M; i++){
					s.score[i].cp = NULL;
					s.score[i].sc = 0;
				}
				s.sum = 0;
				s.rank = -1;
				s.next = NULL;
				fwrite(&s, sizeof(Student), 1, fp);
			}
			else{
				break;
			}
		} while (1);
		fclose(fp);
	}
	head = (Student *)malloc(sizeof(Student));
	head->next = NULL;
	last = head;
	printf_s("Open the student file, input the filename: ");
	gets_s(fname, 20);
	err = fopen_s(&fp, fname, "rb");
	if (err){
		printf_s("\nCan not open file!\n");
		return NULL;
	}

	while (!feof(fp)){
		p = (Student*)malloc(sizeof(Student));
		if (fread(p, sizeof(Student), 1, fp) == 1){
			p->next = NULL;
			last->next = p;
			last = p;
		}
	}
	fclose(fp);
	last->next = NULL;
	return head;
}

//学生记录的保存
void save_s(Student *head)
{
	FILE *fp;
	errno_t err;
	Student *p;
	char bname[20];
	printf_s("Input the save file name: ");
	gets_s(bname, 20);
	err = fopen_s(&fp, bname, "wb");
	if (err){
		printf_s("\nOpen file error!\n");
		return;
	}
	p = head->next;
	while (p){
		fwrite(p, sizeof(Student), 1, fp);
		p = p->next;
	}
	fclose(fp);
}

//成绩录入
void input_g(Student *head, Cour *hg)
{
	Student *p;
	float x1, x2, x3;
	p = head->next;
	while (p){
		printf_s("Input the first term score: ");
		scanf_s("%f%f%f", &x1, &x2, &x3);
		p->score[0].sc = x1;
		p->score[1].sc = x2;
		p->score[2].sc = x3;
		p->sum = x1 + x2 + x3;
		p->score[0].cp = hg;
		p->score[1].cp = hg + 1;
		p->score[2].cp = hg + 2;
		p = p->next;
	}
	_getch();
}

//计算某一科的平均值
void ave_g(Student *head)
{
	Student *p, *q;
	int i, n = 0;
	float sa = 0;
	system("CLS");
	q = head->next;
	for (i = 0; i < M; i++){
		sa = 0;
		n = 0;
		p = head->next;
		while (p){
			n++;
			sa += p->score[i].sc;
			p = p->next;
		}
		sa = sa / n;
		printf_s("%s average %.2f\n", q->score[i].cp->cname, 20, sa);
	}
	_getch();
}

//成绩排序
void sort_g(Student *head)
{
	Student *p, *q, *r, *u;
	int re = 1;
	p = head->next;
	head->next = NULL;
	while (p){
		r = head;
		q = head->next;
		while (q&&q->sum >= p->sum){
			r = q;
			q = q->next;
		}
		u = p->next;
		p->next = r->next;
		r->next = p;
		p = u;
	}
	p = head->next;
	while (p){
		p->rank = re++;
		p = p->next;
	}
	print_g(head);
}

void print_g(Student *head)
{
	system("CLS");
	Student *p;
	p = head->next;
	printf_s("\n\n------------------------STUDENT-----------------------------");
	printf_s("\n| No  | name    | sc1 | sc2 | sc3 |  sum | rank |");
	printf_s("\n|-----|---------|-----|-----|-----|------|------|\n");
	while (p){
		printf_s(FORMAT, DATA);
		p = p->next;
	}
	printf_s("\n-----------------------------END--------------------------------\n");
	getchar();
}

//学生成绩的筛选
void filt_g(Student *head)
{
	int select;
	char *m4[] = { "----Display----",
		"1. 80 =< Record <= 100",
		"2. 60 =< Record <= 80",
		"3. No pass",
		"0. Return"
	};
	while (1){
		system("CLS");
		select = menu(m4, 5);
		if (select == 0){
			break;
		}
		void class1(Student *);
		void class2(Student *);
		void class3(Student *);

		switch (select){
		case 1:class1(head); break;
		case 2:class2(head); break;
		case 3:class3(head); break;
		}
	}
}

void class1(Student *h)
{
	Student *p;
	int i;
	system("CLS");
	p = h->next;
	printf_s("|--number--|--name-----|----subjuec----- -|---score----|\n");
	while (p != NULL){
		for (i = 0; i<M; i++){
			if (p->score[i].sc >= 80){
				printf_s("|%4d|%15s|%15s|%.2f\n\n", p->snum, p->name, p->score[i].cp->cname, p->score[i].sc);
			}
		}
		p = p->next;
	}
	printf_s("\n\npress any key...");
	_getch();
}

void class2(Student *h)
{
	Student *p;
	int i;
	system("CLS");
	p = h->next;
	printf("|--number--|--name-----|----subjuec-------|---score----|\n");
	while (p != NULL){
		for (i = 0; i<M; i++){
			if (p->score[i].sc >= 60 && p->score[i].sc <= 79){
				printf_s("|%4d|%15s|%15s|%.2f\n\n", p->snum, p->name, p->score[i].cp->cname, p->score[i].sc);
			}
		}
		p = p->next;
	}
	printf_s("\n\npress any key...");
	_getch();
}

void  class3(Student *h){
	Student *p;
	int i;
	system("CLS");
	p = h->next;
	printf("|--number--|----------name---------|--------subjuec-------- -|-------score-------|\n");
	while (p != NULL)    {
		for (i = 0; i<M; i++) {
			if (p->score[i].sc<60)
				printf_s("|%4d|%15s|%15s|%.2f\n\n", p->snum, p->name, p->score[i].cp->cname, p->score[i].sc);
		}
		p = p->next;
	}
	printf("\n\npress any key...");
	_getch();
}

int sear_s(Student *head){
	int select;
	Student *p;
	int num;
	char str[30];
	int f = 0;
	system("CLS");
	if (!head->next){
		printf_s("\nThe student not exist!\n");
		getchar();
		return NULL;
	}
	printf_s("\n1. Search by student number.");
	printf_s("\n2. Search by student name.");
	printf_s("\nPlease input the num: ");
	scanf_s("%d", &select);
	getchar();
	switch (select){
	case 1:
		printf_s("Input the student number: ");
		scanf_s("%d", &num);
		p = head->next;
		while (p){
			if (p->snum == num){
				printf_s("\n");
				printf_s("\n\n----------------INFORMATION---------------------");
				printf_s("\n| No  | name    | sc1 | sc2 | sc3 |  sum | rank |");
				printf_s("\n|-----|---------|-----|-----|-----|------|------|\n");
				printf_s(FORMAT, DATA);
				f = 1;
				break;
			}
			p = p->next;
		}
		getchar();
		break;
	case 2:
		printf_s("Input the student name: ");
		gets_s(str);
		p = head->next;
		while (p){
			if (strcmp(p->name, str) == 0){
				f = 1;
				printf_s("\n\n----------------INFORMATION---------------------");
				printf_s("\n| No  | name    | sc1 | sc2 | sc3 |  sum | rank |");
				printf_s("\n|-----|---------|-----|-----|-----|------|------|\n");
				printf_s(FORMAT, DATA);
			}
			p = p->next;
		}
		break;
	}
	_getch();
	return f;
}

//添加学生记录
Student *appe_s(Student *head)
{
	Student *p, *r;
	int num;
	float x1, x2, x3;
	system("CLS");
	r = head;
	while (r->next){
		r = r->next;
	}
	while (1){
		printf_s("Input the student num: ");
		p = (Student *)malloc(sizeof(Student));
		scanf_s("%d", &p->snum);
		getchar();
		int check(Student *, int);
		while (check(head, p->snum) && p->snum != -1){
			printf_s("The student already exist, input again: ");
			scanf_s("%d", &p->snum);
			getchar();
		}
		if (p->snum == -1){
			printf_s("The insert is over, press any key ...\n");
			getchar();
			break;
		}
		else{
			printf_s("Input the student name: ");
			gets_s(p->name);
			printf_s("Input the first term score: ");
			scanf_s("%f%f%f", &x1, &x2, &x3);
			p->score[0].sc = x1;
			p->score[1].sc = x2;
			p->score[2].sc = x3;
			p->sum = x1 + x2 + x3;
			p->rank = -1;
			p->next = NULL;
			r->next = p;
			r = p;
		}
	}
	flag = 1;
	system("CLS");
	print_g(head);
	return head;
}

int check(Student *head, int num)
{
	Student *p;
	p = head->next;
	while (p&&p->snum != num){
		p = p->next;
	}
	if (p){
		return 1;
	}
	else{
		return 0;
	}
}

//修改学生记录
Student *modi_s(Student *head){
	Student *p;
	int num;
	float x1, x2, x3;
	system("CLS");
	printf_s("Modify student recorder ...\n");
	printf_s("Input the modify student number: ");
	scanf_s("%d", &num);
	getchar();
	p = head->next;
	while (p&&p->snum != num){
		p = p->next;
	}
	if (p){
		printf_s("Input the modify student name: ");
		gets_s(p->name);
		printf_s("Input the modify first term score: ");
		scanf_s("%f%f%f", &x1, &x2, &x3);
		p->score[0].sc = x1;
		p->score[1].sc = x2;
		p->score[2].sc = x3;
		p->sum = x1 + x2 + x3;
		print_g(head);
		flag = 1;
		getchar();
	}
	else{
		printf_s("No find record. \n");
	}
	return head;
}

//删除学生记录
Student *dele_s(Student *head){
	int select;
	Student *p, *r;
	char str[30];
	int num;
	system("CLS");
	if (!head->next){
		printf_s("\nNo student record!\n");
		return NULL;
	}
	printf_s("\n1. Delete by number.");
	printf_s("\n2. Delete by name.");
	printf_s("\n Please input the num: ");
	scanf_s("%d", &select);
	getchar();
	if (select == 1){
		printf_s("\nInput the student num: ");
		scanf_s("%d", &num);
		r = head;
		p = head->next;
		while (p&&p->snum != num){
			r = p;
			p = p->next;
		}
		if (p){
			r->next = p->next;
			flag = 1;
			free(p);
			printf_s("\nDelete success!\n");
			getchar();
		}
		else{
			printf_s("\nNo find!\n");
			getchar();
		}
	}
	else if (select == 2){
		printf_s("\nInput the book name: ");
		gets_s(str);
		r = head;
		p = head->next;
		while (p&&strcmp(p->name, str) != 0){
			r = p;
			p = p->next;
		}
		if (p){
			r->next = p->next;
			flag = 1;
			free(p);
			printf_s("\nDelete success!\n");
			getchar();
		}
		else{
			printf_s("\nNo find.\n");
		}
	}
	print_g(head);
	return head;
}

//初始化课程表【采用有向图算法，使用链式存贮】
void init_c(Course *g){
	char fname[20];
	int i, j, k;
	Cnode *s = NULL;


	printf_s("\ninput the course information. ");
	printf_s("\nNo. Course. Credit: \n");
	g->n = M;
	for (i = 0; i < g->n; i++){
		scanf_s("%d", &(g->cr[i].cnum));
		scanf_s("%s", g->cr[i].cname, 20);
		scanf_s("%d", &g->cr[i].credit);
		g->cr[i].indegree = 0;
		g->cr[i].first = NULL;
	}

	printf("\nInput number of course information: ");
	scanf_s("%d", &g->e);
	getchar();

	printf("\nInput information of course: ");
	for (k = 0; k < g->e; k++){
		scanf_s("%d%d", &i, &j);
		getchar();
		s = (Cnode *)malloc(sizeof(Cnode));
		s->num = j;
		s->next = g->cr[i].first;
		g->cr[i].first = s;
	}

	printf("Save the course to file, open the file.\n");
	gets_s(fname, 20);
	FILE *fp;
	errno_t err;
	err = fopen_s(&fp, fname, "wb");
	if (err){
		printf_s("The file can not open.\n");
		exit(0);
	}
	fwrite(g, sizeof(Course), 1, fp);
	fclose(fp);
}


//使用拓扑排序定义每学期课程顺序的问题
int topsort[M];
int ts = 0;
void sort_c(Course *g)
{
	int i, j, top = -1;
	Cnode *p;
	system("CLS");
	for (i = 0; i < g->n; i++){
		p = g->cr[i].first;
		while (p){
			g->cr[i].indegree++;
			p = p->next;
		}
	}
	for (i = 0; i < g->n; i++){
		if (g->cr[i].indegree == 0){
			g->cr[i].indegree = top;
			top = i;
		}
	}
	printf_s("The course arrange :\n");
	while (top != -1){
		j = top;
		top = g->cr[top].indegree;
		printf_s("%s\n", g->cr[i].cname);
		topsort[ts++] = j;
		p = g->cr[j].first;
		while (p){
			i = p->num;
			g->cr[i].indegree--;
			if (g->cr[i].indegree == 0){
				g->cr[i].indegree = top;
				top = i;
			}
			p = p->next;
		}
	}
	getchar();
}

void plan_c(Course *g)
{
	int s = 0;
	char fname[20];
	FILE *fp;
	errno_t err;
	int i, j, k = 0;
	system("CLS");
	printf_s("Open the course, input the filename \n");
	gets_s(fname);
	err = fopen_s(&fp, fname, "rb");
	if (err){
		printf_s("The file can not open!\n");
		return;
	}
	fread(g, sizeof(Course), 1, fp);
	sort_c(g);
	for (i = 0; i < g->n; i++){
		s += g->cr[i].credit;
	}
	s = s / 4;
	j = 1;
	for (i = 0; i < g->n; i++){
		k + g->cr[topsort[i]].credit;
		if (k <= s){
			printf_s("The %d term course: ", j);
			printf_s("\n%d\t%s", g->cr[topsort[i]].cnum, g->cr[topsort[i]].cname);
		}
		else{
			j++;
			k = 0;
		}
	}
	getchar();
	fclose(fp);
}