#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
int service;
int ref[100][2];
typedef struct Que {
	int rTime;
	int trackNum;
	struct Que *next;
}Que;
void delQue(Que *pre_Q, Que *del_Q) {
	pre_Q->next = del_Q->next;
	free(del_Q);
	del_Q = NULL;
}
void addQue(Que *Q, int rTime, int trackNum) {

	int i;
	Que *p = Q;
	Que *NewQue = (Que*)malloc(sizeof(Que));
	NewQue->rTime = rTime;
	NewQue->trackNum = trackNum;
	NewQue->next = NULL;

	while (p->next != NULL)p = p->next;

	p->next = NewQue;
}
void FCFS(FILE *output_fp, Que *Q) {
	int time = 0, tempTime = 0;
	int index = 0;//헤드 현재위치
	int len = 0;//헤드 이동거리
	int r;//요청시간
	int k;//트랙번호
	Que *pre_Q, *now_Q;
	pre_Q = Q;
	now_Q = Q->next;

	while (now_Q) {
		if (now_Q->rTime <= time) {
			len = index - now_Q->trackNum;
			index = now_Q->trackNum;
			time = time + service + abs(len);

			delQue(pre_Q, now_Q);
			now_Q = pre_Q->next;
		}
		else if (now_Q->rTime > time) {
			time = now_Q->rTime;
		}
	}
	fprintf(output_fp, "%d %d", time, index);
}
void SSTF(FILE *output_fp, int max) {
	int time = 0, tempTime = 0;
	int index = 0;//헤드 현재위치
	int len = 0;//헤드 이동거리
	int count = 0;
	int temp_track = 0;
	int  i=0,j;
	printf("%d service\n", service);
	while (1) {
		if (ref[i][0] <= time && ref[i][1]!= -1) {
			for (j = i; j<max; j++) {
				if (abs(ref[i][1]-index) > abs(ref[j][1]-index) && ref[i][1] != -1 && ref[j][0] <= time) {
					temp_track = ref[i][1];
					ref[i][1] = ref[j][1];
					ref[j][1] = temp_track;
				}
			}
			len = index - ref[i][1];
			index = ref[i][1];
			time = time + service + abs(len);
			printf("%d %d |%d\n", time, index, abs(len));
			ref[i][1] = -1;
			count++;
			i++;
		}
		else if (ref[i][0] > time && ref[i][1] != -1) {
			for (j = i; j < max; j++) {
				if (ref[i][0] > ref[j][0] && ref[j][1] != -1) {
					temp_track = ref[i][1];
					ref[i][1] = ref[j][1];
					ref[j][1] = temp_track;

					tempTime = ref[i][0];
					ref[i][0] = ref[j][0];
					ref[j][0] = tempTime;
				}
			}
			
			time = ref[i][0];
		}
		if (count == max)break;
	}

	fprintf(output_fp, "%d %d", time, index);
}
void LOOK(FILE *output_fp, int max) {
	int time = 0, tempTime = 0;
	int index = 0;//헤드 현재위치
	int len = 0;//헤드 이동거리
	int count = 0;
	int temp_track = 0;
	int  i = 0, j;
	printf("%d service\n", service);
	while (1) {
		if (ref[i][0] <= time && ref[i][1] != -1) {
			for (j = i; j<max; j++) {
				if (abs(ref[i][1] - index) > abs(ref[j][1] - index) && ref[i][1] != -1 && ref[j][0] <= time) {
					temp_track = ref[i][1];
					ref[i][1] = ref[j][1];
					ref[j][1] = temp_track;
				}
			}
			len = index - ref[i][1];
			index = ref[i][1];
			time = time + service + abs(len);
			printf("%d %d |%d\n", time, index, abs(len));
			ref[i][1] = -1;
			count++;
			i++;
		}
		else if (ref[i][0] > time && ref[i][1] != -1) {
			for (j = i; j < max; j++) {
				if (ref[i][0] > ref[j][0] && ref[j][1] != -1) {
					temp_track = ref[i][1];
					ref[i][1] = ref[j][1];
					ref[j][1] = temp_track;

					tempTime = ref[i][0];
					ref[i][0] = ref[j][0];
					ref[j][0] = tempTime;
				}
			}

			time = ref[i][0];
		}
		if (count == max)break;
	}

	fprintf(output_fp, "%d %d", time, index);
}
int main() {
	FILE *input_fp = fopen("disk.inp", "rt");
	FILE *output_fp = fopen("disk.out", "wt");

	char charTemp = '\0';
	char command[10];
	char A[] = "FCFS", B[] = "SSTF", C[] = "LOOK";

	fscanf(input_fp, "%s %d", &command, &service);

	Que *Q = (Que*)malloc(sizeof(Que));
	Q->next = NULL;
	Q->trackNum = -1;

	int a, b;
	if (!strcmp(command, A)) {
		while (1) {
			fscanf(input_fp, "%d %d", &a, &b);
			if (a == -1) break;

			addQue(Q, a, b);
		}
		FCFS(output_fp, Q);
	}
	else if (!strcmp(command, B)) {
		int i = 0;
		while (1) {
			fscanf(input_fp, "%d %d", &a, &b);
			if (a == -1) break;
			ref[i][0] = a; 
			ref[i++][1] = b;
		}
		SSTF(output_fp,i);
	}
	else if (!strcmp(command, C)) {
		int i = 0;
		while (1) {
			fscanf(input_fp, "%d %d", &a, &b);
			if (a == -1) break;
			ref[i][0] = a;
			ref[i++][1] = b;
		}
		LOOK(output_fp,i);
	}




	fclose(input_fp);
	fclose(output_fp);
	return 0;
}