#include <stdio.h>
#include<stdlib.h>
void changepositive(int array[][4]); /*If there is a negative number in the difference between the time, change it to a positive number.*/
int findbest(int array[][4], int);  //Find best time to take a nap
void print(int array[][4], int, int);  //For print
void main()
{
	FILE *file;
	file = fopen("schedule.txt", "rt");
	if (file == NULL)
	{
		printf("file not found.\n");
		exit(1);
	}
	else
	{
		char str[100];    //For saving line.
		int value1hour = 0, value1minute = 0, value2hour = 0, value2minute = 0;
		int work = 0, day = 0, line = 0, i = 0, j = 0, count = 0, best = 0;
		int result[5][4];  //For Save nap times available on the day
		while (feof(file) == NULL)
		{
			printf("%s", fgets(str, sizeof(str), file)); //print line
			line++;  //count line
			while (str == NULL)
				count++;  //Count  letters
			if (count == 1 && line == 1)
				work = atoi(&str[0]);     //save Number of schedules           
			else if (line <= work + 1 && line != 1)
			{
				if (line == 2)    //first schedule
				{
					value2hour = atoi(&str[0]);
					value2minute = atoi(&str[3]);
					result[0][0] = value2hour - 10;
					result[0][1] = value2minute - 0;
					result[0][2] = 10;
					result[0][3] = 0;
					value1hour = atoi(&str[5]);
					value1minute = atoi(&str[9]);
					if (line == work + 1)   //If first schedule is last schedule
					{
						result[1][0] = 18 - value1hour;
						result[1][1] = 0 - value1minute;
						result[1][2] = value1hour;
						result[1][3] = value1minute;
					}
				}
				else
				{
					value2hour = atoi(&str[0]);
					value2minute = atoi(&str[3]);
					result[line - 2][0] = value2hour - value1hour;
					result[line - 2][1] = value2minute - value1minute;
					result[line - 2][2] = value1hour;
					result[line - 2][3] = value1minute;
					value1hour = atoi(&str[5]);
					value1minute = atoi(&str[9]);
					if (line == work + 1)  //if this schedule is laast schedule
					{
						result[line - 1][0] = 18 - value1hour;
						result[line - 1][1] = 0 - value1minute;
						result[line - 1][2] = value1hour;
						result[line - 1][3] = value1minute;
					}
				}
				if (work + 1 == line)  //All schedlues are end
				{
					changepositive(result);
					printf("\n");
					best = findbest(result, best);  //find best schedule
					print(result, best, day);
					day++;
					printf("\n");
					for (i = 0; i<5; i++)  //  reset
					{
						for (j = 0; j<4; j++)
							result[i][j] = 0;
					}
					best = 0;
				}
			}
			else       //For next day, reset                              
			{
				line = 1;
				work = atoi(&str[0]);
			}
		}
		printf("\n");
	}
}
void changepositive(int result[][4])  //-1 from hour and +60 to minute
{
	int i = 0;
	for (i = 0; i<5; i++)
	{
		if (result[i][1]<0)
		{
			result[i][0] = result[i][0] - 1;
			result[i][1] = result[i][1] + 60;
		}
	}
}
int findbest(int result[][4], int best) //find the best
{
	int i = 0;
	for (i = 1; i<5; i++)
	{
		if (result[best][0]<result[i][0])
			best = i;
		else if (result[best][0] == result[i][0])
		{
			if (result[best][1]<result[i][1])
				best = i;
			else
				continue;
		}
		else
			continue;
	}
	return best;
}
void print(int result[][4], int best, int day)  //Just print
{
	printf("Day #%d: the longest nap starts at %d:", day + 1, result[best][2]);
	if (result[best][3] == 0)
		printf("00");
	else
		printf("%d", result[best][3]);
	printf(" and will last for %d hours and %d minutes\n", result[best][0], result[best][1]);
}


