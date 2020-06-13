#include <stdio.h>
#include <stdlib.h>
int frame;
int ref[10000][2];
int memory[10000][3];

void FIFO(FILE *output_fp) {
	int i = 0, j;
	int index = 0;
	int pageFault = 0;
	int MaxMemory = 0, MaxPage = 0;
	int bufChange = 0;
	int isSame = 0, isFull = 0;
	int MaxCount[100][2] = { 0, };//프로세스 번호 프레임 갯수 입력
	int PageList[100][4] = { 0, };//페이지와 페이지가 있는 인덱스 위치
	while (ref[index][0] >= 0) {
		isSame = 0, isFull = 0;
		for (i = 0; i < MaxMemory; i++) {
			if (memory[i][0] == ref[index][0]) {
				if (memory[i][1] == ref[index][1]) {
					isSame++;
					break;
				}
			}
		}
		if (!isSame) {
			pageFault++;
			for (i = 0; i < MaxPage; i++) {
				if (ref[index][0] == MaxCount[i][0]) {
					if (MaxCount[i][1] == frame) isFull = 1;

					break;
				}
			}
			if (i == MaxPage || !isFull) {// 해당 프로세스 적재 되지 않았음
				if (i == MaxPage) {
					MaxCount[MaxPage][0] = ref[index][0];
					MaxPage++;
				}
				MaxCount[i][1]++;
				memory[MaxMemory][0] = ref[index][0];
				memory[MaxMemory][1] = ref[index][1];
				memory[MaxMemory][2] = index;
				MaxMemory++;
			}
			else {// 페이지 교체
				bufChange = -1;
				for (i = 0; i < MaxMemory; i++) {
					if (memory[i][0] == ref[index][0]) {
						if (bufChange < 0) bufChange = i;
						else if (memory[bufChange][2] > memory[i][2]) bufChange = i;
					}
				}
				memory[bufChange][1] = ref[index][1];
				memory[bufChange][2] = index;
			}
		}
		

		index++;
	}


	fprintf(output_fp, "FIFO: %d\n", pageFault);
	for (i = 0; i < MaxMemory; i++) {
		fprintf(output_fp, "%d %d %d\n", i, memory[i][0], memory[i][1]);
	}
	return;
}
void LRU(FILE *output_fp) {
	int i=0, j;
	int index = 0;
	int pageFault = 0;
	int MaxMemory=0,MaxPage=0;
	int bufChange = 0;
	int isSame = 0, isFull = 0;
	int MaxCount[100][2] = { 0, };//프로세스 번호 프레임 갯수 입력
	int PageList[100][4] = { 0, };//페이지와 페이지가 있는 인덱스 위치
	while (ref[index][0] >= 0) {
		isSame = 0, isFull = 0;
		for (i = 0; i < MaxMemory; i++) {
			if (memory[i][0] == ref[index][0]) {
				if (memory[i][1] == ref[index][1]) {
					isSame++;
					break;
				}
			}
		}
		if (!isSame) {
			pageFault++;
			for (i = 0; i < MaxPage; i++) {
				if (ref[index][0] == MaxCount[i][0]) {
					if (MaxCount[i][1] == frame) isFull = 1;

					break;
				}
			}
			if (i == MaxPage || !isFull) {// 해당 프로세스 적재 되지 않았음
				if (i == MaxPage) {
					MaxCount[MaxPage][0] = ref[index][0];
					MaxPage++;
				}
				MaxCount[i][1]++;
				memory[MaxMemory][0] = ref[index][0];
				memory[MaxMemory][1] = ref[index][1];
				memory[MaxMemory][2] = index;
				MaxMemory++;
			}
			else {// 페이지 교체
				bufChange = -1;
				for (i = 0; i < MaxMemory; i++) {
					if (memory[i][0] == ref[index][0]) {
						if (bufChange < 0) bufChange = i;
						else if (memory[bufChange][2] > memory[i][2]) bufChange = i;
					}
				}
				memory[bufChange][1] = ref[index][1];
				memory[bufChange][2] = index;
			}
		}
		else {
			memory[i][2] = index;
		}

		index++;
	}

	
	fprintf(output_fp, "LRU: %d\n", pageFault);
	for (i = 0; i < MaxMemory; i++) {
		fprintf(output_fp, "%d %d %d\n", i, memory[i][0], memory[i][1]);
	}
	return;
}
void OPT(FILE *output_fp) {
	int i = 0, j;
	int index = 0,pindex=0;
	int pageFault = 0;
	int MaxMemory = 0, MaxPage = 0;
	int bufChange = 0;
	int isSame = 0, isFull = 0;
	int MaxCount[100][2] = { 0, };//프로세스 번호 프레임 갯수 입력
	int PageList[100][4] = { 0, };//페이지와 페이지가 있는 인덱스 위치
	while (ref[index][0] >= 0) {
		isSame = 0, isFull = 0; pindex = 0;
		for (i = 0; i < MaxMemory; i++) {
			if (memory[i][0] == ref[index][0]) {
				if (memory[i][1] == ref[index][1]) {
					isSame++;
					break;
				}
				else {
					PageList[pindex][0] = memory[i][1];
					PageList[pindex][1] = memory[i][2];
					PageList[pindex][2] = i;
					PageList[pindex][3] = -1;
					pindex++;
				}
			}
		}
		if (!isSame) {
			pageFault++;
			for (i = 0; i < MaxPage; i++) {
				if (ref[index][0] == MaxCount[i][0]) {
					if (MaxCount[i][1] == frame) isFull = 1;

					break;
				}
			}
			if (i == MaxPage || !isFull) {// 해당 프로세스 적재 되지 않았음
				if (i == MaxPage) {
					MaxCount[MaxPage][0] = ref[index][0];
					MaxPage++;
				}
				MaxCount[i][1]++;
				memory[MaxMemory][0] = ref[index][0];
				memory[MaxMemory][1] = ref[index][1];
				memory[MaxMemory][2] = index;
				MaxMemory++;
			}
			else {// 페이지 교체
				for (i = index + 1; ref[i][0]>0; i++){
					if (ref[i][0] == ref[index][0]){
						for (j = 0; j < pindex; j++){
							if (PageList[j][0] == ref[i][1]){
								if (PageList[j][3] <0)PageList[j][3] = i;
							}
						}
					}
				}
				bufChange = 0;
				for (i = 1; i<pindex; i++){
					if (PageList[bufChange][3]<0){
						if (PageList[i][3]<0 && (PageList[bufChange][1] > PageList[i][1]))
							bufChange = i;
					}
					else if (PageList[i][3]<0){
						bufChange = i;
					}
					else{
						if (PageList[bufChange][3] < PageList[i][3])
							bufChange = i;
					}
				}
				bufChange = PageList[bufChange][2];

				memory[bufChange][1] = ref[index][1];
				memory[bufChange][2] = index;
			}
			
		}
		

		index++;
	}
	fprintf(output_fp, "OPT: %d\n", pageFault);
	for (i = 0; i < MaxMemory; i++) {
		fprintf(output_fp, "%d %d %d\n", i, memory[i][0], memory[i][1]);
	}

	return;
}

int main() {
	FILE *input_fp = fopen("page.inp", "rt");
	FILE *output_fp = fopen("page.out", "wt");

	
	fscanf(input_fp, "%d\n", &frame);

	int PID, page_num;
	int i=0;
	while (1) {
		fscanf(input_fp, "%d %d", &PID, &page_num);
		ref[i][0] = PID;
		ref[i][1] = page_num;
		i++;

		if (PID == -1)
			break;
	}
	FIFO(output_fp);
	LRU(output_fp);
	OPT(output_fp);
	fclose(input_fp);
	fclose(output_fp);
	return 0;
}