#include"CFUN.h"


int main(int argc, char *argv[])
{
	char *m1[] = { "----Student system----",
		"1. Init list",
		"2. Scorce management",
		"3. Search record",
		"4. Append a record to list",
		"5. Modefiy a record to list",
		"6. Delete a record form list",
		"7. Save the file",
		"0. exit" 
	};
	char *m2[] = { "----Score system----",
		"1. Init SCORE list",
		"2. Average of each subject",
		"3. Sort and order",
		"4. filter sore",
		"5. Display number and score",
		"0. return"
	};
	char *m3[] = { "----Course system----",
		"1. Init COURSE list",
		"2. Sort of course",
		"3. Plan",
		"0. return"
	};

	int i;
	int s1, s2, s3;
	char ch;
	Course hc;
	Student *heads = NULL;
	do{
		system("CLS");
		s1 = print();
		if (s1 == 1){
			s2 = menu(m1, 9);
			switch (s2){
			case 0:
				if (flag == 1){
					printf_s("\nWhether save the modified record to file?(y/n): ");
					scanf_s("%c", &ch);
					if (ch == 'y' || ch == 'Y'){
						save_s(heads);
					}
				}
				printf_s("The student system quit.\n");
				break;
			case 1:
				heads = init_s(); break;
			case 2:
				do
				{
					system("CLS");
					s3 = menu(m2, 7);
					if (s3 == 0){
						break;
					}
					switch (s3){
					case 1:
						input_g(heads, hc.cr);break;
					case 2:
						ave_g(heads); break;
					case 3:
						sort_g(heads); break;
					case 4:
						filt_g(heads); break;
					case 5:
						print_g(heads); break;
					}
				} while (1);
				break;
			case 3:
				sear_s(heads); break;
			case 4:
				heads = appe_s(heads); break;
			case 5:
				heads = modi_s(heads); break;
			case 6:
				heads = dele_s(heads); break;
			case 7:
				save_s(heads); break;
			}
		}

		else if (s1 == 2){
			do{
				system("CLS");
				s2 = menu(m3, 5);
				if (s2 == 0){
					break;
				}
				switch (s2){
				case 1:init_c(&hc); break;
				case 2:sort_c(&hc); break;
				case 3:plan_c(&hc); break;
				}
			} while (1);
		}
		else if (s1 == 0) {
			break;
		}
	} while (1);

	return 0;
}