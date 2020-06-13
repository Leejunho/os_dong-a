#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void print_SJF(int n, int WT[], FILE *output_fp) {
	int i;
	int result = 0;
	for (i = 0; i < n; i++) {
		result += WT[i];
	}
	fprintf(output_fp, "%d", result);
}

void sort1(int n, int PN[], int AT[], int BT[])
{
	int temp, temp2, temp3;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n - 1; j++)
		{
			if (AT[j] > AT[j + 1])
			{
				temp = AT[j];
				AT[j] = AT[j + 1];
				AT[j + 1] = temp;

				temp2 = BT[j];
				BT[j] = BT[j + 1];
				BT[j + 1] = temp2;

				temp3 = PN[j];
				PN[j] = PN[j + 1];
				PN[j + 1] = temp3;
			}
			else if (PN[j] > PN[j + 1] && AT[j] == AT[j + 1]) {
				temp = AT[j];
				AT[j] = AT[j + 1];
				AT[j + 1] = temp;

				temp2 = BT[j];
				BT[j] = BT[j + 1];
				BT[j + 1] = temp2;

				temp3 = PN[j];
				PN[j] = PN[j + 1];
				PN[j + 1] = temp3;
			}
		}
	}
}

void sort2(int n, int PN[], int AT[], int BT[])
{
	int temp,min;
	int bttime = 0,k=1;

	for (int i = 0; i < n; i++)
	{
		bttime = bttime + BT[i];
		if (i == 0) bttime += AT[i];
		min = BT[k];
		for (int j = k; j < n; j++)
		{
			if (bttime >= AT[j] && BT[j] < min ) {
				temp = PN[k];
				PN[k] = PN[j];
				PN[j] = temp;

				temp = AT[k];
				AT[k] = AT[j];
				AT[j] = temp;

				temp = BT[k];
				BT[k] = BT[j];
				BT[j] = temp;
		
			}

		}
		k++;
		
	}
}

void SJF(int n, int AT[], int BT[], int WT[], int PN[]) {
	int i;
	int time = 0, turn = 0, temp = 0;
	for (i = 0; i < n; i++) {
		time = time + BT[i];
		if (temp - AT[i] > 0) {
			turn = time - AT[i];
			WT[i] = turn - BT[i];
			
		}
		else if (temp - AT[i] <= 0) {
			sort2(n, PN, AT, BT);
			time = time + (AT[i] - temp);
			turn = time - AT[i];
			WT[i] = turn - BT[i];
			
		}
		temp = time;
	}
}
int main() {
	FILE *input_fp, *output_fp;

	if ((input_fp = fopen("sjf.inp", "rt")) == NULL)
	{
		fprintf(stderr, "can't open %s\n", "sjf.inp");
	}
	if ((output_fp = fopen("sjf.out", "wt")) == NULL)
	{
		fprintf(stderr, "can't open %s\n", "sjf.out");
	}
	int n;
	int P_num = 0;
	int at, bt = 0;
	int PN[50] = { 0, };
	int AT[50] = { 0, };
	int BT[50] = { 0, };
	int WT[50] = { 0, };

	fscanf(input_fp, "%d", &n);

	int i;
	for (i = 0; i < n; i++) {
		fscanf(input_fp, "%d %d %d", &P_num, &at, &bt);
		PN[P_num] = P_num; AT[P_num] = at; BT[P_num] = bt;
	}
	sort1(n, PN, AT, BT);
	
	
	SJF(n, AT, BT, WT, PN);
	print_SJF(n, WT, output_fp);

	fclose(input_fp);
	fclose(output_fp);
	return 0;
}