#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int compare(void *first, void *second);
int main()
{
	char str[300] = { 0 }, str2[300] = { 0 }, str3[300] = { 0 };
	int i = 0, j = 0;
	int arr1[3], arr2[3], arr3[3];
	int countyear = 0, countmonth = 0, countday = 0;
	int year1 = 0, year2 = 0, year3 = 0;
	int month1 = 0, month2 = 0, month3 = 0;
	int day1 = 0, day2 = 0, day3 = 0;
	int state = 0, beforestate = -1;
	fgets(str, sizeof(str), stdin);
	fgets(str2, sizeof(str2), stdin);
	fgets(str3, sizeof(str3), stdin);
	if (state != 1 || state != 2 || state != 0)
		state = -1;
	beforestate = -1;

	for (i = 0; i < strlen(str); i++)
	{
		if (str[i] >= 48 && str[i] <= 57)
		{

			if (state == -1)
				state = 0;

			if (beforestate == 0)
				state = 1;
			else if (beforestate == -1)
				state = 0;
			else if (beforestate == 1)
				state = 2;
			if (state == 0)
			{
				year1 = year1 * 10;
				year1 = year1 + str[i] - 48;
				countyear++;
			}
			else if (state == 1)
			{
				month1 = month1 * 10;
				month1 = month1 + str[i] - 48;
				countmonth++;
			}
			else if (state == 2)
			{
				day1 = day1 * 10;
				day1 = day1 + str[i] - 48;
				countday++;
			}
		}
		else if (str[i] < 48 || str[i]>57)
		{
			if (state == -1)
				continue;
			if (state == 0)
			{
				if (countyear == 2) {
					year1 = year1 + 2000;

				}
				else

					state = -1;
				beforestate = 0;
				arr1[0] = year1;
				countyear = 0;
			}
			else if (state == 1)
			{

				arr1[1] = month1;
				state = -1;
				beforestate = 1;
				countmonth = 0;
			}
			else if (state == 2)
			{

				arr1[2] = day1;
				state = -1;
				countmonth = 0;
			}
		}
	}

	if (state != 1 || state != 2 || state != 0)
		state = -1;
	beforestate = -1;

	for (i = 0; i < strlen(str2); i++)
	{
		if (str2[i] >= 48 && str2[i] <= 57)
		{

			if (state == -1)
				state = 0;

			if (beforestate == 0)
				state = 1;
			else if (beforestate == -1)
				state = 0;
			else if (beforestate == 1)
				state = 2;
			if (state == 0)
			{
				year2 = year2 * 10;
				year2 = year2 + str2[i] - 48;
				countyear++;
			}
			else if (state == 1)
			{
				month2 = month2 * 10;
				month2 = month2 + str2[i] - 48;
				countmonth++;
			}
			else if (state == 2)
			{
				day2 = day2 * 10;
				day2 = day2 + str2[i] - 48;
				countday++;
			}
		}
		else if (str2[i] < 48 || str2[i]>57)
		{

			if (state == -1)
				continue;
			if (state == 0)
			{
				if (countyear == 2) {
					year2 = year2 + 2000;

				}
				else

					state = -1;
				beforestate = 0;
				arr2[0] = year2;
				countyear = 0;
			}
			else if (state == 1)
			{

				arr2[1] = month2;
				state = -1;
				beforestate = 1;
				countmonth = 0;
			}
			else if (state == 2)
			{

				arr2[2] = day2;
				state = -1;
				countmonth = 0;
			}
		}
	}

	if (state != 1 || state != 2 || state != 0)
		state = -1;
	beforestate = -1;

	for (i = 0; i < strlen(str3); i++)
	{
		if (str3[i] >= 48 && str3[i] <= 57)
		{

			if (state == -1)
				state = 0;

			if (beforestate == 0)
				state = 1;
			else if (beforestate == -1)
				state = 0;
			else if (beforestate == 1)
				state = 2;
			if (state == 0)
			{
				year3 = year3 * 10;
				year3 = year3 + str3[i] - 48;
				countyear++;
			}
			else if (state == 1)
			{
				month3 = month3 * 10;
				month3 = month3 + str3[i] - 48;
				countmonth++;
			}
			else if (state == 2)
			{
				day3 = day3 * 10;
				day3 = day3 + str3[i] - 48;
				countday++;
			}
		}
		else if (str3[i] < 48 || str3[i]>57)
		{
			if (state == -1)
				continue;
			if (state == 0)
			{
				if (countyear == 2) {
					year3 = year3 + 2000;

				}
				else

					state = -1;
				beforestate = 0;
				arr3[0] = year3;
				countyear = 0;
			}
			else if (state == 1)
			{

				arr3[1] = month3;
				state = -1;
				beforestate = 1;
				countmonth = 0;
			}
			else if (state == 2)
			{

				arr3[2] = day3;
				state = -1;
				countmonth = 0;
			}
		}
	}
	int ar1 = 0, ar2 = 0, ar3 = 0;
	ar1 = arr1[0] * 10000 + arr1[1] * 100 + arr1[2];
	ar2 = arr2[0] * 10000 + arr2[1] * 100 + arr2[2];
	ar3 = arr3[0] * 10000 + arr3[1] * 100 + arr3[2];
	int min = 0;
	int asd[3];
	asd[0] = ar1;
	asd[1] = ar2;
	asd[2] = ar3;
	qsort(asd, 3, sizeof(int), compare);
	for (i = 0; i < 3; i++)
	{
		if (asd[i] == ar1)
			printf("%s", str);
		if (asd[i] == ar2)
			printf("%s", str2);
		if (asd[i] == ar3)
			printf("%s", str3);
	}
	return 0;
}
int compare(void *first, void *second)
{
	if (*(int*)first > *(int*)second)
		return 1;
	else if (*(int*)first < *(int*)second)
		return -1;
	else
		return 0;
}