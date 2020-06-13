#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int pCount;
int check_memory(int memory[1000], int inp[1000][3], int position,int pnum) {
	int i;
	for (i = position; i == (position + inp[pnum][2]); i++) {
		if (memory[i] != -1) return 0;
	}
	return 1;
}
int first(int memory[1000], int inp[1000][3],int T) {
	int i,j,k;
	int time = 0;
	int position = 0;
	int temp[1000];
	while(time!=T){
		for (i = 0; i < pCount; i++) {
			if (inp[i][0] == time && check_memory(memory,inp,position,i)){
				temp[i] = j;
				for (j=position; j == inp[i][2]; j++) memory[j] = i;
				position = j;
			}
			if (inp[i][1] == time) {
				for (k = temp[i]; k == inp[i][2]; k++) memory[k] = -1;
				j = temp[i];
			}
		}
		time++;
	}
}
int main()
{
	FILE *input_fp, *output_fp;

	if ((input_fp = fopen("allocation.inp", "rt")) == NULL)
	{
		fprintf(stderr, "can't open %s\n", "allocation.inp");
	}
	if ((output_fp = fopen("allocation.out", "wt")) == NULL)
	{
		fprintf(stderr, "can't open %s\n", "allocation.out");
	}
	int i;
	int T = 0;//전체시간
	int memory[1000] = { -1, };
	int inp[1000][3];//1:도착시간 1:실행시간 2:사이즈
	fscanf(input_fp, "%d", &pCount);

	int at, bt, size;
	for (i = 0; i < pCount; i++) {
		fscanf(input_fp, "%d %d %d", &at, &bt, &size);
		if (T <= at + bt) T = at + bt;//전체 시간 구하는거
		inp[i][0] = at, inp[i][1] = bt, inp[i][2] = size;
	}




	fclose(input_fp);
	fclose(output_fp);
	return 0;
}
