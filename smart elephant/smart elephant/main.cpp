#include <stdio.h>
#include<stdlib.h>
void main()
{
	int i = 0, k = 0, l = 0, min_weight = 10000, line = 0;
	int data[1000][2];
	int sort[1000][2];
	int stupid[1000] = { 0, };
	int temp[1][2];
	int count = line, j = 0, minsite = 0, under = 0;
	FILE *fp;
	fp = fopen("elephant.txt", "rt");
	if (fp == NULL)
	{
		printf("file not found.\n");
		exit(1);
	}
	else
	{
		while (fscanf(fp, "%d %d", &data[i][0], &data[i][1]) != EOF)
		{
			line++;
			i++;
		}
		for (i = 0; i<line; i++) {                             //copy data to sort array
			sort[i][0] = data[i][0];
			sort[i][1] = data[i][1];
		}
		while (j<line)                                    //sorting about weight start
		{
			for (i = j; i<line; i++)
			{
				if (sort[i][0] <= min_weight)
				{
					min_weight = sort[i][0];
					minsite = i;
				}
			}
			min_weight = 10000;
			temp[0][0] = sort[j][0];
			temp[0][1] = sort[j][1];
			sort[j][0] = sort[minsite][0];
			sort[j][1] = sort[minsite][1];
			sort[minsite][0] = temp[0][0];
			sort[minsite][1] = temp[0][1];
			j++;
		}
	}
	for (l = 0; l<line; l++)
	{
		for (i = k; i<line; i++)
		{
			if (sort[k][1]>sort[i][1])                 // count how many elephants that more fat and more idiot than this elephant
				under++;                              // ex) 500 1000   ->2
			stupid[k] = under;                          //     1000 900   ->1
		}	                                          //     2000 800   ->0
		k++;                                          //     3000 3000  ->0
		under = 0;
	}
	int max = -1, q = 0, w = 1;
	int result[1000][2] = { -1, };
	int number = 0, maxsite = -1;
	while (1)                                       //starter is the biggest value of stupid array. biggest value can make longer.
	{                    // and then next untill end, find (the best biggest value) && (IQ is smaller than (before result array's value)'s IQ)
		for (i = maxsite + 1; i<line; i++)
		{
			if (q == 0)
			{
				for (i = 0; i<line; i++)
				{
					if (stupid[i]>max)
					{
						max = stupid[i];
						maxsite = i;
					}
				}
			}
			else
			{
				for (i = w; i<line; i++)
				{
					if (stupid[i] >= max&&sort[result[q - 1][1]][1] >= sort[i][1])
					{
						if (sort[i][0] == sort[maxsite][0])
							continue;
						else
						{
							max = stupid[i];
							maxsite = i;
						}
					}
				}
			}
			result[q][0] = max;
			result[q][1] = maxsite;
			number++;
			max = 0;
			w = maxsite + 1;
		}
		if (result[q][1] == line || result[q][0] == 0)
			break;
		else
			q++;
	}
	printf("%d\n", number);
	for (i = 0; i<q + 1; i++)                                   //back to data array and print
	{
		for (j = 0; j<line; j++)
		{
			if (sort[result[i][1]][0] == data[j][0] && sort[result[i][1]][1] == data[j][1])
				printf("%d\n", j + 1);
		}
	}
}
