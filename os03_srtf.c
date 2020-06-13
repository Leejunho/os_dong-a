#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int SRTF(int n,int end,int AT[], int BT[], int WT, int PN[],int temp[]) {
	int i,time;
	int smallest;
	int count = 0;
	BT[49] = 9999;
	for (time = 0; count != n; time++) {
		smallest = 49;
		for (i = 0; i < n; i++) {
			if (AT[i] <= time && BT[i] < BT[smallest] && BT[i] > 0) {
				smallest = i;
			}
		}
		BT[smallest]--;
		if (BT[smallest] == 0) {
			count++;
			end = time + 1;
			WT = WT + end - AT[smallest] - temp[smallest];
		}
	}
	return WT;
}


int main() {
	FILE *input_fp, *output_fp;

	if ((input_fp = fopen("srtf.inp", "rt")) == NULL)
	{
		fprintf(stderr, "can't open %s\n", "srtf.inp");
	}
	if ((output_fp = fopen("srtf.out", "wt")) == NULL)
	{
		fprintf(stderr, "can't open %s\n", "srtf.out");
	}
	int n, time=0,end=0, WT = 0;
	int P_num = 0;
	int at, bt = 0;
	int PN[50] = { 0, };
	int AT[50] = { 0, };
	int BT[50] = { 0, };
	int temp[50] = { 0, };

	fscanf(input_fp, "%d", &n);

	int i;
	for (i = 0; i < n; i++) {
		fscanf(input_fp, "%d %d %d", &P_num, &at, &bt);
		PN[P_num] = P_num; AT[P_num] = at; BT[P_num] = bt; temp[P_num] = bt;
	}
	WT = SRTF(n, end,AT, BT, WT, PN, temp);
	fprintf(output_fp, "%d", WT);

	fclose(input_fp);
	fclose(output_fp);
	return 0;
}
