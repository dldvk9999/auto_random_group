#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <windows.h>

#define	NAME_LENGTH 10

/* 배열을 섞는 함수 */
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
	
	/* txt 파일 입력 */
	FILE *fp = fopen("name_table.txt","r");
	if (fp == NULL) system("fsutil file createnew name_table.txt 0 > nul");
	
	/* 총 인원수 세기 */
	while (fgets(buff, NAME_LENGTH, fp)) count++;
	
	/* 초기 출력 창 */
	while (1) {
		printf("\n*******AUTO_RANDOM_GROUP Made_By_P.J.G*******\n\n");
		printf("\t현재 name_table 이름 수 : %d 명\n", count);
		printf("\t몇 개의 조로 할까요? : "); 
		fflush(stdin);
		if	(scanf("%d", &group_number) == 0) { 
			system("cls"); 
			continue; 
		}
		else break;
	}
	
	/* 한 조에 몇명을 넣을지 최적화 */
	row = group_number;
	if (count % group_number) {
		col  = count / group_number + 1;
		rest = count % group_number;
	}
	else col = count / group_number;
	
	/* name 2차원 배열을 동적할당 */
	name = (char **)malloc(sizeof(char *) * count);
	for (int i = 0; i < count; i ++) 
		name[i] = (char *)malloc(sizeof(char) * NAME_LENGTH);
	
	/* fp 처음으로 가서 동적할당한 2차원배열에 대입	 */
	fseek(fp, 0, SEEK_SET);
	while (fgets(buff, NAME_LENGTH, fp)) {
		buff[strlen(buff) - 1] = '\0';
		strcpy(name[index], buff);
		index++;
	} 
	fclose(fp);
	
	while(1) {
		
		/* 배열 랜덤 셔플 */
		shuffle(name, count);
		
		/* 출력 */
		system("cls");
		printf("인원 수 : 총 %d명, 최대 인원 수 : %d명\n\n", count, col);
		col < 10 ? printf("         ") : printf("          ");
		if	(row < 10)	for (int i = 0; i < row; i++) printf("|  %d조   ", i+1);
		else			for (int i = 0; i < row; i++) printf("|  %2d조  ", i+1);
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
		
		/* 최종 출력 창 */
		fflush(stdin);
		printf("\n\nRANDOMIZE 완료!\n");
		printf("다시 하려면 r, 저장하려면 s, 끝내려면 아무키 입력 : ");
		char end = getchar();
		
		/* 다시 할때 */
		if (end == 'r' || end == 'R') continue;
		
		/* 저장 할때 */
		else if (end == 's' || end == 'S') {
			system("fsutil file createnew 조편성결과.xlsx 0 > nul");
			FILE *fp = fopen("조편성결과.xlsx", "w");
			fprintf(fp, "인원 수 :\t%d명\t최대 인원 수 :\t%d명\n\n", count, col);
			for (int i = 0; i < row; i++) fprintf(fp, "\t%d조", i+1);
			fprintf(fp, "\n");
			fprintf(fp, "\n");
			for (int i = 0; i < count; i++) {
				if		(i % row == 0) fprintf(fp, "[%d]", line++);
				fprintf	(fp, "\t%s ", name[i]);
				if		(row == 1)						fprintf(fp, "\n");
				else if	(i != 0 && i % row == row - 1)	fprintf(fp, "\n");
			}
			fclose(fp); 
			printf("저장 완료!\n");
			break;
		}
		
		/* 그 외 */
		else break;
	}
	
	free(name);
	system("pause");
	return 0;
}