#include <stdio.h>
#include <math.h>
int ccw(int, int, int, int, int, int);
void main()
{
	int frosh, location[100][2], i, miny = 9999, minx = 9999, minfrosh, j = 0, result[100], last, q, w, e = 0, re, count = 0, x = 0, y = 0;
	float angle[100][2], temp, length = 0;
	printf("how many frosh?\n");
	scanf("%d", &frosh);
	for (i = 0; i<frosh; i++) {                            //enter location
		printf("%d frosh location x&y: ", i);
		scanf("%d %d", &location[i][0], &location[i][1]);
	}
	for (i = 0; i<frosh; i++) {                          //Find bottom coordinates
		if (location[i][1]<miny) {
			miny = location[i][1];
			minx = location[i][0];
			minfrosh = i;
		}
		else if (location[i][1] == miny) {
			if (location[i][0]<minx) {
				miny = location[i][1];
				minx = location[i][0];
				minfrosh = i;
			}
		}
	}
	printf("minfrosh: %d\n", minfrosh);
	for (i = 0; i<frosh; i++) {
		if (i == minfrosh) {                   //skip minfrosh
			printf("pass\n");
			continue;
		}
		else {
			if (location[i][0]<location[minfrosh][0]) {          //if the starting point is to the right of the value
				printf("<\n");
				angle[j][0] = i;
				angle[j][1] = ((location[i][0] - location[minfrosh][0])) / sqrt(pow(location[i][0] - location[minfrosh][0], 2.0) + pow(location[i][1] - location[minfrosh][1], 2.0));
				j++;
			}
			else if (location[i][0] == location[minfrosh][0]) {   //if the starting point's x same with the value
				printf("==\n");
				angle[j][0] = i;
				angle[j][1] = 0;
				j++;
			}
			else if (location[i][1] == location[minfrosh][1]) {     //if the starting point's y same with the value
				if (location[i][0]<location[minfrosh][0]) {       //and if the starting point is to the right of the value
					angle[j][0] = i;
					angle[j][1] = -1;
					j++;
				}
				else {                                        //and if the starting point is to the left of the value
					angle[j][0] = i;
					angle[j][1] = 1;
					j++;
				}
			}
			else {                          //and if the starting point is to the right of the value
				printf(">\n");
				angle[j][0] = i;
				angle[j][1] = ((location[i][0] - location[minfrosh][0])) / sqrt(pow(location[i][0] - location[minfrosh][0], 2.0) + pow(location[i][1] - location[minfrosh][1], 2.0));
				j++;
			}
		}
	}
	for (i = 0; i<frosh - 1; i++) {                       //arrange cos value in large numbers.
		for (j = 0; j<frosh - 2; j++) {
			if (angle[j][1] < angle[j + 1][1]) {        //number of comparisons is data count-1
				temp = angle[j][1];
				angle[j][1] = angle[j + 1][1];
				angle[j + 1][1] = temp;
				temp = angle[j][0];
				angle[j][0] = angle[j + 1][0];
				angle[j + 1][00] = temp;
			}
		}
	}
	printf("sort finish\n");
	for (i = 0; i<frosh - 1; i++)
		printf("%.0f %.2f\n", angle[i][0], angle[i][1]);         //sort finish
	last = (int)angle[frosh - 2][0];
	x = 2;
	y = 2;
	result[0] = minfrosh;         //starting point
	result[1] = angle[0][0];     //first sorted value
	result[2] = angle[1][0];       //second sorted value           //always true
	count = 3;
	while ((int)angle[y][0] != last) {               //when the new value is the last of the aligned values
		re = ccw(location[result[x - 1]][0], location[result[x - 1]][1], location[result[x]][0], location[result[x]][1], location[(int)angle[y][0]][0], location[(int)angle[y][0]][1]);
		if (re == -1) {       //a clockwise direction
			while (re == -1) {          //until counterclockwise direction or straight line
				x--;        // 2,3,4 x -> 1,2,4 o
				count--;
				re = ccw(location[result[x - 1]][0], location[result[x - 1]][1], location[result[x]][0], location[result[x]][1], location[(int)angle[y][0]][0], location[(int)angle[y][0]][1]);
			}
			result[x + 1] = (int)angle[y][0];
			count++;
			x++;
			y++;
		}
		else {
			result[x + 1] = (int)angle[y][0];
			count++;
			x++;
			y++;
		}
	}
	for (i = 0; i<count; i++)
		printf(" %d -> ", result[i]);                     //show the path
	printf(" %d -> (0,0)-> %d\n", last, result[0]);
	for (i = 1; i<count; i++)
		length = length + sqrt(pow(location[result[i]][0] - location[result[i - 1]][0], 2.0) + pow(location[result[i]][1] - location[result[i - 1]][1], 2.0));
	length = length + sqrt(pow(location[(int)angle[frosh - 3][0]][0] - location[last][0], 2.0) + pow(location[(int)angle[frosh - 3][0]][1] - location[last][1], 2.0));  //length of last point->before
	length = length + sqrt(pow(location[last][0], 2.0) + pow(location[last][1], 2.0));          //length of (0,0)->last point
	length = length + sqrt(pow(location[minfrosh][0], 2.0) + pow(location[minfrosh][1], 2.0));  //length of (0,0)->starting point
	length = length + 2;          //the length of a knot
	printf("length: %.2f\n", length);
}
int ccw(int x1, int y1, int x2, int y2, int x3, int y3) {
	int temp = x1*y2 + x2*y3 + x3*y1;
	temp = temp - y1*x2 - y2*x3 - y3*x1;
	if (temp > 0) {            // counterclockwise direction
		return 1;
	}
	else if (temp < 0) {      // clockwise direction
		return -1;
	}
	else {          // straight line
		return 0;
	}
}