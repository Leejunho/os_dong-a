#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int n, m; 
int isSafe(int alloc[50][50], int max[50][50], int available[50], int buffer[50], int pNumber);
void print(FILE *output_fp, int available[50]);
typedef struct Que {
	int instance[50]; 
	int pNum; 
	struct Que *next;
}Que;

void delQue(Que *pre_Q, Que *del_Q) {
	pre_Q->next = del_Q->next;
	free(del_Q);
	del_Q = NULL;
}
void addQue(Que *Q, int arr[50], int pNum) { 

	int i;
	Que *p = Q;
	Que *NewQue = (Que*)malloc(sizeof(Que));
	NewQue->pNum = pNum;
	for (i = 0; i<m; i++) {
		NewQue->instance[i] = arr[i];
	}
	NewQue->next = NULL;

	while (p->next != NULL)p = p->next;

	p->next = NewQue;
}

int main()
{
	FILE *input_fp, *output_fp;

	if ((input_fp = fopen("banker.inp", "rt")) == NULL)
	{
		fprintf(stderr, "can't open %s\n", "banker.inp");
	}
	if ((output_fp = fopen("banker.out", "wt")) == NULL)
	{
		fprintf(stderr, "can't open %s\n", "banker.out");
	}

	int alloc[50][50] = { 0, };
	int max[50][50] = { 0, };
	int available[50] = { 0, };
	int buffer[50] = { 0, };

	int i, j;
	char charTemp = '\0';
	int pNumber;
	int safe_bool = 0;
	char check;



	fscanf(input_fp, "%d %d", &n, &m);
	for (j = 0; j < m; j++) {
		fscanf(input_fp, "%d%c", &available[j], &charTemp);
	}
	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			fscanf(input_fp, "%d%c", &max[i][j], &charTemp);
		}
	}
	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			fscanf(input_fp, "%d%c", &alloc[i][j], &charTemp);
			available[j] -= alloc[i][j];
		}
	}

	char command[10];
	char A[] = "request";
	char B[] = "release";
	char C[] = "quit";
	Que *Q = (Que*)malloc(sizeof(Que));
	Q->next = NULL;
	Q->pNum = -1;
	Que *pre_Q, *now_Q;
	while (1) {
		fscanf(input_fp, "%s %d", &command, &pNumber);
		if (strcmp(command, A) == 0) {//요청
			for (i = 0; i < m; i++) {
				fscanf(input_fp, "%d%c", &buffer[i], &charTemp);
			}
			addQue(Q, buffer, pNumber);
		}
		else if (strcmp(command, B) == 0) { //반환
			for (i = 0; i < m; i++) {
				fscanf(input_fp, "%d%c", &buffer[i], &charTemp);
				available[i] = available[i] + buffer[i];
				alloc[pNumber][i] = alloc[pNumber][i] - buffer[i];
			}

		}
		else if (strcmp(command, C) == 0) //quit 종료
			break;


		pre_Q = Q;
		now_Q = Q->next;
		while (now_Q) {
			safe_bool = 0;
			for (i = 0; i<m; i++) {
				if (now_Q->instance[i] > available[i]) {
					safe_bool = 1;
					break;
				}
			}
			if (!safe_bool) {
				safe_bool = isSafe(alloc, max, available, now_Q->instance, now_Q->pNum);
			}

			if (!safe_bool) {
				for (i = 0; i<m; i++) {
					alloc[now_Q->pNum][i] += now_Q->instance[i];
					available[i] = available[i] - now_Q->instance[i];
				}
				delQue(pre_Q, now_Q);
				now_Q = pre_Q->next;
			}
			else {
				pre_Q = now_Q;
				now_Q = now_Q->next;
			}
		}
		print(output_fp, available);
	}
	fclose(input_fp);
	fclose(output_fp);
	return 0;
}





int isSafe(int alloc[50][50], int max[50][50], int available[50], int buffer[50], int pNumber) {
	int i, j, k;
	int check = 0; 
	int alloctemp[50][50];
	int maxtemp[50][50];
	int availabletemp[50];
	int fCount = 0;
	int flag[50] = { 0, }; 

	for (j = 0; j<m; j++) {
		availabletemp[j] = available[j];
	}
	for (i = 0; i<n; i++) {
		for (j = 0; j<m; j++) {
			alloctemp[i][j] = alloc[i][j];
			maxtemp[i][j] = max[i][j];
		}
	}
	for (i = 0; i<m; i++) {
		if (buffer[i]>(maxtemp[pNumber][i] - alloctemp[pNumber][i]))return 1;
		alloctemp[pNumber][i] += buffer[i];
		availabletemp[i] -= buffer[i];
	}
	for (i = 0; i<n; i++) {
		for (j = 0; j<m; j++) {
			if (alloctemp[i][j] != maxtemp[i][j]) {
				break;
			}
		}
		if (j == m) {
			flag[i] = 1;
			fCount++;
			for (j = 0; j<m; j++) {
				availabletemp[j] += alloctemp[i][j];
				alloctemp[i][j] = 0;
				maxtemp[i][j] = 0;
			}
		}
	}

	for (k = 0; k<(n - fCount); k++) {
		check = 0;
		for (i = 0; i<n; i++) {
			for (j = 0; j<m && !flag[i]; j++) {
				if ((maxtemp[i][j] - alloctemp[i][j]) > availabletemp[j]) 
					break;
				if (j == m - 1) { 
					for (j = 0; j<m; j++) {
						availabletemp[j] = availabletemp[j] + alloctemp[i][j]; 
						maxtemp[i][j] = 0;
						alloctemp[i][j] = 0; 
						check = 1;
						flag[i] = 1;
					}
				}
			}
			if (check) break;
		}
		if (!check) return 1; 
	}
	return 0; //safe
}
void print(FILE *output_fp, int available[50]) {
	int i;
	for (i = 0; i < m; i++) {
		fprintf(output_fp, "%d", available[i]);
		if (i != m - 1) fprintf(output_fp, " ");
	}
	fprintf(output_fp, "\n");
}
