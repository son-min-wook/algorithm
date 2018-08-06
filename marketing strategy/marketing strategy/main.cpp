#include <stdio.h>
#include <math.h>
int dots;
double bruteforce(int array[][2], double, double);
double closestpair(int array[][2], double, double);
void main()
{
	int dot[30][2], j, tempx, tempy, i;
	double result;
	printf("how many dots?\n");
	scanf("%d", &dots);
	for (i = 0; i<dots; i++) {                            //enter location
		printf("%d dot location x&y: ", i);
		scanf("%d %d", &dot[i][0], &dot[i][1]);
	}
	for (i = 0; i<dots - 1; i++) {      //sort by x 
		for (j = 0; j<dots - 1; j++) {
			if (dot[j][0] > dot[j + 1][0]) {
				tempx = dot[j][0];
				dot[j][0] = dot[j + 1][0];
				dot[j + 1][0] = tempx;
				tempy = dot[j][1];
				dot[j][1] = dot[j + 1][1];
				dot[j + 1][1] = tempy;
			}
			else if (dot[j][0] == dot[j + 1][0]) {
				if (dot[j][1]>dot[j + 1][1]) {
					tempx = dot[j][0];
					dot[j][0] = dot[j + 1][0];
					dot[j + 1][0] = tempx;
					tempy = dot[j][1];
					dot[j][1] = dot[j + 1][1];
					dot[j + 1][1] = tempy;
				}
			}
		}
	}
	printf("sorting by x\n");
	result = closestpair(dot, 0, dots);       //call function
	printf("%.2f\n", result);
}
double closestpair(int dot[][2], double l, double r) {
	int q = (int)ceil((l + r) / 2);      // find middle
	double dl, dr, d, length;
	int i, j, count = 0, s[30][2], tempx, tempy;
	if ((r - l)<3)                     //devide untill less than 4 dots
		d = bruteforce(dot, l, r);            //calculate the length
	else {
		dl = closestpair(dot, l, q - 1);       //find smallest length of dl
		printf("dl: %f\n", dl);
		dr = closestpair(dot, q, r);         //find smallest length of dr
		printf("dr: %f\n", dr);
		if (dl >= dr)
			d = dr;                //select d
		else
			d = dl;
		printf("find length at the middle range....\n");
		for (i = 0; i<dots; i++) {              //find dots in the range q-d~q+d
			if (dot[i][0] >= (dot[q][0] - d) && dot[i][0] <= (dot[q][0] + d)) {
				s[count][0] = dot[i][0];
				s[count][1] = dot[i][1];
				count++;
			}
		}
		for (i = 0; i<count - 1; i++) {      //sort by y 
			for (j = 0; j<count - 1; j++) {
				if (s[j][1] < s[j + 1][1]) {
					tempx = s[j][0];
					s[j][0] = s[j + 1][0];
					s[j + 1][0] = tempx;
					tempy = s[j][1];
					s[j][1] = s[j + 1][1];
					s[j + 1][1] = tempy;
				}
				else if (s[j][1] == s[j + 1][1]) {
					if (s[j][1]<s[j + 1][1]) {
						tempx = s[j][0];
						s[j][0] = s[j + 1][0];
						s[j + 1][0] = tempx;
						tempy = s[j][1];
						s[j][1] = s[j + 1][1];
						s[j + 1][1] = tempy;
					}
				}
			}
		}
		printf("sorting by y\n");
		for (i = 0; i<count - 1; i++) {          //calculate 7 length
			for (j = i + 1; j<count; j++) {
				length = sqrt(pow(s[i][0] - s[j][0], 2.0) + pow(s[i][1] - s[j][1], 2.0));
				if ((j - i) == 7)
					break;
				if (length<d)
					d = length;
			}
		}
	}
	return d;
}
double bruteforce(int dot[][2], double l, double r)
{
	int i, j;
	double small = 9999999;
	double length;
	if ((r - l) == 0) {         //if only 1 dot.
		length = 10000;
		return length;
	}
	else {                     //if 2 dots or 3 dots
		for (i = 0; i<r - l; i++) {
			for (j = i + 1; j <= r; j++) {
				length = sqrt(pow(dot[i][0] - dot[j][0], 2.0) + pow(dot[i][1] - dot[j][1], 2.0));
				if (length<small)
					small = length;      //find smallest length
			}
		}
		return small;
	}
}