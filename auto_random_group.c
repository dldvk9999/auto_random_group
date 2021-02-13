#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <windows.h>

#define	NAME_LENGTH 10

/* �迭�� ���� �Լ� */
void shuffle(char **arr, int num) {
	srand(time(NULL)); 
	char *temp = malloc(sizeof(char) * NAME_LENGTH);
	for (int i = 0; i < num-1; i++) {
		int rn = rand() % (num - i) + i;
		strcpy(temp, arr[i]);
		strcpy(arr[i], arr[rn]);
		strcpy(arr[rn], temp);
	}
	free(temp);
}

int main (void) {
	int	count			= 0;
	int	index			= 0;
	int	group_number	= 0;
	int	col				= 0;
	int	row				= 0;
	int	rest			= 0;
	int	line			= 1;
	char buff[NAME_LENGTH];
	char **name;
	
	/* txt ���� �Է� */
	FILE *fp = fopen("name_table.txt","r");
	if (fp == NULL) system("fsutil file createnew name_table.txt 0 > nul");
	
	/* �� �ο��� ���� */
	while (fgets(buff, NAME_LENGTH, fp)) count++;
	
	/* �ʱ� ��� â */
	while (1) {
		printf("\n*******AUTO_RANDOM_GROUP Made_By_P.J.G*******\n\n");
		printf("\t���� name_table �̸� �� : %d ��\n", count);
		printf("\t�� ���� ���� �ұ��? : "); 
		fflush(stdin);
		if	(scanf("%d", &group_number) == 0) { 
			system("cls"); 
			continue; 
		}
		else break;
	}
	
	/* �� ���� ����� ������ ����ȭ */
	row = group_number;
	if (count % group_number) {
		col  = count / group_number + 1;
		rest = count % group_number;
	}
	else col = count / group_number;
	
	/* name 2���� �迭�� �����Ҵ� */
	name = (char **)malloc(sizeof(char *) * count);
	for (int i = 0; i < count; i ++) 
		name[i] = (char *)malloc(sizeof(char) * NAME_LENGTH);
	
	/* fp ó������ ���� �����Ҵ��� 2�����迭�� ����	 */
	fseek(fp, 0, SEEK_SET);
	while (fgets(buff, NAME_LENGTH, fp)) {
		buff[strlen(buff) - 1] = '\0';
		strcpy(name[index], buff);
		index++;
	} 
	fclose(fp);
	
	while(1) {
		
		/* �迭 ���� ���� */
		shuffle(name, count);
		
		/* ��� */
		system("cls");
		printf("�ο� �� : �� %d��, �ִ� �ο� �� : %d��\n\n", count, col);
		col < 10 ? printf("         ") : printf("          ");
		if	(row < 10)	for (int i = 0; i < row; i++) printf("|  %d��   ", i+1);
		else			for (int i = 0; i < row; i++) printf("|  %2d��  ", i+1);
		printf("\n");
		for (int i = 0; i < row+1; i++) printf("----------", i+1);
		printf("\n");
		for (int i = 0; i < count; i++) {
			if		(i % row == 0 && col <  10) printf("   [%d]   ", line++);
			else if	(i % row == 0 && col >= 10) printf("   [%2d]   ", line++);
			printf	("| %s ", name[i]);
			if		(row == 1)						printf("\n");
			else if	(i != 0 && i % row == row - 1)	printf("\n");
		}
		line = 1;
		
		/* ���� ��� â */
		fflush(stdin);
		printf("\n\nRANDOMIZE �Ϸ�!\n");
		printf("�ٽ� �Ϸ��� r, �����Ϸ��� s, �������� �ƹ�Ű �Է� : ");
		char end = getchar();
		
		/* �ٽ� �Ҷ� */
		if (end == 'r' || end == 'R') continue;
		
		/* ���� �Ҷ� */
		else if (end == 's' || end == 'S') {
			system("fsutil file createnew �������.xlsx 0 > nul");
			FILE *fp = fopen("�������.xlsx", "w");
			fprintf(fp, "�ο� �� :\t%d��\t�ִ� �ο� �� :\t%d��\n\n", count, col);
			for (int i = 0; i < row; i++) fprintf(fp, "\t%d��", i+1);
			fprintf(fp, "\n");
			fprintf(fp, "\n");
			for (int i = 0; i < count; i++) {
				if		(i % row == 0) fprintf(fp, "[%d]", line++);
				fprintf	(fp, "\t%s ", name[i]);
				if		(row == 1)						fprintf(fp, "\n");
				else if	(i != 0 && i % row == row - 1)	fprintf(fp, "\n");
			}
			fclose(fp); 
			printf("���� �Ϸ�!\n");
			break;
		}
		
		/* �� �� */
		else break;
	}
	
	free(name);
	system("pause");
	return 0;
}