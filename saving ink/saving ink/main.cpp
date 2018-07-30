#include <stdio.h>
#include<stdlib.h>
#include <math.h>
int source, f, n, edge = 0, spot[30][2];       //
float weight[100][3], table[30][30];
int cycle(int start, int end)                  //find it make cycle or not.
{
	int j, k;
	if (source == end)            //start==end it is cylce
		return 1;
	for (j = 0; j < n; j++) {               //look all edge of start with end and on and on
		if (table[end][j] != -1 && start != j)
		{
			if (cycle(end, j))
				return 1;
		}
	}
	return 0;
}
void build_tree()      //store the weight into table and call cycle, if it is cycle, turn the weight -1
{
	int start, end, k, count = 0, i, j;
	float weights;
	for (count = 0; count < n; f++)
	{
		if (f >= edge)
			break;
		start = weight[f][1];
		end = weight[f][2];
		weights = weight[f][0];
		table[start][end] = table[end][start] = weights;
		source = start;
		k = cycle(start, end);
		if (k)
			table[start][end] = table[end][start] = -1;
		else
			count++;
	}
}

void main()
{
	int line = 0, i = 0, j = 0;
	float temp1, temp2, temp3, sum = 0;
	FILE *fp;
	fp = fopen("ink.txt", "rt");
	if (fp == NULL)
	{
		printf("file not found.\n");
		exit(1);
	}
	else {
		while (feof(fp) == NULL) {
			if (line == 0) {
				fscanf(fp, "%d", &n);        //save count of spot
				line++;
			}
			else if (line != 0) {
				while (fscanf(fp, "%d %d", &spot[i][0], &spot[i][1]) != EOF)  //save spot
				{
					line++;
					i++;
				}
			}
		}
	}
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			weight[i][j] = -1;
			table[i][j] = -1;
		}
	}
	for (i = 0; i<n - 1; i++)
	{
		for (j = i + 1; j<n; j++)     //save weight , start,end
		{
			weight[edge][0] = sqrt(pow(spot[j][1] - spot[i][1], 2.0) + pow(spot[j][0] - spot[i][0], 2.0));
			weight[edge][1] = i;
			weight[edge][2] = j;
			edge++;
		}
	}
	for (i = 0; i<edge - 1; i++)
	{
		for (j = 0; j<edge - 1; j++)
		{
			if (weight[j][0] > weight[j + 1][0])   //sorting by weight
			{
				temp1 = weight[j][0];
				temp2 = weight[j][1];
				temp3 = weight[j][2];
				weight[j][0] = weight[j + 1][0];
				weight[j][1] = weight[j + 1][1];
				weight[j][2] = weight[j + 1][2];
				weight[j + 1][0] = temp1;
				weight[j + 1][1] = temp2;
				weight[j + 1][2] = temp3;
			}
		}
	}
	for (i = 0; i<edge; i++)      //store sorted weight into table
		table[int(weight[i][1])][int(weight[i][2])] = weight[i][0];
	build_tree();         // call function for check cycle
	for (i = 0; i < n; i++)
		for (j = i + 1; j < n; j++)
			if (table[i][j] != -1)
			{
				printf("%d ------ %d = %f\n", i, j, table[i][j]);
				sum += table[i][j];
			}
	printf("Total Weight : %f\n", sum);
}
