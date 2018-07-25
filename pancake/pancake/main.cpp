#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
void fliping(int[], int[], int, int);
void main()
{
	char pancake1[30] = { 0, };
	int i = 0, j = 0, k = 0, count = 0, order = 1, lastmin = 31, pancake2[30] = { 0, }, pancake3[30] = { 0, };
	int min = 31, mincount = 0, minnum[30] = { 0, }, max = 0, flip = 0, repeat = 0;
	int site = 0, correct = 0, cycle = 0, maxim = 0;
	printf("enter pancake\n");
	scanf("%[^\n]s", pancake1);
	while (pancake1[i] != NULL)                     //convert a character to an integer
	{
		if (pancake1[i] != ' ')
		{
			pancake2[j] = pancake1[i] - 48;
			count++;
			j++;
		}
		i++;
	}
	for (i = 0; i<count; i++)                      //copy pancakw2 to pancake3
		pancake3[i] = pancake2[i];
	int a = count;
	while (a>0)                               //store to minnum[] according to size
	{                                        //ex) 1 39 4 6 29-> 1 5 2 3 4
		for (i = 0; i<count; i++)
		{
			if (pancake2[i] == 0)
				continue;
			else if (pancake2[i] <= min)
			{
				if (lastmin == pancake2[i] && lastmin != 31)
				{
					repeat++;
					if (repeat >= 2)
					{
						order++;
						repeat = 0;
					}
					order = order - 1;
				}
				min = pancake2[i];
				mincount = i;
			}
			if (lastmin != min)
				repeat = 0;
		}
		lastmin = min;
		minnum[mincount] = order;
		pancake2[mincount] = 0;
		order++;
		a--;
		min = 31;
	}
	while (correct != count - 1)             //until alignment
	{
		for (i = 0; i<count; i++)
		{
			if (minnum[i] + 1 == minnum[i + 1] || minnum[i] == minnum[i + 1])    //calculate how many alignments have been made
				correct++;
		}
		site = 0;
		if (correct == count - 1)               //exit when all is right
		{
			printf("0");
			printf("\n");
			break;
		}
		else
		{
			for (i = 0; i<count - cycle; i++)           //find a biggest one
			{
				if (maxim<minnum[i])
				{
					maxim = minnum[i];
					max = i;
				}
			}
			if (max<count - cycle - 1 && max>0)  //biggest, but not at the end
			{
				if (minnum[max - 1]>minnum[max + 1]) //If the left of the largest number is greater than the right of the larger number, flip from the largest number
				{
					fliping(pancake3, minnum, count, count - max);
					printf("flip(%d)\n", count - max);
					for (i = 0; i<count; i++)
						printf("%d ", pancake3[i]);
					printf("\n");
					fliping(pancake3, minnum, count, 1 + cycle);
					printf("flip(%d)\n", 1 + cycle);
					for (i = 0; i<count; i++)
						printf("%d ", pancake3[i]);
					printf("\n");
				}
				else
				{
					i = 0;
					while (minnum[max + i] - 1 == minnum[max + i + 1] || minnum[max + i] == minnum[max + i + 1])  //If it continues from the right of the largest number, it flips at the end
					{
						i++;
						site++;
					}
					fliping(pancake3, minnum, count, count - max - site);
					printf("flip(%d)\n", count - max - site);
					for (i = 0; i<count; i++)
						printf("%d ", pancake3[i]);
					printf("\n");
					if (site == 0)  //if there is no consecutive number
					{
						fliping(pancake3, minnum, count, count - cycle - 1);
						printf("flip(%d)\n", count - cycle - 1);
						for (i = 0; i<count; i++)
							printf("%d ", pancake3[i]);
						printf("\n");
					}
					else
					{
						fliping(pancake3, minnum, count, count - site);
						printf("flip(%d)\n", count - site);
						for (i = 0; i<count; i++)
							printf("%d ", pancake3[i]);
						printf("\n");
						fliping(pancake3, minnum, count, cycle + 1);
						printf("flip(%d)\n", cycle + 1);
						for (i = 0; i<count; i++)
							printf("%d ", pancake3[i]);
						printf("\n");
						cycle = cycle + site;
					}
				}
				cycle++;
			}
			else if (max == 0)    //the biggest number is at the front
			{
				fliping(pancake3, minnum, count, cycle + 1);
				printf("flip(%d)\n", cycle + 1);
				for (i = 0; i<count; i++)
					printf("%d ", pancake3[i]);
				printf("\n");
				cycle++;
			}
			else
			{               //the largest number is at the end
				i = 0;
				while (minnum[max - i] - 1 == minnum[max - i - 1])  //If it continues from the right of the largest number, it flips at the end
				{
					i++;
					site++;
				}
				cycle = cycle + site + 1;
			}
		}
		maxim = 0;
		max = 0;
		correct = 0;
	}
}
void fliping(int pancake[], int order[], int count, int set)
{
	int i, j = count - set;
	int temp1[30] = { 0, }, temp2[30] = { 0, };
	for (i = 0; i<count; i++)
	{
		temp1[i] = pancake[i];
		temp2[i] = order[i];
	}
	for (i = 0; i<count - set + 1; i++)
	{
		pancake[i] = temp1[j];
		order[i] = temp2[j];
		j--;
	}
}

